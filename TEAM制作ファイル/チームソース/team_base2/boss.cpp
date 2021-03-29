#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// ボスの処理 [boss.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "boss.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "portal.h"
#include "meshfield.h"
#include "collision.h"

#include <stdio.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void LoadXFileBoss(const char* cXFileName, Model *model);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Boss g_Boss;									// ボスの情報

CharacterPartsInfo g_partsBoss;	// boss read info
Model g_modelBoss[BOSS_MODEL_PARTS];				// boss model

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//テキストから読み込み
	ReadCharacterInfo(&g_partsBoss, "data//TXT//motion_Boss.txt");

	//読み込んだ情報を使ってXファイル読み込み
	for (int nCntModel = 0; nCntModel < g_partsBoss.nModelNum; nCntModel++) LoadXFileBoss(&g_partsBoss.cModelFileName[nCntModel][0], &g_modelBoss[nCntModel]);

	//各パーツの階層構造設定
	for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
	{// Robot000
		g_modelBoss[nCntModel].nNumModel = g_partsBoss.nModelNum;
		g_modelBoss[nCntModel].nIdxModelParent = g_partsBoss.nModelParent[nCntModel];
		g_modelBoss[nCntModel].pos = D3DXVECTOR3(g_partsBoss.fModelPos[nCntModel][0], g_partsBoss.fModelPos[nCntModel][1], g_partsBoss.fModelPos[nCntModel][2]);
		g_modelBoss[nCntModel].rot = D3DXVECTOR3(g_partsBoss.fModelRot[nCntModel][0], g_partsBoss.fModelRot[nCntModel][1], g_partsBoss.fModelRot[nCntModel][2]);
	}

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//初期設定
		g_Boss.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
		g_Boss.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
		g_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動値の初期設定
		g_Boss.bUse = false;
		g_Boss.bInvincible = false;
		g_Boss.nLife = ENEMY_HP_MAX;
		g_Boss.nLifeMax = ENEMY_HP_MAX;
		g_Boss.bHit = false;
		g_Boss.bAttack = false;
		g_Boss.dwTimeAtk = NULL;
		g_Boss.dwTimeInv = NULL;
	}
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitBoss(void)
{
	for (int nCnt = 0; nCnt < BOSS_MODEL_PARTS; nCnt++)
	{
		if (g_modelBoss[nCnt].pMeshModel != NULL)
		{//	MESH RELEASE
			g_modelBoss[nCnt].pMeshModel->Release();
			g_modelBoss[nCnt].pMeshModel = NULL;
		}
		if (g_modelBoss[nCnt].pBuffMatModel != NULL)
		{//	BUFFMAT RELEASE
			g_modelBoss[nCnt].pBuffMatModel->Release();
			g_modelBoss[nCnt].pBuffMatModel = NULL;
		}
		for (int nCntTEX = 0; nCntTEX < 10; nCntTEX++)
		{//	TEXTURE RELEASE
			if (g_modelBoss[nCnt].pTexture[nCntTEX] != NULL)
			{
				g_modelBoss[nCnt].pTexture[nCntTEX]->Release();
				g_modelBoss[nCnt].pTexture[nCntTEX] = NULL;
			}
		}
	}

	for (int nCnt = 0; nCnt < g_Boss.aModel[0].nNumModel; nCnt++)
	{
		if (g_Boss.aModel[nCnt].pMeshModel != NULL)
		{//	MESH RELEASE
			g_Boss.aModel[nCnt].pMeshModel->Release();
			g_Boss.aModel[nCnt].pMeshModel = NULL;
		}
		if (g_Boss.aModel[nCnt].pBuffMatModel != NULL)
		{//	BUFFMAT RELEASE
			g_Boss.aModel[nCnt].pBuffMatModel->Release();
			g_Boss.aModel[nCnt].pBuffMatModel = NULL;
		}
		for (int nCntTEX = 0; nCntTEX < 10; nCntTEX++)
		{//	TEXTURE RELEASE
			if (g_Boss.aModel[nCnt].pTexture[nCntTEX] != NULL)
			{
				g_Boss.aModel[nCnt].pTexture[nCntTEX]->Release();
				g_Boss.aModel[nCnt].pTexture[nCntTEX] = NULL;
			}
		}
	}
}


