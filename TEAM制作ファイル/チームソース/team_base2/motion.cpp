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
#include "boss.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void PlayerMotion(bool bPlayMotion);
void EnemyMotion(bool bPlayMotion, int nIdx);
void BossMotion(bool bPlayMotion);
void InitMotionPlayer000(void);
void InitMotionAKR(void);
void InitMotionBoss(void);
void InitMotionCyborg(void);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitMotion(void)
{
	//InitMotionPlayer000();
	//InitMotionAKR();
	InitMotionCyborg();
	InitMotionRobot000();
	InitMotionRobot001();
	InitMotionBoss();

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
	Boss *pBoss = GetBoss();

	//プレイヤーのモーション更新
	PlayerMotion(pPlayer->bPlayMotion);

	//敵のモーション更新
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].bUse == true)
		{
			EnemyMotion(pEnemy[nCntEnemy].bPlayMotion, nCntEnemy);
		}
	}

	//bossmotion
	BossMotion(pBoss->bPlayMotion);
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
	Boss *pBoss = GetBoss();

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

	case SELECTMOTION_BOSS:
		//モーションタイプが変更されようとしていたら
		if (motionType != pBoss->motionType)
		{
			if (pBoss->bPlayMotion == true && pBoss->bLoopMotion == false)
			{

			}
			else
			{
				//モーション変更
				pBoss->motionType = motionType;								// モーションタイプ変更
				ResetMotion(SELECTMOTION_BOSS, false, true, true, false, nIdxEnemy);			// モーションリセット
			}

		}

		//モーション開始
		if (pBoss->bPlayMotion == false)
		{
			pBoss->bPlayMotion = true;
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
		D3DXVECTOR3 rot[20];
		D3DXVECTOR3 pos[20];

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
void EnemyMotion(bool bPlayMotion, int nIdx)
{
	Enemy *pEnemy = GetEnemy();

	if (bPlayMotion == true)
	{
		D3DXVECTOR3 rot[20];
		D3DXVECTOR3 pos[20];

		if (pEnemy[nIdx].bUse == true)
		{
			//ループ
			pEnemy[nIdx].bLoopMotion = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].bLoop;

			//モーションカウントアップ
			pEnemy[nIdx].nCounterMotion++;

			//プレイヤーの初期状態
			KEY *pKeyDef = pEnemy[nIdx].DefKey;

			//モデル数分回す
			for (int nCntModel = 0; nCntModel < pEnemy[nIdx].aModel[0].nNumModel; nCntModel++)
			{
				KEY keyDiff[20];

				//現在のキーと次のキーとの差分を計算
				if (pEnemy[nIdx].nKey >= pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].nNumKey - 1 && pEnemy[nIdx].bLoopMotion == true)
				{	// ループの場合
					keyDiff[nCntModel].fPosX = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[0].aKey[nCntModel].fPosX - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosX;
					keyDiff[nCntModel].fPosY = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[0].aKey[nCntModel].fPosY - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosY;
					keyDiff[nCntModel].fPosZ = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[0].aKey[nCntModel].fPosZ - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosZ;
					keyDiff[nCntModel].fRotX = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[0].aKey[nCntModel].fRotX - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotX;
					keyDiff[nCntModel].fRotY = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[0].aKey[nCntModel].fRotY - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotY;
					keyDiff[nCntModel].fRotZ = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[0].aKey[nCntModel].fRotZ - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotZ;
				}
				else
				{	// それ以外
					keyDiff[nCntModel].fPosX = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey + 1].aKey[nCntModel].fPosX - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosX;
					keyDiff[nCntModel].fPosY = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey + 1].aKey[nCntModel].fPosY - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosY;
					keyDiff[nCntModel].fPosZ = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey + 1].aKey[nCntModel].fPosZ - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosZ;
					keyDiff[nCntModel].fRotX = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey + 1].aKey[nCntModel].fRotX - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotX;
					keyDiff[nCntModel].fRotY = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey + 1].aKey[nCntModel].fRotY - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotY;
					keyDiff[nCntModel].fRotZ = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey + 1].aKey[nCntModel].fRotZ - pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotZ;
				}

				//pos
				pos[nCntModel].x = (pKeyDef[nCntModel].fPosX + pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosX) + keyDiff[nCntModel].fPosX * ((float)pEnemy[nIdx].nCounterMotion / (float)pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame);
				pos[nCntModel].y = (pKeyDef[nCntModel].fPosY + pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosY) + keyDiff[nCntModel].fPosY * ((float)pEnemy[nIdx].nCounterMotion / (float)pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame);
				pos[nCntModel].z = (pKeyDef[nCntModel].fPosZ + pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fPosZ) + keyDiff[nCntModel].fPosZ * ((float)pEnemy[nIdx].nCounterMotion / (float)pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame);

				//現在モーションの差分を再生フレームで割ったもの rot
				rot[nCntModel].x = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotX + keyDiff[nCntModel].fRotX * ((float)pEnemy[nIdx].nCounterMotion / (float)pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame);
				rot[nCntModel].y = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotY + keyDiff[nCntModel].fRotY * ((float)pEnemy[nIdx].nCounterMotion / (float)pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame);
				rot[nCntModel].z = pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].aKey[nCntModel].fRotZ + keyDiff[nCntModel].fRotZ * ((float)pEnemy[nIdx].nCounterMotion / (float)pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame);

				pEnemy[nIdx].aModel[nCntModel].pos.x = pos[nCntModel].x;
				pEnemy[nIdx].aModel[nCntModel].pos.y = pos[nCntModel].y;
				pEnemy[nIdx].aModel[nCntModel].pos.z = pos[nCntModel].z;

				pEnemy[nIdx].aModel[nCntModel].rot.x = rot[nCntModel].x;
				pEnemy[nIdx].aModel[nCntModel].rot.y = rot[nCntModel].y;
				pEnemy[nIdx].aModel[nCntModel].rot.z = rot[nCntModel].z;

				if (pEnemy[nIdx].aModel[nCntModel].rot.x > D3DX_PI) pEnemy[nIdx].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
				if (pEnemy[nIdx].aModel[nCntModel].rot.x < -D3DX_PI) pEnemy[nIdx].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
				if (pEnemy[nIdx].aModel[nCntModel].rot.y > D3DX_PI) pEnemy[nIdx].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
				if (pEnemy[nIdx].aModel[nCntModel].rot.y < -D3DX_PI) pEnemy[nIdx].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
				if (pEnemy[nIdx].aModel[nCntModel].rot.z > D3DX_PI) pEnemy[nIdx].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
				if (pEnemy[nIdx].aModel[nCntModel].rot.z < -D3DX_PI) pEnemy[nIdx].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}

			//現在キーの再生フレーム数に到達したら
			if (pEnemy[nIdx].nCounterMotion >= pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].aKeyInfo[pEnemy[nIdx].nKey].nFrame)
			{
				//次のキーに
				pEnemy[nIdx].nKey++;

				//モーションカウンタリセット
				ResetMotion(SELECTMOTION_ENEMY, false, true, false, false, nIdx);
			}

			//現在キーがモーションのキー数に到達したら
			if (pEnemy[nIdx].nKey >= pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].nNumKey - 1 && pEnemy[nIdx].bLoopMotion == false)
			{//ループしない場合
			 //モーションリセット
				ResetMotion(SELECTMOTION_ENEMY, false, true, true, true, nIdx);
			}
			else if (pEnemy[nIdx].nKey >= pEnemy[nIdx].aMotionInfo[pEnemy[nIdx].motionType].nNumKey && pEnemy[nIdx].bLoopMotion == true)
			{//ループの場合
			 //カウンタとキーをリセット
				ResetMotion(SELECTMOTION_ENEMY, false, true, true, false, nIdx);
			}
		}
		else if (pEnemy[nIdx].bPlayMotion == false)
		{
			//モーションリセット
			ResetMotion(SELECTMOTION_ENEMY, false, true, true, false, nIdx);
		}
	}
}

