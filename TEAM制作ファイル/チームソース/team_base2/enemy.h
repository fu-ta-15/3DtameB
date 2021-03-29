//-----------------------------------------------------------------------------
//
// 敵の処理 ヘッダー [enemy.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "game.h"
#include "player.h"
#include <time.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define ENENY_AMOUNT_SNAKE (32)		// 蛇の敵を用意する数
#define ENEMY_AMOUNT_ROBOT (32)		// ロボット
#define ENEMY_AMOUNT_MAX (ENENY_AMOUNT_SNAKE + ENEMY_AMOUNT_ROBOT)			// 用意している敵の最大数
#define ENEMY_MODEL_PARTS_MAX (10)	// 使用できる最大パーツ数
#define ENEMY_ROBOT_MODELPARTS (10)	// amount of parts of robot model
#define ENEMY_ROBOT001_MODELPARTS (8)	

#define ENEMY_ROBOT000_COL_HEIGHT (20)				// ロボット000の高さ (判定用)
#define ENEMY_ROBOT000_COL_WIDTH (20)				// 幅
#define ENEMY_ROBOT001_COL_HEIGHT (35)				// 001
#define ENEMY_ROBOT001_COL_WIDTH (35)				// 

#define ENEMY_KNOCKBACK (10)			// ノックバック量
#define ENEMY_INVINCIBLE_TIME (500)		// 攻撃された時の無敵時間
#define ENEMY_FALLSPEED (0.4f)			// 落下速度
#define ENEMY_DETECT_RADIUS (200)		// 敵感知距離
#define ENEMY_DETECT_RADIUS_RANGED (500)
#define ENEMY_MOVESPEED (0.2f)			// 移動速度
#define ENEMY_ATTACK_RADIUS (35)		// 攻撃範囲
#define ENEMY_ATTACK_RADIUS_RANGED (300)
#define ENEMY_ATTACK_COOLTIME (1000)	// 攻撃CT
#define ENEMY_ATTACK_BULLETSPEED (2)
#define ENEMY_HP_MAX (3)				// 敵の体力

//-----------------------------------------------------------------------------
// enemy type
//-----------------------------------------------------------------------------
typedef enum
{
	ENEMYTYPE_ROBOT000,	// robot
	ENEMYTYPE_ROBOT001,
	ENEMYTYPE_BOSS,
	ENEMYTYPE_MAX
} ENEMYTYPE;

//-----------------------------------------------------------------------------
// 敵の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	D3DXVECTOR3 posOld;							// 前回の位置
	D3DXVECTOR3 move;							// 移動
	D3DXVECTOR3 rot;							// 向き
	D3DXVECTOR3 rotDest;						// 目標の向き
	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	ENEMYTYPE type;								// 敵の種類
	Model aModel[ENEMY_MODEL_PARTS_MAX];		// パーツ
	float fWidth;								// 幅
	float fDepth;								// 奥行
	float fHeight;								// 高さ

	bool bPlayMotion;							// モーション再生状態
	MOTION_INFO aMotionInfo[MOTION_MAX];		// モーション情報	 (モーションの最大数)
	MOTIONTYPE motionType;						// モーションタイプ
	bool bLoopMotion;							// ループの有無
	int nCurrentMotion;							// 現在のモーション
	int nNumMotion;								// モーション数
	int nNumKey;								// キー数
	int nKey;									// キーナンバー
	int nCounterMotion;							// モーションカウンター
	KEY DefKey[ENEMY_MODEL_PARTS_MAX];	// 初期配置

	int nLifeMax;								// 最大体力
	int nLife;									// 体力
	int nIdx;									// 自分のID
	bool bUse;									// 使用中か
	bool bHit;									// 攻撃判定中か
	bool bInvincible;							// 無敵状態
	bool bAttack;								// 攻撃した
	DWORD dwTimeInv;							// 無敵時間計算用
	DWORD dwTimeAtk;							// 攻撃時間計算用
} Enemy;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy *GetEnemy(void);
Model *GetEnemyModelParts(ENEMYTYPE type);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type);
void SetTextEnemy(void);

#endif