//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateBoss(void)
{
	StartMotion(SELECTMOTION_BOSS, MOTIONTYPE_BOSS_NEUTRAL, NULL);	// とりあえずニュートラルさせとく

	//ボスとプレイヤーの移動当たり判定
	ColPlayerBoxThing(g_Boss.pos, g_Boss.fWidth, g_Boss.fDepth);
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得

	//ロボットタイプの敵描画
		if (g_Boss.bUse == true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得
			D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
			D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
			D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
			D3DXMATERIAL *pMatAlt;														// 代えのマテリアル

			//プレイヤーのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Boss.mtxWorld);

			//プレイヤーの向き反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Boss.rot.y, g_Boss.rot.x, g_Boss.rot.z);
			D3DXMatrixMultiply(&g_Boss.mtxWorld, &g_Boss.mtxWorld, &mtxRot);

			//プレイヤーの位置反映
			D3DXMatrixTranslation(&mtxTrans, g_Boss.pos.x, g_Boss.pos.y, g_Boss.pos.z);
			D3DXMatrixMultiply(&g_Boss.mtxWorld, &g_Boss.mtxWorld, &mtxTrans);

			//プレイヤーのワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Boss.mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_Boss.aModel[0].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
				D3DXMATRIX mtxParent;					// 親のマトリックス

				//各パーツのワールドマトリックス初期化
				D3DXMatrixIdentity(&g_Boss.aModel[nCntModel].mtxWorld);

				//各パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Boss.aModel[nCntModel].rot.y, g_Boss.aModel[nCntModel].rot.x, g_Boss.aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModel].mtxWorld, &g_Boss.aModel[nCntModel].mtxWorld, &mtxRotModel);

				//各パーツの位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_Boss.aModel[nCntModel].pos.x, g_Boss.aModel[nCntModel].pos.y, g_Boss.aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModel].mtxWorld, &g_Boss.aModel[nCntModel].mtxWorld, &mtxTransModel);

				//各パーツの親のマトリックスを設定
				if (g_Boss.aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_Boss.aModel[g_Boss.aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_Boss.mtxWorld;	// プレイヤーのマトリックスを設定
				}

				//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModel].mtxWorld, &g_Boss.aModel[nCntModel].mtxWorld, &mtxParent);

				//各パーツのワールドマトリックス設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Boss.aModel[nCntModel].mtxWorld);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Boss.aModel[nCntModel].pBuffMatModel->GetBufferPointer();
				pMatAlt = (D3DXMATERIAL*)g_Boss.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

				//無敵状態か見てモデルの色を変える
				if (g_Boss.bInvincible == true)
				{//無敵状態
					pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_Boss.aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//マテリアル設定
						pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_Boss.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
				else if (g_Boss.bInvincible == false)
				{//通常状態
					pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_Boss.aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//マテリアル設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_Boss.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
}

//-----------------------------------------------------------------------------
// ボス情報の取得
//-----------------------------------------------------------------------------
Boss *GetBoss(void)
{
	return &g_Boss;
}

//-----------------------------------------------------------------------------
// bossを配置する
//-----------------------------------------------------------------------------
void SetBoss(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	if (g_Boss.bUse == false)
	{
		//位置を指定
		g_Boss.pos = pos;

		//種類付け
		g_Boss.type = type;

		switch (type)
		{
		case ENEMYTYPE_BOSS:
			//パーツ情報を渡す
			for (int nCntRobot = 0; nCntRobot < ENEMY_ROBOT_MODELPARTS; nCntRobot++) g_Boss.aModel[nCntRobot] = g_modelBoss[nCntRobot];
			for (int nCnt = 0; nCnt < ENEMY_ROBOT_MODELPARTS; nCnt++)
			{
				g_Boss.DefKey[nCnt] = KeyPosRot(g_modelBoss[nCnt].pos.x, g_modelBoss[nCnt].pos.y, g_modelBoss[nCnt].pos.z, 0, 0, 0);
				g_Boss.aModel[nCnt].nNumModel = g_modelBoss[nCnt].nNumModel;
			}
			g_Boss.fWidth = BOSS_COL_WIDTH;
			g_Boss.fDepth = BOSS_COL_WIDTH;
			g_Boss.fHeight = BOSS_COL_HEIGHT;
			//初期キー

			break;
		}

		//使用中に移行
		g_Boss.bUse = true;
	}
}


/* Xファイルからモデルを読み込む関数*/
void LoadXFileBoss(const char* cXFileName, Model *model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	//Xファイルの読み込み
	HRESULT hr = D3DXLoadMeshFromX(
		cXFileName,										// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,								// 固定
		pDevice,										// デバイス
		NULL,											// NULL固定
		&model->pBuffMatModel,							// マテリアル
		NULL,											// NULL固定
		&model->nNumMatModel,							// マテリアル数
		&model->pMeshModel);							// メッシュ

	//マテリアル情報へのポインタ
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)model->pBuffMatModel->GetBufferPointer();

	//テクスチャを取得
	//for (int nCntMat = 0; nCntMat < (int)model->nNumMatModel; nCntMat++)
	//{
	//	D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &model->pTexture[nCntMat]);
	//}
}