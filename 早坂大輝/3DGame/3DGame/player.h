//=============================================================================
//
// �v���C���[�̏��� [model.h]
// Author:Taiki Hayasaka
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_USE_MODEL (2)	//���f���̍ő吔

//=============================================================================
// ���f���̍\����
//=============================================================================
typedef struct
{
	LPD3DXMESH pMesh;		//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A���̐�
	D3DXVECTOR3 pos;		//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
}Model;

//=============================================================================
// �v���C���[�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���S���W
	D3DXVECTOR3 rot;		//��]
	D3DXVECTOR3 rotDest;	//�ړI�̌���
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float boost;			//�W�����v�u�[�X�g
	bool bUse;				//�g�p���Ă��邩
	int nShadow;			//�e

	Model aModel[MAX_USE_MODEL];	//���f��(�p�[�c)
	int nNumModel;					//���f��(�p�[�c)��
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void); 
Player *GetPlayer(void);

#endif
