#pragma once
#include "DirectX.h"

#define TITLE1_COMPONENT (3)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}TITLE1;

HRESULT InitTitle1(void);
void UninitTitle1(void);
void UpdateTitle1(void);
void DrawTitle1(void);