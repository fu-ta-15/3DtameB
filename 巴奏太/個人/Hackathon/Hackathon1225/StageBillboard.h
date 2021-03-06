#pragma once
#include "DirectX.h"
#define BILLBOARD_NUMBER (500)
#define BILLBOARD_TEXTURE_NUM (5)
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR2 size; //大きさ
	D3DXVECTOR3 move; //移動
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 nor; //法線向き　normal vector
	bool bUse, bAnime;
	int nPatternAnime, nTextureID;
}BILLBOARD;

HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(void);