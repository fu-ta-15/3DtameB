//-----------------------------------------------------------------------------
//
// モーションの処理 [motion.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "motion.h"
#include "player.h"
#include "enemy.h"
#include "input.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void ResetMotion(SELECTMOTION resetType, bool bPartsReset, bool bCounterReset, bool bKeyReset, bool bMotionTrig, int nIdxEnemy);
void PlayerMotion(bool bPlayMotion);
void EnemyMotion(bool bPlayMotion);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitMotion(void)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

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

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].type == ENEMYTYPE_ROBOT)
		{
			//モーションの設定
			pEnemy[nCntEnemy].nNumMotion = 3;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey = 2;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].bLoop = true;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].nFrame = 65;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].nFrame = 65;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.75f, 1.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.09f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.09f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.22f, 0.79f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.22f, -0.79f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, -0.09f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.18f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.09f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].nNumKey = 4;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].bLoop = false;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].nFrame = 30;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -2.80f, 0.0f, 0.48f, 0.25f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.44f, -0.31f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.97f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.07f, -1.17f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.50f, 0.0f, -0.85f, -0.35f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.4f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.5f, -0.35f, 0.13f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.59f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(-0.00f, -5.40f, -3.20f, 0.41f, 0.35f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.66f, -0.31f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.45f, -0.82f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 1.07f, -1.16f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.19f, -0.41f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.41f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.5f, -0.41f, 0.13f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.60f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.00f, -6.10f, -26.60f, -0.41f, -0.44f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.62f, 0.06f, -1.16f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.00f, -6.40f, -27.00f, -0.44f, -0.44f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.13f, 0.47f, -1.16f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].nNumKey = 4;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].bLoop = true;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].nFrame = 9;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].nFrame = 6;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].nFrame = 9;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].nFrame = 6;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -1.6f, 0.0f, -0.19f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.01f, 0.00f, 1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, -1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.0, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.01f, -0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -4.2f, 0.0f, -0.35f, 0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, -0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.50f, -0.00f, 1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, -1.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.04f, -0.41f, -1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.41f, 0.16f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.82f, -0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.01f, -0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, 0.00f, 0.00f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, -1.6f, 0.0f, -0.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.01f, 0.00f, 1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, -0.00f, -1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -4.2f, 0.0f, -0.35f, -0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.41f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.07f, 0.41f, 1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, -0.41f, 0.16f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.50f, 0.00f, -1.60f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.97f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.01f, 0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.85f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.82f, 0.41f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
		}
	}
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
	Enemy *pEnemy = GetEnemy();

	//プレイヤーのモーション更新
	PlayerMotion(pPlayer->bPlayMotion);

	//敵のモーション更新
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++) EnemyMotion(pEnemy[nCntEnemy].bPlayMotion);

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
void StartMotion(SELECTMOTION motionSelect, MOTIONTYPE motionType, int nIdxEnemy)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	switch (motionSelect)
	{
	case SELECTMOTION_PLAYER:
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
				ResetMotion(SELECTMOTION_PLAYER, false, true, true, false, NULL);			// モーションリセット
			}

		}

		//モーション開始
		if (pPlayer->bPlayMotion == false)
		{
			pPlayer->bPlayMotion = true;
		}
		break;

	case SELECTMOTION_ENEMY:
		//モーションタイプが変更されようとしていたら
		if (motionType != pEnemy[nIdxEnemy].motionType)
		{
			if (pEnemy[nIdxEnemy].bPlayMotion == true && pEnemy[nIdxEnemy].bLoopMotion == false)
			{

			}
			else
			{
				//モーション変更
				pEnemy[nIdxEnemy].motionType = motionType;								// モーションタイプ変更
				ResetMotion(SELECTMOTION_ENEMY, false, true, true, false, nIdxEnemy);			// モーションリセット
			}

		}

		//モーション開始
		if (pEnemy[nIdxEnemy].bPlayMotion == false)
		{
			pEnemy[nIdxEnemy].bPlayMotion = true;
		}
		break;

	default:
		break;
	}

}


