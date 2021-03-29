//-----------------------------------------------------------------------------
//
// ボスの処理 ヘッダー [boss.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include <time.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define BOSS_MODEL_PARTS (8)
#define BOSS_COL_HEIGHT (50)	// ボスの高さ (判定用)
#define BOSS_COL_WIDTH (35)		// 幅

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
	Model aModel[BOSS_MODEL_PARTS];		// パーツ
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
	KEY DefKey[BOSS_MODEL_PARTS];	// 初期配置

	int nLifeMax;								// 最大体力
	int nLife;									// 体力
	bool bUse;									// 使用中か
	bool bHit;									// 攻撃判定中か
	bool bInvincible;							// 無敵状態
	bool bAttack;								// 攻撃した
	DWORD dwTimeInv;							// 無敵時間計算用
	DWORD dwTimeAtk;							// 攻撃時間計算用
} Boss;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
Boss *GetBoss(void);
void SetBoss(D3DXVECTOR3 pos, ENEMYTYPE type);
#endif


