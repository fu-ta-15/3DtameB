//-----------------------------------------------------------------------------
//
// モーションの処理 ヘッダー [motion.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MOTION_MAX (10) // max amount of motion

//-----------------------------------------------------------------------------
// モーションの種類
//-----------------------------------------------------------------------------
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,			// ニュートラルモーション
	MOTIONTYPE_ATTACK,				// 攻撃モーション
	MOTIONTYPE_WALK,				// 歩きモーション
	MOTIONTYPE_MAX
} MOTIONTYPE;

//-----------------------------------------------------------------------------
// 選択用
//-----------------------------------------------------------------------------
typedef enum
{
	SELECTMOTION_PLAYER,		// 関数を使う時に選択する用
	SELECTMOTION_PLAYERBLEND,
	SELECTMOTION_ENEMY,
	SELECTMOTION_MAX
} SELECTMOTION;

//-----------------------------------------------------------------------------
// キーの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	float fPosX;		// 位置X
	float fPosY;		// 位置Y
	float fPosZ;		// 位置Z
	float fRotX;		// 向きX
	float fRotY;		// 向きY
	float fRotZ;		// 向きZ
} KEY;

//-----------------------------------------------------------------------------
// キー情報の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	int nFrame;			// 再生フレーム
	KEY aKey[10];		// キー (パーツ最大数分)
} KEY_INFO;

//-----------------------------------------------------------------------------
// モーション情報の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	bool bLoop;					// ループの有無
	int nNumKey;				// キーの総数
	KEY_INFO aKeyInfo[10];		// キー情報	(キーの最大数)
} MOTION_INFO;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitMotion(void);
void UninitMotion(void);
void UpdateMotion(void);
void DrawMotion(void);
KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
void StartMotion(SELECTMOTION motionSelect, MOTIONTYPE motionType, int nIdxEnemy);
void MotionText(const char* cXFileName);


#endif