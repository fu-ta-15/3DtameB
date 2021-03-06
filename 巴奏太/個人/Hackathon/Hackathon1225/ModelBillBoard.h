#pragma once
#include "DirectX.h"
#define BILLBOARDMOD_NUMBER (200)
#define BILLBOARDMOD_TEXTURE_NUM (4)
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR2 size; //大きさ
	D3DXVECTOR3 move; //移動
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 nor; //法線向き　normal vector
	D3DXMATRIX mtxworld;
	bool bUse, bAnime;
	int nPatternAnime, nTextureID;
}BILLBOARDMOD;

HRESULT InitBillboardMod(void);
void UninitBillboardMod(void);
void UpdateBillboardMod(void);
void DrawBillboardMod(void);
void SetBillboardMod(void);
void SetBillboardMod(D3DXVECTOR3 pos, int nType);