void BossMotion(bool bPlayMotion)
{
	Boss *pBoss = GetBoss();

	if (bPlayMotion == true)
	{
		D3DXVECTOR3 rot[20];
		D3DXVECTOR3 pos[20];

		if (pBoss->bUse == true)
		{
			//ループ
			pBoss->bLoopMotion = pBoss->aMotionInfo[pBoss->motionType].bLoop;

			//モーションカウントアップ
			pBoss->nCounterMotion++;

			//プレイヤーの初期状態
			KEY *pKeyDef = pBoss->DefKey;

			//モデル数分回す
			for (int nCntModel = 0; nCntModel < pBoss->aModel[0].nNumModel; nCntModel++)
			{
				KEY keyDiff[20];

				//現在のキーと次のキーとの差分を計算
				if (pBoss->nKey >= pBoss->aMotionInfo[pBoss->motionType].nNumKey - 1 && pBoss->bLoopMotion == true)
				{	// ループの場合
					keyDiff[nCntModel].fPosX = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[0].aKey[nCntModel].fPosX - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosX;
					keyDiff[nCntModel].fPosY = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[0].aKey[nCntModel].fPosY - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosY;
					keyDiff[nCntModel].fPosZ = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[0].aKey[nCntModel].fPosZ - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosZ;
					keyDiff[nCntModel].fRotX = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[0].aKey[nCntModel].fRotX - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotX;
					keyDiff[nCntModel].fRotY = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[0].aKey[nCntModel].fRotY - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotY;
					keyDiff[nCntModel].fRotZ = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[0].aKey[nCntModel].fRotZ - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotZ;
				}
				else
				{	// それ以外
					keyDiff[nCntModel].fPosX = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey + 1].aKey[nCntModel].fPosX - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosX;
					keyDiff[nCntModel].fPosY = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey + 1].aKey[nCntModel].fPosY - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosY;
					keyDiff[nCntModel].fPosZ = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey + 1].aKey[nCntModel].fPosZ - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosZ;
					keyDiff[nCntModel].fRotX = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey + 1].aKey[nCntModel].fRotX - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotX;
					keyDiff[nCntModel].fRotY = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey + 1].aKey[nCntModel].fRotY - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotY;
					keyDiff[nCntModel].fRotZ = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey + 1].aKey[nCntModel].fRotZ - pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotZ;
				}

				//pos
				pos[nCntModel].x = (pKeyDef[nCntModel].fPosX + pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosX) + keyDiff[nCntModel].fPosX * ((float)pBoss->nCounterMotion / (float)pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame);
				pos[nCntModel].y = (pKeyDef[nCntModel].fPosY + pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosY) + keyDiff[nCntModel].fPosY * ((float)pBoss->nCounterMotion / (float)pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame);
				pos[nCntModel].z = (pKeyDef[nCntModel].fPosZ + pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fPosZ) + keyDiff[nCntModel].fPosZ * ((float)pBoss->nCounterMotion / (float)pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame);

				//現在モーションの差分を再生フレームで割ったもの rot
				rot[nCntModel].x = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotX + keyDiff[nCntModel].fRotX * ((float)pBoss->nCounterMotion / (float)pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame);
				rot[nCntModel].y = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotY + keyDiff[nCntModel].fRotY * ((float)pBoss->nCounterMotion / (float)pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame);
				rot[nCntModel].z = pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].aKey[nCntModel].fRotZ + keyDiff[nCntModel].fRotZ * ((float)pBoss->nCounterMotion / (float)pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame);

				pBoss->aModel[nCntModel].pos.x = pos[nCntModel].x;
				pBoss->aModel[nCntModel].pos.y = pos[nCntModel].y;
				pBoss->aModel[nCntModel].pos.z = pos[nCntModel].z;

				pBoss->aModel[nCntModel].rot.x = rot[nCntModel].x;
				pBoss->aModel[nCntModel].rot.y = rot[nCntModel].y;
				pBoss->aModel[nCntModel].rot.z = rot[nCntModel].z;

				if (pBoss->aModel[nCntModel].rot.x > D3DX_PI) pBoss->aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
				if (pBoss->aModel[nCntModel].rot.x < -D3DX_PI) pBoss->aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
				if (pBoss->aModel[nCntModel].rot.y > D3DX_PI) pBoss->aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
				if (pBoss->aModel[nCntModel].rot.y < -D3DX_PI) pBoss->aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
				if (pBoss->aModel[nCntModel].rot.z > D3DX_PI) pBoss->aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
				if (pBoss->aModel[nCntModel].rot.z < -D3DX_PI) pBoss->aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}

			//現在キーの再生フレーム数に到達したら
			if (pBoss->nCounterMotion >= pBoss->aMotionInfo[pBoss->motionType].aKeyInfo[pBoss->nKey].nFrame)
			{
				//次のキーに
				pBoss->nKey++;

				//モーションカウンタリセット
				ResetMotion(SELECTMOTION_BOSS, false, true, false, false, NULL);
			}

			//現在キーがモーションのキー数に到達したら
			if (pBoss->nKey >= pBoss->aMotionInfo[pBoss->motionType].nNumKey - 1 && pBoss->bLoopMotion == false)
			{//ループしない場合
			 //モーションリセット
				ResetMotion(SELECTMOTION_BOSS, false, true, true, true, NULL);
			}
			else if (pBoss->nKey >= pBoss->aMotionInfo[pBoss->motionType].nNumKey && pBoss->bLoopMotion == true)
			{//ループの場合
			 //カウンタとキーをリセット
				ResetMotion(SELECTMOTION_BOSS, false, true, true, false, NULL);
			}
		}
		else if (pBoss->bPlayMotion == false)
		{
			//モーションリセット
			ResetMotion(SELECTMOTION_BOSS, false, true, true, false, NULL);
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
		else if (resetType == SELECTMOTION_BOSS)
		{
			Boss *pBoss = GetBoss();

			//
			pBoss->nCounterMotion = 0;
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
		else if (resetType == SELECTMOTION_BOSS)
		{
			Boss *pBoss = GetBoss();

			//
			pBoss->nKey = 0;
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
		else if (resetType == SELECTMOTION_BOSS)
		{
			Boss *pBoss = GetBoss();

			pBoss->bPlayMotion = false;
		}
	}
}

// モーションをテキストで読み込み
void MotionText(const char * cXFileName)
{
	//MOTION_INFO MotionInfo;				// モーション情報保存用

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

// モーション読み込み プレイヤー(仮）
void InitMotionPlayer000(void)
{
	Player *pPlayer = GetPlayer();

	//モーションの設定
	pPlayer->nNumMotion = 4;

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
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);


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
	//pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

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

	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].nNumKey = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].bLoop = false;
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].nFrame = 30;
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].nFrame = 30;

	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.25f, 0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.25f, -0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.18f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.18f, 0.0f, 0.0f);
	//pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 1.48f);

	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, -2.30f, 9.10f, 0.0f, 1.01f, 0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.91f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.35f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.51f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.57f, -1.07f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, -0.13f, 0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[2].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 1.48f);

	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[0] = KeyPosRot(8.10f, -2.30f, -16.60f, 0.0f, -1.70f, 0.03f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.91f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.57f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.09f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.03f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.57f, -0.85f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, -0.13f, 0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//pPlayer->aMotionInfo[MOTIONTYPE_SLASH].aKeyInfo[3].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 1.48f);

}

