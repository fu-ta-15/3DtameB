#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// プレイヤーの処理 [player.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "player.h"
#include "camera.h"
#include "input.h"
#include "meshfield.h"
#include "fade.h"
#include "result.h"
#include "motion.h"
#include "enemy.h"
#include "commandaction.h"
#include "bullet.h"
#include "Dinput.h"

#include <stdio.h>
#include <time.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_SMOOTHTURN_SPEED (0.1f)											// 滑らかに振り向く速度
#define PLAYER_SMOOTHTURN_SPEED_ATK (0.02f)

#define READROW (1028)	// ファイル読み込みで読む最大数

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed);
HRESULT LoadXFile(const char* cXFileName, Model *modelInfo);
void PlayerSmoothTurn(void);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Player g_player;																		// プレイヤーの情報
KEY g_playerDefaultKey[PLAYER_MODEL_AMOUNT];
CharacterPartsInfo g_ModelInfo;															// 読み込んだモデルの情報

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//プレイヤーの初期設定
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
	g_player.bHit = false;
	g_player.bInvincible = false;
	g_player.dwTime = NULL;
	g_player.nLife = PLAYER_HEALTH;
	g_player.nLifeMax = PLAYER_HEALTH;

	//テキスト読み込み
	ReadCharacterInfo(&g_ModelInfo, "data\\TXT\\motion_team_model1.txt");

	//読み込んだ情報を使ってXファイル読み込み
	for (int nCntModel = 0; nCntModel < g_ModelInfo.nModelNum; nCntModel++)
	{
		LoadXFile(&g_ModelInfo.cModelFileName[nCntModel][0], &g_player.aModel[nCntModel]);
	}

	//モデルのパーツ数
	g_player.nNumModel = g_ModelInfo.nModelNum;

	//各パーツの階層構造設定
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		g_player.aModel[nCntModel].nIdxModelParent = g_ModelInfo.nModelParent[nCntModel];
		g_player.aModel[nCntModel].pos = D3DXVECTOR3(g_ModelInfo.fModelPos[nCntModel][0], g_ModelInfo.fModelPos[nCntModel][1], g_ModelInfo.fModelPos[nCntModel][2]);
		g_player.aModel[nCntModel].rot = D3DXVECTOR3(g_ModelInfo.fModelRot[nCntModel][0], g_ModelInfo.fModelRot[nCntModel][1], g_ModelInfo.fModelRot[nCntModel][2]);
	}

	//初期キー
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		g_playerDefaultKey[nCnt] = KeyPosRot(g_player.aModel[nCnt].pos.x, g_player.aModel[nCnt].pos.y, g_player.aModel[nCnt].pos.z, 0, 0, 0);
	}

	LoadXFile("data//MODEL//naginata_fix.x", &g_player.AltWeapon);

	g_player.weaponPos = D3DXVECTOR3(-1.0f, -0.5f, 0.0f);
	g_player.weaponRot = D3DXVECTOR3(0.0f, 1.5f, -1.6f);

	g_player.posWeaponCol[0] = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.posWeaponCol[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_player.posWeaponCol[2] = D3DXVECTOR3(0.0f, 45.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < PLAYER_MODEL_AMOUNT; nCntModel++)
	{
		//メッシュの破棄
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	DWORD dwCurrentTime = timeGetTime();	// 現在時間
	DIJOYSTATE2 *pController = pGetPadCont();

	//位置保存
	g_player.posOld = g_player.pos;

	//移動量追加
	g_player.pos += g_player.move;

	//移動量減衰
	g_player.move.x += (0 - g_player.move.x) * 0.2f;
	g_player.move.z += (0 - g_player.move.z) * 0.2f;

	//重力
	g_player.move.y -= 0.2f;

	//移動制限
	//if (g_player.pos.x > FIELD_MAXSIZE) g_player.pos.x = FIELD_MAXSIZE;
	//if (g_player.pos.x < -FIELD_MAXSIZE) g_player.pos.x = -FIELD_MAXSIZE;
	//if (g_player.pos.z > FIELD_MAXSIZE) g_player.pos.z = FIELD_MAXSIZE;
	//if (g_player.pos.z < -FIELD_MAXSIZE) g_player.pos.z = -FIELD_MAXSIZE;
	if (g_player.pos.y <= 0.0f)
	{
		g_player.move.y = 0.0f;
		g_player.pos.y = 0.0f;
	}

	/* モデルの移動 */
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_D) == true) MovePlayer(D3DXToRadian(45.0f), PLAYER_MOVESPEED);			// 右前
		else if (GetKeyboardPress(DIK_A) == true) MovePlayer(D3DXToRadian (-45.0f), PLAYER_MOVESPEED);		// 左前
		else MovePlayer(0.0f, PLAYER_MOVESPEED);												// 前
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_D) == true) MovePlayer(D3DXToRadian(135.0f), PLAYER_MOVESPEED);			// 右後ろ
		else if (GetKeyboardPress(DIK_A) == true) MovePlayer(D3DXToRadian(-135.0f), PLAYER_MOVESPEED);		// 左後ろ
		else MovePlayer(D3DXToRadian(-180.0f), PLAYER_MOVESPEED);												// 後ろ
	}
	else if (GetKeyboardPress(DIK_A) == true) MovePlayer(D3DXToRadian(-90.0f), PLAYER_MOVESPEED);			// 左
	else if (GetKeyboardPress(DIK_D) == true) MovePlayer(D3DXToRadian(90.0f), PLAYER_MOVESPEED);			// 右

	/* プレイヤーの振り向きを滑らかにする */
	PlayerSmoothTurn();

	//行動にモーションつける
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	if (g_player.weapon == PWEAPON_KATANA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_KATANA_ATTACK, NULL);
	//	else if (g_player.weapon == PWEAPON_NAGINATA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NAGINATA_ATTACK, NULL);
	//}
	//else if (GetKeyboardPress(DIK_W) ||
	//	GetKeyboardPress(DIK_S) ||
	//	GetKeyboardPress(DIK_A) ||
	//	GetKeyboardPress(DIK_D) == true)
	//{
	//	StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_WALK, NULL);
	//}
	//else
	//{
	//	StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NEUTRAL, NULL);
	//}

	if (pController->lX != 0 || pController->lY != 0)
	{//	スティックが傾いた時
		float fAngle = atan2f((float)pController->lX, -(float)pController->lY);
		MovePlayer(fAngle, PLAYER_MOVESPEED);

		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_WALK, NULL);
	}
	else
	{
		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NEUTRAL, NULL);
	}
	if (GetKeypadTrigger(D_BUUTON_A))
	{
		if (g_player.weapon == PWEAPON_KATANA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_KATANA_ATTACK, NULL);
		else if (g_player.weapon == PWEAPON_NAGINATA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NAGINATA_ATTACK, NULL);
	}


	//攻撃中は移動０にする
	if (g_player.motionType == MOTIONTYPE_CYBORG_KATANA_ATTACK ||
		g_player.motionType == MOTIONTYPE_CYBORG_NAGINATA_ATTACK)
	{
		g_player.move = D3DXVECTOR3(0, 0, 0);
	}

	//時間経過で無敵時間解除
	if (dwCurrentTime - g_player.dwTime >= PLAYER_INVINCIBLE_TIME)
	{
		//無敵解除
		g_player.bInvincible = false;
	}


	if (GetKeyboardTrigger(DIK_H) == true)
	{
		if (g_player.weapon == PWEAPON_KATANA) g_player.weapon = PWEAPON_NAGINATA;
		else if (g_player.weapon == PWEAPON_NAGINATA) g_player.weapon = PWEAPON_KATANA;
	}
	if (GetKeypadTrigger(D_BUUTON_RB))
	{
		if (g_player.weapon == PWEAPON_KATANA) g_player.weapon = PWEAPON_NAGINATA;
		else if (g_player.weapon == PWEAPON_NAGINATA) g_player.weapon = PWEAPON_KATANA;
	}

}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得
	D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
	D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ

	//プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//プレイヤーの向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//プレイヤーの位置反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//プレイヤーのワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//モデルパーツ
	for (int nCntModel = 0; nCntModel < g_player.nNumModel - 1; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
		D3DXMATRIX mtxParent;					// 親のマトリックス

		//各パーツのワールドマトリックス初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//各パーツの親のマトリックスを設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;	// プレイヤーのマトリックスを設定
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		//無敵状態か見てモデルの色を変える
		if (g_player.bInvincible == true)
		{//無敵状態
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				D3DXMATERIAL matDef[20];

				matDef[nCntMat] = pMat[nCntMat];

				pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);

				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデルパーツの描画
				g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);

				pMat[nCntMat] = matDef[nCntMat];
			}
		}
		else if (g_player.bInvincible == false)
		{//通常状態
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				//pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);

				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデルパーツの描画
				g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//武器パーツ
	D3DXMATRIX mtxRotWpn, mtxTransWpn;	// 計算用
	D3DXMATRIX mtxParentWpn;			// 親のマトリクス

	if (g_player.weapon == PWEAPON_KATANA)
	{
		//各パーツのワールドマトリックス初期化
		D3DXMatrixIdentity(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxRotWpn);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxTransWpn);

		//親マトリクス設定
		mtxParentWpn = g_player.aModel[g_player.aModel[PLAYER_MODEL_AMOUNT - 1].nIdxModelParent].mtxWorld;

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxParentWpn);

		//各パーツのワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pBuffMatModel->GetBufferPointer();

		//マテリアル設定と描画
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[PLAYER_MODEL_AMOUNT - 1].nNumMatModel; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデルパーツの描画
			g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pMeshModel->DrawSubset(nCntMat);
		}
	}
	else if (g_player.weapon == PWEAPON_NAGINATA)
	{
		//各パーツのワールドマトリックス初期化
		D3DXMatrixIdentity(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxRotWpn);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxTransWpn);

		//親マトリクス設定
		mtxParentWpn = g_player.aModel[g_player.aModel[PLAYER_MODEL_AMOUNT - 1].nIdxModelParent].mtxWorld;

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxParentWpn);

		//各パーツのワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.AltWeapon.pBuffMatModel->GetBufferPointer();

		//マテリアル設定と描画
		for (int nCntMat = 0; nCntMat < (int)g_player.AltWeapon.nNumMatModel; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデルパーツの描画
			g_player.AltWeapon.pMeshModel->DrawSubset(nCntMat);
		}
	}


	//test
	for (int nCntCol = 0; nCntCol < PLAYER_WEAPON_COLLISION_COMPONENTS; nCntCol++)
	{
		//武器パーツ
		D3DXMATRIX mtxRotWpnC, mtxTransWpnC;	// 計算用
		D3DXMATRIX mtxParentWpnC;			// 親のマトリクス

		//各パーツのワールドマトリックス初期化
		D3DXMatrixIdentity(&g_player.mtxWeaponCol[nCntCol]);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransWpnC, g_player.posWeaponCol[nCntCol].x, g_player.posWeaponCol[nCntCol].y, g_player.posWeaponCol[nCntCol].z);
		D3DXMatrixMultiply(&g_player.mtxWeaponCol[nCntCol], &g_player.mtxWeaponCol[nCntCol], &mtxTransWpnC);

		//親マトリクス設定
		mtxParentWpnC = g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld;

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.mtxWeaponCol[nCntCol], &g_player.mtxWeaponCol[nCntCol], &mtxParentWpnC);

		//各パーツのワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWeaponCol[nCntCol]);
	}


	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

