#pragma once
#include "DirectX.h"

#define STAGEMODEL_NUM_RED (50)
#define STAGEMODEL_NUM_BLUE (50)
#define STAGEMODEL_NUM_YELLOW (50)
#define STAGEMODEL_NUM_GREEN (50)
#define STAGEMODEL_NUM_ALL (200)

typedef enum
{
	MODELTYPE_RED = 0,	// RED
	MODELTYPE_BLUE,		// BLUE
	MODELTYPE_YELLOW,	// YELLOW
	MODELTYPE_GREEN,	// GREEN
	MODELTYPE_MAX
}MODELTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR2 size;
	D3DXVECTOR3 rot;
	bool bUse;
	MODELTYPE modelType;
	float fMoveSpeed;
}MODEL;

void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);