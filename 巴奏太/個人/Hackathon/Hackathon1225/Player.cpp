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
#include "Xinput.h"
#include <stdio.h>

//----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_MODEL_AMOUNT (10)
#define PLAYER_SMOOTHTURN_SPEED (0.1f)											// 滑らかに振り向く速度

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed);
void LoadXFile(const char* cXFileName, int nCountModel);
KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
void PlayerSmoothTurn(void);
void PlayMotion(bool bPlayMotion);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Player g_player;																// プレイヤーの情報
D3DXVECTOR3 g_MotionKey[4][10];													// モーションのキー
bool g_bMotionStart;															// モーション開始
int g_nMotionNum;																// 現在のモーション

void SetPlayer(void)
{
	g_player.nScore = 0;
	g_player.nHp = 3;
	g_player.nTime = 90;
	g_player.bMotionStart = false;
	g_player.bHit = false;
	g_player.nCntHit = 0;
}
//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	SetPlayer();
	LoadXFile("data\\MODEL\\00_robot_body.x", 0);
	LoadXFile("data\\MODEL\\01_robot_head.x", 1);
	LoadXFile("data\\MODEL\\02_robot_armR.x", 2);
	LoadXFile("data\\MODEL\\03_robot_handR.x", 3);
	LoadXFile("data\\MODEL\\04_robot_armL.x", 4);
	LoadXFile("data\\MODEL\\05_robot_handL.x", 5);
	LoadXFile("data\\MODEL\\06_robot_legR.x", 6);
	LoadXFile("data\\MODEL\\07_robot_footR.x", 7);
	LoadXFile("data\\MODEL\\08_robot_legL.x", 8);
	LoadXFile("data\\MODEL\\09_robot_footL.x", 9);

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\Model\00_robot_body.x",					// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,								// 固定
		pDevice,										// デバイス
		NULL,											// NULL固定
		&g_player.aModel[0].pBuffMatModel,				// マテリアル
		NULL,											// NULL固定
		&g_player.aModel[0].nNumMatModel,				// マテリアル数
		&g_player.aModel[0].pMeshModel);				// メッシュ

	g_player.nNumModel = 10;

	//各パーツの階層構造設定
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-7.5f, 12.0f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[4].nIdxModelParent = 0;
	g_player.aModel[4].pos = D3DXVECTOR3(7.5f, 12.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[5].nIdxModelParent = 4;
	g_player.aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[6].nIdxModelParent = 0;
	g_player.aModel[6].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//プレイヤーの初期設定
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置の初期設定
	g_player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);		// 向きの初期設定
	g_player.rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// 向きの目標初期設定

															//モーションの設定
	g_player.nNumMotion = 2;

	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey = 2;
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].bLoop = true;
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].nFrame = 65;
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].nFrame = 65;

	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.75f, 1.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.22f, 0.79f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.22f, -0.79f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, -0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.18f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].nNumKey = 4;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].bLoop = false;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].nFrame = 10;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].nFrame = 10;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].nFrame = 10;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].nFrame = 30;

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.48f, 0.25f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.44f, -0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.97f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.07f, -1.17f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.85f, -0.35f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.4f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.5f, -0.35f, 0.13f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.59f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 0.35f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.66f, -0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.45f, -0.82f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 1.07f, -1.16f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.19f, -0.41f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.41f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.5f, -0.41f, 0.13f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.60f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.41f, -0.44f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.62f, 0.06f, -1.16f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, -0.44f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.13f, 0.47f, -1.16f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

	g_player.motionType = MOTIONTYPE_ATTACK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
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
	GAMEPAD *pPad = GetGamePad();

	/* モデルの移動
	if (GetkeyboardPress(DIK_UP) == true)
	{
	if (GetkeyboardPress(DIK_RIGHT) == true) MovePlayer(45.0f, PLAYER_MOVESPEED);			// 右前
	else if (GetkeyboardPress(DIK_LEFT) == true) MovePlayer(-45.0f, PLAYER_MOVESPEED);		// 左前
	else MovePlayer(0.0f, PLAYER_MOVESPEED);												// 前
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	}
	else if (GetkeyboardPress(DIK_DOWN) == true)
	{
	if (GetkeyboardPress(DIK_RIGHT) == true) MovePlayer(135.0f, PLAYER_MOVESPEED);			// 右後ろ
	else if (GetkeyboardPress(DIK_LEFT) == true) MovePlayer(-135.0f, PLAYER_MOVESPEED);		// 左後ろ
	else MovePlayer(-180.0f, PLAYER_MOVESPEED);												// 後ろ
	}
	else if (GetkeyboardPress(DIK_LEFT) == true) MovePlayer(-90.0f, PLAYER_MOVESPEED);			// 左
	else if (GetkeyboardPress(DIK_RIGHT) == true) MovePlayer(90.0f, PLAYER_MOVESPEED);			// 右
	*/

	/* プレイヤーの振り向きを滑らかにする */
	PlayerSmoothTurn();

	//Mキーでモーション開始
	if (GetkeyboardTrigger(DIK_M) == true || pPad->bA == true || pPad->bB == true || pPad->bX == true || pPad->bY == true || pPad->bStart)
	{
		g_bMotionStart = true;

		pPad->bA = false;
		pPad->bStart = false;
	}

	/* モーション再生 */
	PlayMotion(g_player.bMotionStart);

	//キャラの回転リセット
	if (GetkeyboardTrigger(DIK_N) == true)
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			g_player.aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		g_bMotionStart = false;
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

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
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

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデルパーツの描画
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
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

