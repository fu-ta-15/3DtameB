#pragma once
#include "DirectX.h"

#define TITLE_COMPONENT (2)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}TITLE;

HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);