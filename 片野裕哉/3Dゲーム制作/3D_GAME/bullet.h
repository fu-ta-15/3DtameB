//
//
// �o���b�g�w�b�_�[ [bullet.h]
//
//
//
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//
// �\����
//
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	bool bUse;					// �g�p���Ă��邩�ǂ���
} BULLET;

//
// �v���g�^�C�v�錾
//
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);
void SetVertexBullet(int nIdx);

#endif