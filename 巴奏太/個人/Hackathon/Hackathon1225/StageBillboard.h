#pragma once
#include "DirectX.h"
#define BILLBOARD_NUMBER (500)
#define BILLBOARD_TEXTURE_NUM (5)
typedef struct
{
	D3DXVECTOR3 pos; //ˆÊ’u
	D3DXVECTOR2 size; //‘å‚«‚³
	D3DXVECTOR3 move; //ˆÚ“®
	D3DXVECTOR3 rot; //Œü‚«
	D3DXVECTOR3 nor; //–@üŒü‚«@normal vector
	bool bUse, bAnime;
	int nPatternAnime, nTextureID;
}BILLBOARD;

HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(void);