/* プレイヤーのモーション */
void PlayerMotion(bool bPlayMotion)
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
			ResetMotion(SELECTMOTION_PLAYER, false, true, false, false, NULL);
		}

		//現在キーがモーションのキー数に到達したら
		if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->motionType].nNumKey - 1 && pPlayer->bLoopMotion == false)
		{//ループしない場合
		 //モーションリセット
			ResetMotion(SELECTMOTION_PLAYER, false, true, true, true, NULL);
		}
		else if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->motionType].nNumKey && pPlayer->bLoopMotion == true)
		{//ループの場合
		 //カウンタとキーをリセット
			ResetMotion(SELECTMOTION_PLAYER, false, true, true, false, NULL);
		}
	}
	else if (pPlayer->bPlayMotion == false)
	{
		//モーションリセット
		ResetMotion(SELECTMOTION_PLAYER, false, true, true, false, NULL);
	}
}

/* Enemyのモーション */
void EnemyMotion(bool bPlayMotion)
{
	Enemy *pEnemy = GetEnemy();

	if (bPlayMotion == true)
	{
		D3DXVECTOR3 rot[10];
		D3DXVECTOR3 pos[10];

		for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
		{
			if (pEnemy[nCntEnemy].bUse == true)
			{
				//ループ
				pEnemy[nCntEnemy].bLoopMotion = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].bLoop;

				//モーションカウントアップ
				pEnemy[nCntEnemy].nCounterMotion++;

				//プレイヤーの初期状態
				KEY *pKeyDef = GetDefKey();

				//モデル数分回す
				for (int nCntModel = 0; nCntModel < pEnemy[nCntEnemy].aModel[0].nNumModel; nCntModel++)
				{
					KEY keyDiff[20];

					//現在のキーと次のキーとの差分を計算
					if (pEnemy[nCntEnemy].nKey >= pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].nNumKey - 1 && pEnemy[nCntEnemy].bLoopMotion == true)
					{	// ループの場合
						keyDiff[nCntModel].fPosX = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[0].aKey[nCntModel].fPosX - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX;
						keyDiff[nCntModel].fPosY = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[0].aKey[nCntModel].fPosY - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY;
						keyDiff[nCntModel].fPosZ = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[0].aKey[nCntModel].fPosZ - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ;
						keyDiff[nCntModel].fRotX = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[0].aKey[nCntModel].fRotX - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX;
						keyDiff[nCntModel].fRotY = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[0].aKey[nCntModel].fRotY - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY;
						keyDiff[nCntModel].fRotZ = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[0].aKey[nCntModel].fRotZ - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ;
					}
					else
					{	// それ以外
						keyDiff[nCntModel].fPosX = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fPosX - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX;
						keyDiff[nCntModel].fPosY = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fPosY - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY;
						keyDiff[nCntModel].fPosZ = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fPosZ - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ;
						keyDiff[nCntModel].fRotX = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fRotX - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX;
						keyDiff[nCntModel].fRotY = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fRotY - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY;
						keyDiff[nCntModel].fRotZ = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey + 1].aKey[nCntModel].fRotZ - pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ;
					}

					//pos
					pos[nCntModel].x = (pKeyDef[nCntModel].fPosX + pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosX) + keyDiff[nCntModel].fPosX * ((float)pEnemy[nCntEnemy].nCounterMotion / (float)pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame);
					pos[nCntModel].y = (pKeyDef[nCntModel].fPosY + pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosY) + keyDiff[nCntModel].fPosY * ((float)pEnemy[nCntEnemy].nCounterMotion / (float)pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame);
					pos[nCntModel].z = (pKeyDef[nCntModel].fPosZ + pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ) + keyDiff[nCntModel].fPosZ * ((float)pEnemy[nCntEnemy].nCounterMotion / (float)pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame);

					//現在モーションの差分を再生フレームで割ったもの rot
					rot[nCntModel].x = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotX + keyDiff[nCntModel].fRotX * ((float)pEnemy[nCntEnemy].nCounterMotion / (float)pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame);
					rot[nCntModel].y = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotY + keyDiff[nCntModel].fRotY * ((float)pEnemy[nCntEnemy].nCounterMotion / (float)pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame);
					rot[nCntModel].z = pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].aKey[nCntModel].fRotZ + keyDiff[nCntModel].fRotZ * ((float)pEnemy[nCntEnemy].nCounterMotion / (float)pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame);

					pEnemy[nCntEnemy].aModel[nCntModel].pos.x = pos[nCntModel].x;
					pEnemy[nCntEnemy].aModel[nCntModel].pos.y = pos[nCntModel].y;
					pEnemy[nCntEnemy].aModel[nCntModel].pos.z = pos[nCntModel].z;

					pEnemy[nCntEnemy].aModel[nCntModel].rot.x = rot[nCntModel].x;
					pEnemy[nCntEnemy].aModel[nCntModel].rot.y = rot[nCntModel].y;
					pEnemy[nCntEnemy].aModel[nCntModel].rot.z = rot[nCntModel].z;

					if (pEnemy[nCntEnemy].aModel[nCntModel].rot.x > D3DX_PI) pEnemy[nCntEnemy].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
					if (pEnemy[nCntEnemy].aModel[nCntModel].rot.x < -D3DX_PI) pEnemy[nCntEnemy].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
					if (pEnemy[nCntEnemy].aModel[nCntModel].rot.y > D3DX_PI) pEnemy[nCntEnemy].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
					if (pEnemy[nCntEnemy].aModel[nCntModel].rot.y < -D3DX_PI) pEnemy[nCntEnemy].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
					if (pEnemy[nCntEnemy].aModel[nCntModel].rot.z > D3DX_PI) pEnemy[nCntEnemy].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
					if (pEnemy[nCntEnemy].aModel[nCntModel].rot.z < -D3DX_PI) pEnemy[nCntEnemy].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;

				}

				//現在キーの再生フレーム数に到達したら
				if (pEnemy[nCntEnemy].nCounterMotion >= pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].aKeyInfo[pEnemy[nCntEnemy].nKey].nFrame)
				{
					//次のキーに
					pEnemy[nCntEnemy].nKey++;

					//モーションカウンタリセット
					ResetMotion(SELECTMOTION_ENEMY, false, true, false, false, nCntEnemy);
				}

				//現在キーがモーションのキー数に到達したら
				if (pEnemy[nCntEnemy].nKey >= pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].nNumKey - 1 && pEnemy[nCntEnemy].bLoopMotion == false)
				{//ループしない場合
				 //モーションリセット
					ResetMotion(SELECTMOTION_ENEMY, false, true, true, true, nCntEnemy);
				}
				else if (pEnemy[nCntEnemy].nKey >= pEnemy[nCntEnemy].aMotionInfo[pEnemy[nCntEnemy].motionType].nNumKey && pEnemy[nCntEnemy].bLoopMotion == true)
				{//ループの場合
				 //カウンタとキーをリセット
					ResetMotion(SELECTMOTION_ENEMY, false, true, true, false, nCntEnemy);
				}
			}
			else if (pEnemy[nCntEnemy].bPlayMotion == false)
			{
				//モーションリセット
				ResetMotion(SELECTMOTION_ENEMY, false, true, true, false, nCntEnemy);
			}
		}
	}
}