// test
void InitMotionAKR(void)
{
	Player *pPlayer = GetPlayer();

	//モーションの設定
	pPlayer->nNumMotion = 3;

	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey = 2;
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].bLoop = true;
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].nFrame = 50;
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].nFrame = 50;

	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.10f, 0, 0);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.28f, 0.69f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.25, 0);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.28f, -0.69f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 0.06f, -0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, -0.06f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[10] =KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, -0.09f, -0.19f);


	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -1.00f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.25f, 0.95f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.25f, -0.95f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.53f , 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.12f, 0.06f, 0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.18f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.12f, -0.06f, 0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.18f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.00f, -0.25f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].nNumKey = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].bLoop = false;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].nFrame = 30;

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.25f, 0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.25f, -0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.18f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.50f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.18f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -2.30f, 9.10f, 0.0f, 1.01f, 0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.91f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.35f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.51f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.57f, -1.07f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, -0.13f, 0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 1.48f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(8.10f, -2.30f, -16.60f, 0.0f, -1.70f, 0.03f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.91f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.57f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.09f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.03f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.57f, -0.85f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, -0.13f, 0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 1.48f);

	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(8.10f, -2.30f, -16.60f, 0.0f, -1.70f, 0.03f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.91f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.57f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.09f, -0.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.03f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.57f, -0.85f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, -0.13f, 0.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 1.48f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].nNumKey = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].bLoop = true;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].nFrame = 8;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].nFrame = 8;
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].nFrame = 10;

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 1.0f, 0.0f, -0.37f, -0.16f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.12f, -0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.51f, 0.00f, 1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.09f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.32f, 0.00f, -1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.09f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.51f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.45f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -2.30f, 0.0f, -0.53f, -0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, -0.16f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.42f, 0.00f, 1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.90f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.45f, 0.0f, -1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.81f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.75f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.16f, 0.09f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.45f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 1.00f, 0.0f, -0.37f, 0.14f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.14f, 0.00f, 1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.09f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.52f, 0.00f, -1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.09f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.51f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.05f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.07f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.92f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[2].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.50f, 0.00f, -0.97f);

	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -2.30f, 0.0f, -0.53f, 0.23f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.16f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.27f, 0.00f, 1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.84f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.33f, 0.00f, -1.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.59f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.16f, -0.09f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.43f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.76f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_WALK].aKeyInfo[3].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.50f, 0.00f, -0.97f);
}