//-----------------------------------------------------------------------------
// プレイヤーの情報を取得
//-----------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;
}
//-----------------------------------------------------------------------------
// モデルの初期状態を取得
//-----------------------------------------------------------------------------
KEY *GetDefKey(void)
{
	return &g_playerDefaultKey[0];
}

/* モデルを移動させる関数 */
void MovePlayer(float fMoveRad, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// カメラの情報取得

	g_player.move.x += sinf(pCamera->rot.y + fMoveRad) * fMoveSpeed;
	g_player.move.z += cosf(pCamera->rot.y + fMoveRad) * fMoveSpeed;
	g_player.rotDest.y = pCamera->rot.y + fMoveRad + D3DX_PI;
}

/* Xファイルからモデルを読み込む関数*/
HRESULT LoadXFile(const char* cXFileName, Model *modelInfo)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得
	HRESULT hres;

	//Xファイルの読み込み
	hres = D3DXLoadMeshFromX(
		cXFileName,										// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,								// 固定
		pDevice,										// デバイス
		NULL,											// NULL固定
		&modelInfo->pBuffMatModel,						// マテリアル
		NULL,											// NULL固定
		&modelInfo->nNumMatModel,						// マテリアル数
		&modelInfo->pMeshModel);						// メッシュ
	return hres;
}

