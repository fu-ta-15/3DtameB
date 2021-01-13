#pragma once
#include "DirectX.h"

#define TUTORIAL_COMPONENT (2)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	bool bUse;
}TUTORIAL;

HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);