/* モーションリセット関数 */
void ResetMotion(SELECTMOTION resetType, bool bPartsReset, bool bCounterReset, bool bKeyReset, bool bMotionTrig, int nIdxEnemy)
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
		else if (resetType == SELECTMOTION_ENEMY)
		{
			Enemy *pEnemy = GetEnemy();

			//モーションカウンタ初期化
			pEnemy[nIdxEnemy].nCounterMotion = 0;
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
		else if (resetType == SELECTMOTION_ENEMY)
		{
			Enemy *pEnemy = GetEnemy();

			//現在キーを初期化
			pEnemy[nIdxEnemy].nKey = 0;
		}
	}

	if (bMotionTrig == true)
	{
		if (resetType == SELECTMOTION_PLAYER)
		{
			Player *pPlayer = GetPlayer();

			pPlayer->bPlayMotion = false;
		}
		else if (resetType == SELECTMOTION_ENEMY)
		{
			Enemy *pEnemy = GetEnemy();

			pEnemy[nIdxEnemy].bPlayMotion = false;
		}
	}
}

// モーションをテキストで読み込み
void MotionText(const char * cXFileName)
{
	MOTION_INFO MotionInfo;				// モーション情報保存用

	FILE * pFile = fopen(cXFileName, "r");	// ファイルへのポインタ

	char *str;				// 文字列読み込み用
	int FileSize;			// ファイルのサイズ保存用

	// ファイルの中の最後までの長さを取得
	fseek(pFile, 0, SEEK_END);
	FileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// メモリの確保
	str = (char*)malloc(sizeof(char) * FileSize);

	// メモリの初期化
	memset(str, NULL, sizeof(char) * FileSize);


	while (strcmp(str, "MOTION_END") != 0)
	{

	}

	free(str);
}
