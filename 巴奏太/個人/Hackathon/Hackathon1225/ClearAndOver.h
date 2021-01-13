#pragma once
#include "DirectX.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}OAC;

HRESULT InitOAC(void);
void UninitOAC(void);
void UpdateOAC(void);
void DrawOAC(void);
OAC *GetOAC(void);