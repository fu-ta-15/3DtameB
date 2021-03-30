//##################################################################################################################################################################//
//
// エフェクトヘッダファイル [effect.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//=====================================================================================================================================================================//
// マクロ定義
//=====================================================================================================================================================================//

typedef enum
{
	EFFECT_TYPE_NORMAL = 0,
	EFFECT_TYPE_PORTAL,
	EFFECT_TYPE_NOT,

	EFFECT_TYPE_MAX
}EFFECT_TYPE;


//=====================================================================================================================================================================//
// 弾の構造体
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 posdest;			// 位置
	D3DXVECTOR3 rot;
	D3DXVECTOR3 oldpos;				// 過去の位置
	D3DXVECTOR3 move;				// 移動量
	D3DXCOLOR color;				// 色
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	EFFECT_TYPE type;
	float EffectSizeW;				// 弾のサイズ
	float EffectSizeH;				// 弾のサイズ
	float fRadius;					// 半径
	float fAngle;					// 角度
	int nLife;						// 寿命
	int nCnt;
	int nFrame;
	int nIdx;						// 何個出すか
	bool bUse;						// 使用しているかどうか
}Effect;

//=====================================================================================================================================================================//
//プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void EffectOn(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float movex, float movez,float movey,int nIdx,int nLife);

void EffectPortalOn(void);
void SetEffectPortal(D3DXVECTOR3 pos,D3DXVECTOR3 posDest, D3DXCOLOR col, D3DXVECTOR3 move, D3DXVECTOR3 posdicetance, int nIdx, int nLife, int nFrame);

Effect *GetEffect(void);
#endif 

