//
//
// ���f���w�b�_�[ [model.h]
//
//
//
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//
// �\����
//
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 rotObjective;	// �ړI�̌���
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
} MODEL;

//
// �v���g�^�C�v�錾
//
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);

#endif