//
//
// �p�[�e�B�N���w�b�_�[ [particle.h]
//
//
//
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
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
	int nLife;					// ����
	bool bUse;					// �g�p���Ă��邩�ǂ���
} PARTICLE;

//
// �v���g�^�C�v�錾
//
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move);
void SetVertexParticle(int nIdx);

#endif