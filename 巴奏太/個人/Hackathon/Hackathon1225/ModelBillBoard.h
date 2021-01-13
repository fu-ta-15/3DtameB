#pragma once
#include "DirectX.h"
#define BILLBOARDMOD_NUMBER (200)
#define BILLBOARDMOD_TEXTURE_NUM (4)
typedef struct
{
	D3DXVECTOR3 pos; //ˆÊ’u
	D3DXVECTOR2 size; //‘å‚«‚³
	D3DXVECTOR3 move; //ˆÚ“®
	D3DXVECTOR3 rot; //Œü‚«
	D3DXVECTOR3 nor; //–@üŒü‚«@normal vector
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