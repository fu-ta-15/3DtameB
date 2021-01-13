#pragma once
#include "DirectX.h"
#define BILLBOARDMOD_NUMBER (200)
#define BILLBOARDMOD_TEXTURE_NUM (4)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR2 size; //�傫��
	D3DXVECTOR3 move; //�ړ�
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 nor; //�@�������@normal vector
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