#pragma once
#include "DirectX.h"

#define UI_COMPONENT (13)
#define UI_TYPE (2)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTexture, nPatternAnime;
	bool bUse;
	int nDisplayNumber, nZeroNumber, nMultipleNumber; //score ‚É‚Â‚¢‚Ä
}UI;

HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);