/* キャラの回転を滑らかにする関数 */
void PlayerSmoothTurn(void)
{
	D3DXVECTOR3 RotDiff;
	float fTurnSpeed;

	if (g_player.motionType == MOTIONTYPE_ATTACK) fTurnSpeed = PLAYER_SMOOTHTURN_SPEED_ATK;
	else if (g_player.motionType == MOTIONTYPE_CYBORG_KATANA_ATTACK) fTurnSpeed = PLAYER_SMOOTHTURN_SPEED_ATK;
	else if (g_player.motionType == MOTIONTYPE_CYBORG_NAGINATA_ATTACK) fTurnSpeed = PLAYER_SMOOTHTURN_SPEED_ATK;
	else fTurnSpeed = PLAYER_SMOOTHTURN_SPEED;

	//差分計算
	RotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//差分がD3DX_PI以上(半周以上)の場合、逆回転
	if (RotDiff.y > D3DX_PI)
	{
		g_player.rot.y -= ((D3DX_PI * 2) - RotDiff.y) * fTurnSpeed;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		g_player.rot.y += ((D3DX_PI * 2) + RotDiff.y) * fTurnSpeed;
	}
	else
	{
		g_player.rot.y += RotDiff.y * fTurnSpeed;
	}

	// 回転の修正 (3.14超えたら±逆に)
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_player.rotDest.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
}

