//
//
// �\���b�h�w�b�_�[ [solid.h]
//
//
//
#ifndef _SOLID_H_
#define _SOLID_H_
#include "main.h"

//
// �v���g�^�C�v�錾
//
HRESULT InitSolid(void);
void UninitSolid(void);
void UpdateSolid(void);
void DrawSolid(void);
void SetSolid(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetVertexSolid(int nIdx);

#endif