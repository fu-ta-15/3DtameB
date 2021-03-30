//-----------------------------------------------------------------------------
//
// ボス攻撃の処理 ヘッダー [boss_attack.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _BOSS_ATK_H_
#define _BOSS_ATK_H_
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define BOSS_ATTACK_MAX (8)	// 同時に出せる最大数
#define BOSS_ATTACK_OBJ (2)	// 必要なオブジェ数
#define BOSS_ATTACK_DMG (3)
#define BOSS_ATTACK_RADIUS (100.0f)
//-----------------------------------------------------------------------------
// 攻撃床の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 向き
	LPDIRECT3DVERTEXBUFFER9 pVtx;	// 頂点バッファ

	float fFloorRatio;		// 床を広げる時の割合
	bool bDraw;				// 描画フラグ
	bool bAttackFlag;		// 攻撃フラグ
} AttackFloor;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitBossATK(void);
void UninitBossATK(void);
void UpdateBossATK(void);
void DrawBossATK(void);
void BeginBossAttack(D3DXVECTOR3 pos);

#endif
