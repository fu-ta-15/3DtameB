//-----------------------------------------------------------------------------
//
// モーションの処理 [motion.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "motion.h"
#include "player.h"
#include "input.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void ResetMotion(SELECTMOTION resetType, bool bPartsReset, bool bCounterReset, bool bKeyReset, bool bMotionTrig);
void PlayerMotion(bool bPlayMotion, bool bBlendMotion, int nFrameBlend);
//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitMotion(void)
{
	Player *pPlayer = GetPlayer();

	//モーションの設定
	pPlayer->nNumMotion = 3;

	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey = 2;
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].bLoop = true;
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].nFrame = 65;
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].nFrame = 65;

	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.75f, 1.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.22f, 0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.22f, -0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, -0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.18f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].nNumKey = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].bLoop = false;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].nFrame = 30;

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -2.80f, 0.0f, 0.48f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.44f, -0.31f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.97f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.07f, -1.17f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.50f, 0.0f, -0.85f, -0.35f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.4f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.5f, -0.35f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.59f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(-0.00f, -5.40f, -3.20f, 0.41f, 0.35f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.66f, -0.31f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.45f, -0.82f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 1.07f, -1.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.19f, -0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.5f, -0.41f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.60f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.00f, -6.10f, -26.60f, -0.41f, -0.44f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.62f, 0.06f, -1.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.00f, -6.40f, -27.00f, -0.44f, -0.44f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.13f, 0.47f, -1.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].nNumKey = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].bLoop = true;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].nFrame = 9;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].nFrame = 6;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].nFrame = 9;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].nFrame = 6;

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -1.6f, 0.0f, -0.19f, 0.00f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.01f, 0.00f, 1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, -1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.0, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.01f, -0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -4.2f, 0.0f, -0.35f, 0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, -0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.50f, -0.00f, 1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, -1.00f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.04f, -0.41f, -1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.41f, 0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.82f, -0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, 0.00f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.01f, -0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, 0.00f, 0.00f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, -1.6f, 0.0f, -0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.01f, 0.00f, 1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, -0.00f, -1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -4.2f, 0.0f, -0.35f, -0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.07f, 0.41f, 1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, -0.41f, 0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.50f, 0.00f, -1.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.97f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.01f, 0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.85f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.82f, 0.41f, 0.00f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitMotion(void)
{
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateMotion(void)
{
	Player *pPlayer = GetPlayer();
	pPlayer->nFrameBlend = 10;
	//player motion
	PlayerMotion(pPlayer->bPlayMotion, true, pPlayer->nFrameBlend);
	if (GetKeyboardTrigger(DIK_J) == true) Sleep(5000);
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawMotion(void)
{
}

//-----------------------------------------------------------------------------
// キーのPos,Rotを簡易的に入力させる関数
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// モーション開始関数
//-----------------------------------------------------------------------------
void StartMotion(SELECTMOTION motionSelect, MOTIONTYPE motionType)
{
	Player *pPlayer = GetPlayer();

	//モーションタイプが変更されようとしていたら
	if (motionType != pPlayer->motionType)
	{
		if (pPlayer->bPlayMotion == true && pPlayer->bLoopMotion == false)
		{

		}
		else
		{
			//モーション変更
			pPlayer->motionType = motionType;								// モーションタイプ変更
			ResetMotion(SELECTMOTION_PLAYER, false, true, true, false);			// モーションリセット
		}

	}

	//モーション開始
	if (pPlayer->bPlayMotion == false)
	{
		pPlayer->bPlayMotion = true;
	}
}

/* プレイヤーのモーション */
void PlayerMotion(bool bPlayMotion, bool bBlendMotion, int nFrameBlend)
{
	Player *pPlayer = GetPlayer();

	if (bPlayMotion == true)
	{
		D3DXVECTOR3 rot[10];
		D3DXVECTOR3 pos[10];

		//ループ
		pPlayer->bLoopMotion = pPlayer->aMotionInfo[pPlayer->motionType].bLoop;

		//モーションカウントアップ
		pPlayer->nCounterMotion++;

		//プレイヤーの初期状態
		KEY *pKeyDef = GetDefKey();

		//モデル数分回す
		for (int nCntModel = 0; nCntModel < pPlayer->nNumModel; nCntModel++)
		{
			KEY keyDiff[20];

			//現在のキーと次のキーとの差分を計算
			if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->motionType].nNumKey - 1 && pPlayer->bLoopMotion == true)
			{	// ループの場合
				keyDiff[nCntModel].fPosX = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[0].aKey[nCntModel].fPosX - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosX;
				keyDiff[nCntModel].fPosY = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[0].aKey[nCntModel].fPosY - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosY;
				keyDiff[nCntModel].fPosZ = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[0].aKey[nCntModel].fPosZ - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosZ;
				keyDiff[nCntModel].fRotX = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[0].aKey[nCntModel].fRotX - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotX;
				keyDiff[nCntModel].fRotY = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[0].aKey[nCntModel].fRotY - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotY;
				keyDiff[nCntModel].fRotZ = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[0].aKey[nCntModel].fRotZ - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotZ;
			}
			else
			{	// それ以外
				keyDiff[nCntModel].fPosX = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey + 1].aKey[nCntModel].fPosX - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosX;
				keyDiff[nCntModel].fPosY = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey + 1].aKey[nCntModel].fPosY - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosY;
				keyDiff[nCntModel].fPosZ = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey + 1].aKey[nCntModel].fPosZ - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosZ;
				keyDiff[nCntModel].fRotX = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey + 1].aKey[nCntModel].fRotX - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotX;
				keyDiff[nCntModel].fRotY = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey + 1].aKey[nCntModel].fRotY - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotY;
				keyDiff[nCntModel].fRotZ = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey + 1].aKey[nCntModel].fRotZ - pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotZ;
			}

			//pos
			pos[nCntModel].x = (pKeyDef[nCntModel].fPosX + pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosX) + keyDiff[nCntModel].fPosX * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
			pos[nCntModel].y = (pKeyDef[nCntModel].fPosY + pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosY) + keyDiff[nCntModel].fPosY * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
			pos[nCntModel].z = (pKeyDef[nCntModel].fPosZ + pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fPosZ) + keyDiff[nCntModel].fPosZ * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);

			//現在モーションの差分を再生フレームで割ったもの rot
			rot[nCntModel].x = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotX + keyDiff[nCntModel].fRotX * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
			rot[nCntModel].y = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotY + keyDiff[nCntModel].fRotY * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);
			rot[nCntModel].z = pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel].fRotZ + keyDiff[nCntModel].fRotZ * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame);

			pPlayer->aModel[nCntModel].pos.x = pos[nCntModel].x;
			pPlayer->aModel[nCntModel].pos.y = pos[nCntModel].y;
			pPlayer->aModel[nCntModel].pos.z = pos[nCntModel].z;

			pPlayer->aModel[nCntModel].rot.x = rot[nCntModel].x;
			pPlayer->aModel[nCntModel].rot.y = rot[nCntModel].y;
			pPlayer->aModel[nCntModel].rot.z = rot[nCntModel].z;

			if (pPlayer->aModel[nCntModel].rot.x > D3DX_PI) pPlayer->aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			if (pPlayer->aModel[nCntModel].rot.x < -D3DX_PI) pPlayer->aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			if (pPlayer->aModel[nCntModel].rot.y > D3DX_PI) pPlayer->aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			if (pPlayer->aModel[nCntModel].rot.y < -D3DX_PI) pPlayer->aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			if (pPlayer->aModel[nCntModel].rot.z > D3DX_PI) pPlayer->aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			if (pPlayer->aModel[nCntModel].rot.z < -D3DX_PI) pPlayer->aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			
		}

		//現在キーの再生フレーム数に到達したら
		if (pPlayer->nCounterMotion >= pPlayer->aMotionInfo[pPlayer->motionType].aKeyInfo[pPlayer->nKey].nFrame)
		{
			//次のキーに
			pPlayer->nKey++;

			//モーションカウンタリセット
			ResetMotion(SELECTMOTION_PLAYER, false, true, false, false);
		}

		//現在キーがモーションのキー数に到達したら
		if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->motionType].nNumKey - 1 && pPlayer->bLoopMotion == false)
		{//ループしない場合
		 //モーションリセット
			ResetMotion(SELECTMOTION_PLAYER, false, true, true, true);
		}
		else if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->motionType].nNumKey && pPlayer->bLoopMotion == true)
		{//ループの場合
		 //カウンタとキーをリセット
			ResetMotion(SELECTMOTION_PLAYER, false, true, true, false);
		}
	}
	else if (pPlayer->bPlayMotion == false)
	{
		//モーションリセット
		ResetMotion(SELECTMOTION_PLAYER, false, true, true, false);
	}
}