/* モデルを移動させる関数 */
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// カメラの情報取得

	g_player.pos.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_player.pos.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_player.rotDest.y = pCamera->rot.y + D3DXToRadian(fMoveAngleDegree) + D3DX_PI;
}

/* Xファイルからモデルを読み込む関数*/
void LoadXFile(const char* cXFileName, int nCountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

												//Xファイルの読み込み
	D3DXLoadMeshFromX(
		cXFileName,										// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,								// 固定
		pDevice,										// デバイス
		NULL,											// NULL固定
		&g_player.aModel[nCountModel].pBuffMatModel,		// マテリアル
		NULL,											// NULL固定
		&g_player.aModel[nCountModel].nNumMatModel,		// マテリアル数
		&g_player.aModel[nCountModel].pMeshModel);		// メッシュ
}

/* キーのPos,Rotを簡易的に入力させる関数*/
KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	KEY key;

	key.fPosX = posX;
	key.fPosY = posY;
	key.fPosZ = posZ;

	key.fRotX = rotX;
	key.fRotY = rotY;
	key.fRotZ = rotZ;

	return key;
}

/* キャラの回転を滑らかにする関数 */
void PlayerSmoothTurn(void)
{
	D3DXVECTOR3 RotDiff;

	//差分計算
	RotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//差分がD3DX_PI以上(半周以上)の場合、逆回転
	if (RotDiff.y > D3DX_PI)
	{
		g_player.rot.y -= ((D3DX_PI * 2) - RotDiff.y) * PLAYER_SMOOTHTURN_SPEED;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		g_player.rot.y += ((D3DX_PI * 2) + RotDiff.y) * PLAYER_SMOOTHTURN_SPEED;
	}
	else
	{
		g_player.rot.y += RotDiff.y * PLAYER_SMOOTHTURN_SPEED;
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

/* モーションの再生関数 */
void PlayMotion(bool bPlayMotion)
{
	if (bPlayMotion == true)
	{
		//ループ
		g_player.bLoopMotion = g_player.aMotionInfo[g_player.motionType].bLoop;

		//モーションカウントアップ
		g_player.nCounterMotion++;

		//モデル数分回す
		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			//差分計算用
			KEY keyDiff[20];

			//現在のキーと次のキーとの差分を計算
			if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey - 1 && g_player.bLoopMotion == true)
			{	// ループの場合
				keyDiff[nCntModel].fPosX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fPosX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosX;
				keyDiff[nCntModel].fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fPosY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosY;
				keyDiff[nCntModel].fPosZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosZ;
				keyDiff[nCntModel].fRotX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fRotX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotX;
				keyDiff[nCntModel].fRotY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fRotY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotY;
				keyDiff[nCntModel].fRotZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotZ;
			}
			else
			{	// それ以外
				keyDiff[nCntModel].fPosX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fPosX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosX;
				keyDiff[nCntModel].fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fPosY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosY;
				keyDiff[nCntModel].fPosZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fPosZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosZ;
				keyDiff[nCntModel].fRotX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fRotX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotX;
				keyDiff[nCntModel].fRotY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fRotY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotY;
				keyDiff[nCntModel].fRotZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fRotZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotZ;
			}

			//現在のキーに差分をモーションカウントで割った分を足したものをrotに代入
			//g_player.aModel[nCntModel].pos.x = g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosX + keyDiff[nCntModel].fPosX * (g_player.nCounterMotion / g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].nFrame);
			//g_player.aModel[nCntModel].pos.y = g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosY + keyDiff[nCntModel].fPosY * (g_player.nCounterMotion / g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].nFrame);
			//g_player.aModel[nCntModel].pos.z = g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosZ + keyDiff[nCntModel].fPosX * (g_player.nCounterMotion / g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].nFrame);
			g_player.aModel[nCntModel].rot.x = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotX + keyDiff[nCntModel].fRotX * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame);
			g_player.aModel[nCntModel].rot.y = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotY + keyDiff[nCntModel].fRotY * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame);
			g_player.aModel[nCntModel].rot.z = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotZ + keyDiff[nCntModel].fRotZ * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame);
		}

		//現在キーの再生フレーム数に到達したら
		if (g_player.nCounterMotion >= g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame)
		{
			//次のキーに
			g_player.nKey++;

			//モーションカウンタリセット
			g_player.nCounterMotion = 0;
		}

		//現在キーがモーションのキー数に到達したら
		if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey - 1 && g_player.bLoopMotion == false)
		{//ループしない場合

		 //モーション状態を終わる
			g_player.bMotionStart = false;

			//モーションカウンタリセット
			g_player.nCounterMotion = 0;

			//現在キーを初期化
			g_player.nKey = 0;

			for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
			{
				g_player.aModel[nCntModel].rot.x = g_player.aMotionInfo[0].aKeyInfo[0].aKey[nCntModel].fRotX;
				g_player.aModel[nCntModel].rot.y = g_player.aMotionInfo[0].aKeyInfo[0].aKey[nCntModel].fRotY;
				g_player.aModel[nCntModel].rot.z = g_player.aMotionInfo[0].aKeyInfo[0].aKey[nCntModel].fRotZ;
			}
		}
		else if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey && g_player.bLoopMotion == true)
		{//ループの場合

		 //モーションカウンタリセット
			g_player.nCounterMotion = 0;

			//現在キーを初期化
			g_player.nKey = 0;
		}
	}
}