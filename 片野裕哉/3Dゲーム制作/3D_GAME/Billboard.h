//
//
// �r���{�[�h�w�b�_�[ [Billboard.h]
//
//
//
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"

//
// �\����
//
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
} BILLBOARD;

//
// �v���g�^�C�v�錾
//
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);

#endif