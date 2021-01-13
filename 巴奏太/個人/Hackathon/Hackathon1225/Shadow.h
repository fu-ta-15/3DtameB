#pragma once
#include "DirectX.h"

typedef struct
{
	D3DXMATRIX mtWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR2 size;
	D3DXVECTOR2 move;
}SHADOW;

void SetShadow(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nIndex);//return ID of Shadow's mod
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void); 