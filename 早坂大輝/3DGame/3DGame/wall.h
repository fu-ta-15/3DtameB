//=============================================================================
//
// �ǂ̏��� [wall.h]
// Author:Taiki Hayasaka
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//=============================================================================
// �ǂ̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Wall;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetVertexWall(int nCntWall);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Wall *GetWall(void);

#endif