/* キャラクターのモデル情報を読み込む関数 */
void ReadCharacterInfo(CharacterPartsInfo *characterInfo, char* fileName)
{
	FILE *pFile;
	char cCharRead[READROW][128];
	char cEqual[2];

	int nCountModelNum = 0;
	int nCountModelIdx = 0;
	int nCountModelParent = 0;
	int nCountModelPos = 0;
	int nCountModelRot = 0;

	pFile = fopen(fileName, "r");
	if (pFile != NULL)
	{
		//1028行探す
		for (int nCntRow = 0; nCntRow < READROW; nCntRow++)
		{
			//文字列読み込み
			fscanf(pFile, "%s", &cCharRead[nCntRow][0]);

			//SCRIPTの文字列を見つけたら
			if (strcmp(&cCharRead[nCntRow][0], "SCRIPT") == 0)
			{
				for (int nCntRow = 0; nCntRow < READROW; nCntRow++)
				{
					//次の文字列読み込み
					fscanf(pFile, "%s", &cCharRead[nCntRow][0]);

					if (strcmp(&cCharRead[nCntRow][0], "NUM_MODEL") == 0)
					{
						//次の文字列
						fscanf(pFile, "%s", &cEqual[0]);

						//イコール見つかったら
						if (strcmp(&cEqual[0], "=") == 0)
						{
							//イコールの次の整数を変数に入れる
							fscanf(pFile, "%d", &characterInfo->nModelNum);
						}
					}

					if (strcmp(&cCharRead[nCntRow][0], "MODEL_FILENAME") == 0)
					{
						//次の文字列
						fscanf(pFile, "%s", &cEqual[0]);

						//イコール見つけたら
						if (strcmp(&cEqual[0], "=") == 0)
						{
							//イコールの次の文字列を配列に入れる
							fscanf(pFile, "%s", &characterInfo->cModelFileName[nCountModelNum][0]);

							//カウントアップ
							nCountModelNum++;
						}
					}

					if (strcmp(&cCharRead[nCntRow][0], "CHARACTERSET") == 0)
					{
						for (int nCntCSET = 0; nCntCSET < READROW; nCntCSET++)
						{
							fscanf(pFile, "%s", &cCharRead[nCntCSET][0]);

							//PARTSSET見つけた
							if (strcmp(&cCharRead[nCntCSET][0], "PARTSSET") == 0)
							{
								for (int nCntPSET = 0; nCntCSET < READROW; nCntCSET++)
								{
									fscanf(pFile, "%s", &cCharRead[nCntCSET][0]);

									//INDEX
									if (strcmp(&cCharRead[nCntCSET][0], "INDEX") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											fscanf(pFile, "%d", &characterInfo->nModelIdx[nCountModelIdx]);

											nCountModelIdx++;
										}
									}

									//PARENT
									if (strcmp(&cCharRead[nCntCSET][0], "PARENT") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											fscanf(pFile, "%d", &characterInfo->nModelParent[nCountModelParent]);

											nCountModelParent++;
										}
									}

									//POS
									if (strcmp(&cCharRead[nCntCSET][0], "POS") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											for (int nCntVector3 = 0; nCntVector3 < 3; nCntVector3++)
											{
												fscanf(pFile, "%f", &characterInfo->fModelPos[nCountModelPos][nCntVector3]);
											}
											nCountModelPos++;
										}
									}

									//ROT
									if (strcmp(&cCharRead[nCntCSET][0], "ROT") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											for (int nCntVector3 = 0; nCntVector3 < 3; nCntVector3++)
											{
												fscanf(pFile, "%f", &characterInfo->fModelRot[nCountModelRot][nCntVector3]);
											}
											nCountModelRot++;
										}
									}

									//END_PARTSSET見つけたらループ抜ける
									if (strcmp(&cCharRead[nCntCSET][0], "END_PARTSSET") == 0)
									{
										break;
									}
								}
							}

							//END_CHARACTERSET見つけたらループ抜ける
							if (strcmp(&cCharRead[nCntCSET][0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}
					}
				}
				break;
			}
		}
	}
}