// モーション読み込み ロボット000
void InitMotionRobot000(void)
{
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].type == ENEMYTYPE_ROBOT000)
		{
			//モーションの設定
			pEnemy[nCntEnemy].nNumMotion = 3;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].nNumKey = 2;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].bLoop = true;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].nFrame = 50;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].nFrame = 50;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.00f, -0.64f, 0.00f, -0.08f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.00f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00, 0.00f, -0.33f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.33f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.08f, 0.00f, -0.11f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.08f, 0.00f, 0.10f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].nNumKey = 7;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].bLoop = false;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].nFrame = 8;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].nFrame = 7;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].nFrame = 6;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].nFrame = 4;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].nFrame = 40;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, 0.00f, 0.06f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, 0.00f, -0.13f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.00f, 0.13f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.00f, -0.06f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.00f, 0.00f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -1.20f, 0.0f, -0.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.01f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.91f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, -4.10f, 0.0f, -0.82f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.50f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.82f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, 0.0f, -20.00f, -1.35f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[0] = KeyPosRot(0.0f, -11.20f, -26.70f, -1.57f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.53f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.57f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[4].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[0] = KeyPosRot(0.0f, -4.40f, -26.40f, -0.75f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.82f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.82f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.75f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[5].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[0] = KeyPosRot(0.0f, 0.0f, -26.00f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_ATTACK].aKeyInfo[6].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].nNumKey = 4;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].bLoop = true;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].nFrame = 20;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].nFrame = 20;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].nFrame = 20;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].nFrame = 20;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.f, 0.0f, 0.13f, 0.00f, -0.19f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.00f, -0.16f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 0.00f, 0.19f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, -0.28f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.22f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.00f, 0.19f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 0.00f, -0.22f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.00f, -0.30f, 0.00f, 0, 0.47f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.03f, -0.19f, -0.06f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT000_WALK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0, -0.25f, 0.0f);
		}
	}
}

