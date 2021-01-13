#pragma once
#include "DirectX.h"
#define BILLBOARD_NUMBER (500)
#define BILLBOARD_TEXTURE_NUM (5)
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR2 size; //�傫��
	D3DXVECTOR3 move; //�ړ�
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 nor; //�@�������@normal vector
	bool bUse, bAnime;
	int nPatternAnime, nTextureID;
}BILLBOARD;

HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(void);