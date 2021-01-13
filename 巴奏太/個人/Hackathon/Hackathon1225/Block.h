#pragma once
#include "DirectX.h"

#define STAGEMODEL_NUM (50)
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 size;
	D3DXVECTOR3 rot;
	bool bUse;
	int ID;
	float fMoveSpeed;
}MODEL;

void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);