/* モーションリセット関数 */
void ResetMotion(SELECTMOTION resetType, bool bPartsReset, bool bCounterReset, bool bKeyReset, bool bMotionTrig)
{
	if (bPartsReset == true)
	{
		if (resetType == SELECTMOTION_PLAYER)
		{
			Player *pPlayer = GetPlayer();
			KEY *pKeyDef = GetDefKey();

			//プレイヤーのパーツ回転初期化
			for (int nCnt = 0; nCnt < pPlayer->nNumModel; nCnt++)
			{
				pPlayer->aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pPlayer->aModel[nCnt].pos.x = pKeyDef[nCnt].fPosX;
				pPlayer->aModel[nCnt].pos.y = pKeyDef[nCnt].fPosY;
				pPlayer->aModel[nCnt].pos.z = pKeyDef[nCnt].fPosZ;
			}
		}
		else if (resetType == SELECTMOTION_ENEMY)
		{

		}
	}

	if (bCounterReset == true)
	{
		if (resetType == SELECTMOTION_PLAYER)
		{
			Player *pPlayer = GetPlayer();

			//モーションカウンタ初期化
			pPlayer->nCounterMotion = 0;
		}
	}

	if (bKeyReset == true)
	{
		if (resetType == SELECTMOTION_PLAYER)
		{
			Player *pPlayer = GetPlayer();

			//現在キーを初期化
			pPlayer->nKey = 0;
		}
	}

	if (bMotionTrig == true)
	{
		if (resetType == SELECTMOTION_PLAYER)
		{
			Player *pPlayer = GetPlayer();

			pPlayer->bPlayMotion = false;
		}
	}
}