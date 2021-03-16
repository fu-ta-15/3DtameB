#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// 敵の処理 [enemy.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "portal.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void MoveEnemy(float fMoveAngleDegree, float fMoveSpeed);
void LoadXFileEnemy(const char* cXFileName, PlayerModel *model);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Enemy g_aEnemy[ENEMY_AMOUNT_MAX];	// 敵の情報
int g_nEnemyAlive = 0;				// 敵の生存数

CharacterPartsInfo g_partsRobot;	// 読み込んだパーツ情報(ロボット)
KEY g_defKeyRobot[ENEMY_ROBOT_MODELPARTS];					//

PlayerModel g_modelSnake;			// 蛇のモデル情報
PlayerModel g_modelRobot[ENEMY_ROBOT_MODELPARTS];			// ロボットのモデル情報

bool g_bEliminated;					// 全滅したか
DWORD g_dwTimeTransition;			// 画面遷移時間計算

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//Xファイルの読み込み
	LoadXFileEnemy("data\\MODEL\\snake.x", &g_modelSnake);

	//テキストから読み込み
	ReadCharacterInfo(&g_partsRobot, "model_robot.txt");

	//読み込んだ情報を使ってXファイル読み込み
	for (int nCntModel = 0; nCntModel < g_partsRobot.nModelNum; nCntModel++)
	{
		LoadXFileEnemy(&g_partsRobot.cModelFileName[nCntModel][0], &g_modelRobot[nCntModel]);
	}

	//各パーツの階層構造設定
	for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
	{
		g_modelRobot[nCntModel].nNumModel = g_partsRobot.nModelNum;
		g_modelRobot[nCntModel].nIdxModelParent = g_partsRobot.nModelParent[nCntModel];
		g_modelRobot[nCntModel].pos = D3DXVECTOR3(g_partsRobot.fModelPos[nCntModel][0], g_partsRobot.fModelPos[nCntModel][1], g_partsRobot.fModelPos[nCntModel][2]);
		g_modelRobot[nCntModel].rot = D3DXVECTOR3(g_partsRobot.fModelRot[nCntModel][0], g_partsRobot.fModelRot[nCntModel][1], g_partsRobot.fModelRot[nCntModel][2]);
	}

	//初期キー
	for (int nCnt = 0; nCnt < ENEMY_ROBOT_MODELPARTS; nCnt++)
	{
		g_defKeyRobot[nCnt] = KeyPosRot(g_modelRobot[nCnt].pos.x, g_modelRobot[nCnt].pos.y, g_modelRobot[nCnt].pos.z, 0, 0, 0);
	}

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//初期設定
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].bInvincible = false;
		g_aEnemy[nCntEnemy].nLife = ENEMY_HP_MAX;
		g_aEnemy[nCntEnemy].nLifeMax = ENEMY_HP_MAX;
		g_aEnemy[nCntEnemy].bHit = false;
		g_aEnemy[nCntEnemy].bAttack = false;
		g_aEnemy[nCntEnemy].dwTimeAtk = NULL;
		g_aEnemy[nCntEnemy].dwTimeInv = NULL;
		g_aEnemy[nCntEnemy].nIdx = NULL;
	}
	g_nEnemyAlive = 0;
	g_dwTimeTransition = NULL;
	g_bEliminated = false;

	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 250.0f), ENEMYTYPE_ROBOT);
	SetEnemy(D3DXVECTOR3(50.0f, 0.0f, 250.0f), ENEMYTYPE_SNAKE);
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitEnemy(void)
{
	//蛇のマテリアル開放
	if (g_modelSnake.pBuffMatModel != NULL)
	{
		g_modelSnake.pBuffMatModel->Release();
		g_modelSnake.pBuffMatModel = NULL;
	}
	//蛇のメッシュ開放
	if (g_modelSnake.pMeshModel != NULL)
	{
		g_modelSnake.pMeshModel->Release();
		g_modelSnake.pMeshModel = NULL;
	}
	//蛇のテクスチャ開放
	for (int nCntTex = 0; nCntTex < 10; nCntTex++)
	{
		if (g_modelSnake.pTexture[nCntTex] != NULL)
		{
			g_modelSnake.pTexture[nCntTex]->Release();
			g_modelSnake.pTexture[nCntTex] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateEnemy(void)
{
	DWORD dwCurrentTime = timeGetTime();	// 現在時間

	//使用中の敵を探す
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			Player *pPlayer = GetPlayer();	// プレイヤーの取得

			//移動量追加
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			//移動量減衰
			g_aEnemy[nCntEnemy].move.x = g_aEnemy[nCntEnemy].move.x * 0.2f;
			g_aEnemy[nCntEnemy].move.z = g_aEnemy[nCntEnemy].move.z * 0.2f;

			//重力
			g_aEnemy[nCntEnemy].move.y -= ENEMY_FALLSPEED;

			if (g_aEnemy[nCntEnemy].pos.y < 0) g_aEnemy[nCntEnemy].pos.y = 0;

			//体力なくなったら
			if (g_aEnemy[nCntEnemy].nLife <= 0)
			{
				//使用状況を切り替える
				g_aEnemy[nCntEnemy].bUse = false;

				//生存数を減算
				g_nEnemyAlive--;
			}

			//モーション管理
			if (g_aEnemy[nCntEnemy].move.x != 0.0f || g_aEnemy[nCntEnemy].move.z != 0.0f)
			{
				StartMotion(SELECTMOTION_ENEMY, MOTIONTYPE_WALK, nCntEnemy);
			}
			else
			{
				StartMotion(SELECTMOTION_ENEMY, MOTIONTYPE_NEUTRAL, nCntEnemy);
			}

			//プレイヤーとの距離
			float fDistanceToPlayer = sqrtf((pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x) * ((pPlayer->pos.x) - g_aEnemy[nCntEnemy].pos.x) + (pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z) * (pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z));

			//距離が検知範囲以内だったら
			if (fDistanceToPlayer <= ENEMY_DETECT_RADIUS)
			{
				//プレイヤーに向かう単位ベクトル
				D3DXVECTOR3 vecToPlayer = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
				D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

				//移動を加算
				g_aEnemy[nCntEnemy].move += vecToPlayer * ENEMY_MOVESPEED;

				//プレイヤーへのラジアン角
				float fRadianToPlayer = atan2f(g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x, g_aEnemy[nCntEnemy].pos.z - pPlayer->pos.z);
				g_aEnemy[nCntEnemy].rot.y = fRadianToPlayer;
			}

			//距離が攻撃範囲内だったら
			if (fDistanceToPlayer <= ENEMY_ATTACK_RADIUS)
			{
				//すでに攻撃していない場合
				if (g_aEnemy[nCntEnemy].bAttack != true)
				{
					//プレイヤーの無敵時間じゃない場合
					if (pPlayer->bInvincible != true)
					{
						//現在時間取得（無敵時間計算）
						g_aEnemy[nCntEnemy].dwTimeAtk = timeGetTime();

						//現在時間取得（攻撃CT計算）
						pPlayer->dwTime = timeGetTime();

						//体力減少
						pPlayer->nLife--;

						//敵から自分に向かうベクトル
						D3DXVECTOR3 vecEnemyToPlayer = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
						D3DXVec3Normalize(&vecEnemyToPlayer, &vecEnemyToPlayer);

						//ノックバック
						pPlayer->move += vecEnemyToPlayer * ENEMY_KNOCKBACK;
						pPlayer->move.y += 1.0f;

						//無敵になる
						pPlayer->bInvincible = true;

						//敵が攻撃クールタイムに入る
						g_aEnemy[nCntEnemy].bAttack = true;
					}
				}
			}

			//時間経過で攻撃CT解除
			if (dwCurrentTime - g_aEnemy[nCntEnemy].dwTimeAtk >= ENEMY_ATTACK_COOLTIME)
			{
				//CT解除
				g_aEnemy[nCntEnemy].bAttack = false;
			}
			
			//敵が全滅したら
			if (g_nEnemyAlive <= 0)
			{
				//ポータルを起動
				ActivatePortal(true, true);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得

	//蛇タイプの敵描画
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].type == ENEMYTYPE_SNAKE)
		{
			D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
			D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
			D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
			D3DXMATERIAL *pMatAlt;														// 代えのマテリアル

			//プレイヤーのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//プレイヤーの向き反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//プレイヤーの位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//プレイヤーのワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_modelSnake.pBuffMatModel->GetBufferPointer();
			pMatAlt = (D3DXMATERIAL*)g_modelSnake.pBuffMatModel->GetBufferPointer();

			//無敵状態か見てモデルの色を変える
			if (g_aEnemy[nCntEnemy].bInvincible == true)
			{//無敵状態
				pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				for (int nCntMat = 0; nCntMat < (int)g_modelSnake.nNumMatModel; nCntMat++)
				{
					//マテリアル設定
					pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_modelSnake.pTexture[nCntMat]);

					//モデルパーツの描画
					g_modelSnake.pMeshModel->DrawSubset(nCntMat);
				}
			}
			else if (g_aEnemy[nCntEnemy].bInvincible == false)
			{//通常状態
				pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
				for (int nCntMat = 0; nCntMat < (int)g_modelSnake.nNumMatModel; nCntMat++)
				{
					//マテリアル設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_modelSnake.pTexture[nCntMat]);

					//モデルパーツの描画
					g_modelSnake.pMeshModel->DrawSubset(nCntMat);
				}
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}

	//ロボットタイプの敵描画
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].type == ENEMYTYPE_ROBOT)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得
			D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
			D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
			D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
			D3DXMATERIAL *pMatAlt;														// 代えのマテリアル

			//プレイヤーのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//プレイヤーの向き反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//プレイヤーの位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//プレイヤーのワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
				D3DXMATRIX mtxParent;					// 親のマトリックス

				//各パーツのワールドマトリックス初期化
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//各パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//各パーツの位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//各パーツの親のマトリックスを設定
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;	// プレイヤーのマトリックスを設定
				}

				//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//各パーツのワールドマトリックス設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMatModel->GetBufferPointer();
				pMatAlt = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMatModel->GetBufferPointer();

				//無敵状態か見てモデルの色を変える
				if (g_aEnemy[nCntEnemy].bInvincible == true)
				{//無敵状態
					pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//マテリアル設定
						pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_aEnemy[nCntEnemy].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
				else if (g_aEnemy[nCntEnemy].bInvincible == false)
				{//通常状態
					pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//マテリアル設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_aEnemy[nCntEnemy].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
			}


			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------------------
// プレイヤーの情報を取得
//-----------------------------------------------------------------------------
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//-----------------------------------------------------------------------------
// パーツ情報を取得
//-----------------------------------------------------------------------------
PlayerModel *GetEnemyModelParts(ENEMYTYPE type)
{
	switch (type)
	{
	case ENEMYTYPE_SNAKE:
		return &g_modelSnake;
		break;

	case ENEMYTYPE_ROBOT:
		return &g_modelRobot[0];
		break;

	default:
		return NULL;
		break;
	}
}

//-----------------------------------------------------------------------------
// 敵を配置する
//-----------------------------------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//位置を指定
			g_aEnemy[nCntEnemy].pos = pos;

			//番号付け
			g_aEnemy[nCntEnemy].nIdx = nCntEnemy;

			//種類付け
			g_aEnemy[nCntEnemy].type = type;

			//パーツ情報を渡す
			switch (type)
			{
			case ENEMYTYPE_SNAKE:
				break;

			case ENEMYTYPE_ROBOT:
				for (int nCntRobot = 0; nCntRobot < ENEMY_ROBOT_MODELPARTS; nCntRobot++)
				{
					g_aEnemy[nCntEnemy].aModel[nCntRobot] = g_modelRobot[nCntRobot];
				}
				break;

			default:
				break;
			}

			//生存数に加算
			g_nEnemyAlive++;

			//使用中に移行
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}
}

/* モデルを移動させる関数 */
void MoveEnemy(float fMoveAngleDegree, float fMoveSpeed)
{
	/*Camera *pCamera = GetCamera();	// カメラの情報取得

	g_enemy.pos.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_enemy.pos.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_enemy.rotDest.y = pCamera->rot.y + D3DXToRadian(fMoveAngleDegree) + D3DX_PI;*/
}

/* Xファイルからモデルを読み込む関数*/
void LoadXFileEnemy(const char* cXFileName, PlayerModel *model)
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

	if (hr != S_OK)
	{
		Sleep(10);
	}
	//マテリアル情報へのポインタ
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)model->pBuffMatModel->GetBufferPointer();

	//テクスチャを取得
	for (int nCntMat = 0; nCntMat < (int)model->nNumMatModel; nCntMat++)
	{
		D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &model->pTexture[nCntMat]);
	}
}