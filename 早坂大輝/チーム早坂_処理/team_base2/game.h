//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author:Taiki Hayasaka, Sota Tomoe
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef struct
{
	int nStageNum;
} Stage;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
Stage *GetStage(void);
void SetWall(void);
void SetPause(bool bPause);

#endif