// モーション読み込み ロボット001
void InitMotionRobot001(void)
{
	Enemy *pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].type == ENEMYTYPE_ROBOT001)
		{
			//モーションの設定
			pEnemy[nCntEnemy].nNumMotion = 3;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].nNumKey = 4;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].bLoop = true;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].nFrame = 50;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].nFrame = 30;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].nFrame = 30;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].nFrame = 50;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -8.00f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.57f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.70f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.70f, 0.00f, 0.00f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.63f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, -0.63f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -8.00f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.00f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.57f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.70f, 0.00f, 0.00f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_NEUTRAL].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.70f, 0.00f, 0.00f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].nNumKey = 5;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].bLoop = false;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].nFrame = 20;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].nFrame = 20;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -1.10f, 4.10f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);


			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -1.10f, 7.10f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.09f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.09f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);


			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -1.10f, 10.00f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.28f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.19f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_ATTACK].aKeyInfo[4].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].nNumKey = 4;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].bLoop = true;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].nFrame = 10;
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].nFrame = 10;

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 1.60f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.47f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, -2.40f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 1.40f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.57f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, 0.0f, 0.0f);

			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, 0.0f, -1.90f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.13f, 0.0f, 0.0f);
			pEnemy[nCntEnemy].aMotionInfo[MOTIONTYPE_ROBOT001_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);
		}
	}
}

// BOSS MOTION
void InitMotionBoss(void)
{
	Boss *pBoss = GetBoss();

	//モーションの設定
	pBoss->nNumMotion = 3;

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].nNumKey = 4;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].bLoop = true;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].nFrame = 50;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].nFrame = 30;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].nFrame = 30;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].nFrame = 30;

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 3.10f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.28f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.22f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.47f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 2.00f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.19f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.19f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.16f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 1.00f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.13f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.03f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.19f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.09f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.13f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_NEUTRAL].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].nNumKey = 4;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].bLoop = false;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].nFrame = 10;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].nFrame = 10;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].nFrame = 10;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].nFrame = 30;

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].nNumKey = 4;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].bLoop = true;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].nFrame = 10;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].nFrame = 10;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].nFrame = 10;
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].nFrame = 10;

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.53f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.88f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.16f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 3.10f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.53f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.88f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.53f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.88f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.16f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -3.10f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.53f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.88f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.16f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.06f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pBoss->aMotionInfo[MOTIONTYPE_BOSS_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

// モーション読み込み サイボーグ忍者
void InitMotionCyborg(void)
{
	Player *pPlayer = GetPlayer();

	//モーションの設定
	pPlayer->nNumMotion = 4;

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].nNumKey = 2;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].bLoop = true;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].nFrame = 50;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].nFrame = 50;

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -0.50f, 0.0f, 0.03f, 0.66f, 0.03f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, -0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.47f, 1.35f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, -0.22f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.00f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.00f, 0.19f, -0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, -0.60f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -1.10f, -0.80f, -0.03f, 0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.03f, -0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, -0.16f, 1.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, -0.22f, -0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.03f, 0.00f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.16f, -0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, -0.60f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NEUTRAL].aKeyInfo[1].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);


	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].nNumKey = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].bLoop = true;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].nFrame = 5;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].nFrame = 5;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].nFrame = 5;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].nFrame = 5;

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, -21.00f, 0.0f, -0.91f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, 0.0f, 1.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.63f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.13f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, -0.03f, -1.29f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.51f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.63f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.88f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.58f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.63f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[0].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.38f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, -22.40f, 0.0f, -0.91f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, 0.00f, 1.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.60f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.16f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, -0.03f, -1.29f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.51f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.32f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.50f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.42f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.28f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.48f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.35f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.45f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.10f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[1].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.35f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, -21.00f, 0.0f, -0.91f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.00f, 1.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.63f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.13f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.53f, -0.03f, -1.29f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.51f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.57f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.86f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.63f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.01f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[2].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.28f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, -22.40f, 0.0f, -0.91f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.00f, 1.41f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.60f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.16f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, -0.03f, -1.29f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.51f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.38f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.54f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.16f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.23f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.35f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.45f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.10f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_WALK].aKeyInfo[3].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.31f, 0.0f);


	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].nNumKey = 8;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].bLoop = false;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].nFrame = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].nFrame = 6;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].nFrame = 2;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].nFrame = 15;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].nFrame = 4;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].nFrame = 6;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].nFrame = 8;

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(-32.80f, -25.50f, -29.30f, -0.57f, 0.66f, 0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -0.66f, -0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.00f, -0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, 1.10f, 1.07f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.41f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.60f, -0.60f, -1.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.95f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, -0.16f, 0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.53f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.69f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[0].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(-32.80f, -25.50f, -29.30f, -0.57f, 0.19f, -0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, -0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.94f, 0.25f, 1.63f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.67f, -0.41f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.60f, -0.60f, -1.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.79f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.95f, 0.66f, 0.72f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.19f, 0.63f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, -0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.75f, 0.00f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[1].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(-32.80f, -25.50f, -29.30f, -0.57f, -0.69f, -0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.22f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.94f, -0.72f, 1.63f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.67f, -0.41f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.09f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.82f, -0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.67f, 0.31f, -0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.47f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.12f, 0.69f, 1.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, -0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.75f, 0.00f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[2].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, -0.38f, -1.85f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(-32.80f, -25.50f, -29.30f, -0.57f, -0.06f, -0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, -0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.94f, -0.53f, 1.63f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.23f, -0.41f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.45f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.53f, -0.66f, -1.70f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.95f, 0.79f, 0.72f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.31f, 0.81f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, -0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.75f, 0.00f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[3].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.95f, 1.19f, 0.47f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[0] = KeyPosRot(-32.80f, -10.60f, -24.10f, -0.41f, -0.06f, -0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, -0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.92f, -0.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.63f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.92f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.53f, -0.66f, -1.70f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.10f, 0.22f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, 0.85f, 0.81f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, -0.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.75f, 0.00f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[4].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 1.57f, 0.28f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[0] = KeyPosRot(-32.80f, -2.10f, -40.10f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, -0.22f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.69f, -2.45f, -0.44f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.82f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.54f, 2.26f, 0.66f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.85f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.28f, 0.00f, -0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.25f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.00f, 0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.35f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[5].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.47f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[0] = KeyPosRot(-29.40f, -14.20f, -12.60f, -0.38f, 0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, -0.50f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.53f, 0.00f, 1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.63f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, -0.38f, -1.45f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.29f, -1.29f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.47f, 0.28f, 0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.00f, 0.09f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.26f, 0.60f, 0.60f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.94f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[6].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.38f, 1.04f, 0.0f);

	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[0] = KeyPosRot(0.0f, -0.50f, 0.0f, -0.16f, 0.66f, 0.03f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, -0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.47f, 0.47f, 1.63f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.57f, -0.22f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.00f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.19f, -0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.15f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.97f, -0.25f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.10f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_KATANA_ATTACK].aKeyInfo[7].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);


	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].nNumKey = 8;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].bLoop = false;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].nFrame = 6;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].nFrame = 15;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].nFrame = 7;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].nFrame = 7;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].nFrame = 7;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].nFrame = 10;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].nFrame = 20;
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].nFrame = 20;
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(-33.00f, -20.00f, -21.40f, -0.66f, -0.50f, 0.31f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.83f, -1.10f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, 0.00f, 0.66f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, -0.28f, 0.44f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 1.89f, 0.44f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.34f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.36f, 0.13f, -0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.63f, 0.00f, -0.35f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.82f, -0.28f, 0.10f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.10f, 0.09f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.69f, 0.00f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.79f, 0.19f, -0.47f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[0].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, 0.72f, 0.03f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(-33.00f, -23.60f, -21.40f, -0.88f, -0.50f, 0.47f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.83f, -1.10f, -0.28f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, 0.00f, 0.66f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, -0.28f, 0.44f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 1.89f, 0.44f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.35f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.36f, 0.13f, -0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.03f, 0.00f, -0.35f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.82f, -0.47f, -0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.00f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[1].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, 0.72f, 0.03f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(-33.00f, -23.60f, -21.40f, -0.88f, -0.50f, 0.47f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -2.83f, -1.10f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.35f, 0.00f, 0.66f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.70f, 0.50f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.53f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.36f, 0.13f, -0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.03f, 0.00f, -0.35f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.82f, -0.47f, -0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.13f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.00f, 0.25f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.01f, 0.19f, -0.47f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[2].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, 0.72f, -0.13f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(-33.00f, -21.70f, -21.40f, -0.63f, -1.32f, 0.47f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.92f, -1.60f, 0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 0.00f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.88f, - 0.06f, - 0.98f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.79f, 1.41f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.35f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.13f, -1.51f, -2.23f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.50f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.16f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.79f, -0.38f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.45f, -0.53f, -0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.35f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.50f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.41f, -0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[3].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 0.44f, 0.0f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[0] = KeyPosRot(-12.30f, -14.40f, -21.40f, -0.38f, -1.92f, 0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, -0.44f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.44f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.98f, -1.98f, -0.22f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 0.00f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.09f, -1.13f, -1.01f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 1.95f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.13f, 0.22f, -0.53f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.22f, -0.79f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.47f, -0.19f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, -0.25f, 0.53f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.20f, -0.53f, -0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.35f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.50f, -0.38f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.44f, -0.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[4].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 0.57f, 0.0f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[0] = KeyPosRot(11.80f, -6.30f, 0.0f, -0.19f, 2.32f, 0.12f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.44f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, -3.11f, -1.98f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 0.00f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.25f, -1.38f, -0.44f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 1.95f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 1.26f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, -0.31f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.79f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[5].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.69f, 0.0f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[0] = KeyPosRot(4.40f, -3.80f, 10.70f, 0.0f, 0.63f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.44f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.28f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 2.36f, -1.98f, -0.57f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 0.00f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.75f, -1.19f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.88f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 1.26f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.28f, -0.31f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.79f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.16f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[6].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.25f, 0.0f);
	
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[0] = KeyPosRot(0.0f, -0.50f, 0.0f, 0.03f, 0.66f, 0.03f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, - 0.66f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.69f, -0.50f, 1.32f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.03f, 0.00f, 0.13f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.00f, -1.38f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.72f, 0.25f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.19f, -0.16f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[10] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[11] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[12] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.19f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[13] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, -0.60f, 0.06f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[14] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[15] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.09f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[16] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.0f);
	pPlayer->aMotionInfo[MOTIONTYPE_CYBORG_NAGINATA_ATTACK].aKeyInfo[7].aKey[17] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.25f, 0.0f);

}