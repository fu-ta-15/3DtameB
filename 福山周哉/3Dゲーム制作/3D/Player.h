//===================================================================
//
// �v���C���[�̏����@[player.h]
// Author: fukuyama syuya
//
//===================================================================

#ifndef PLAYER_H_
#define PLAYER_H_

#include "main.h"

//===========================================================================================================
// �}�N����`
//===========================================================================================================
#define MAX_MODEL (15)					//���f���̍ő吔

//===================================================================
//���f���̍\����
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;									//���f���̈ʒu
	D3DXVECTOR3 posDest;								//�ړI�̃��f���̈ʒu
	D3DXVECTOR3 rot;									//���f���̌���
	D3DXVECTOR3 rotDest;								//�ړI�̃��f���̌���
	D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshModel = NULL;						//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel = NULL;					//�}�e���A���ւ̃|�C���^
	DWORD nNumMatModel = 1;								//�}�e���A���̐�
	D3DXVECTOR3 VtxMinModel, g_VtxMaxModel;				//���f���̍ŏ��l�E�ő�l
	LPDIRECT3DTEXTURE9 apTextureModel[256] = {};		//�e�N�X�`���ւ̃|�C���^
	int nIdxModelParent;								//�e�̃C���f�b�N�X
}Model;

//===================================================================
//�v���C���[�̍\����
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 posDest;				//�ړI�̃��f���̈ʒu
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 rotDest;				//�ړI�̃��f���̌���
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	Model aModel[MAX_MODEL];			//���f��(�p�[�c)
	int nNumModel;						//�p�[�c��
}PLAYER;

typedef enum
{
	MODEL_LABEL_BODY = 0,	// ����
	MODEL_LABEL_HEAD,		// ����
	MODEL_LABEL_ARM_T_R,	// �E�r(���`�I)
	MODEL_LABEL_ARM_U_R,	// �E�r(�I�`���)
	MODEL_LABEL_HAND_R,		// �E��
	MODEL_LABEL_ARM_T_L,	// ���r(���`�I)
	MODEL_LABEL_ARM_U_L,	// ���r(�I�`���)
	MODEL_LABEL_HAND_L,		// ����
	MODEL_LABEL_LEG_T_R,	// �E�r(��)
	MODEL_LABEL_LEG_U_R,	// �E�r(����)
	MODEL_LABEL_FOOT_R,		// �E��
	MODEL_LABEL_LEG_T_L,	// ���r(��)
	MODEL_LABEL_LEG_U_L,	// ���r(����)
	MODEL_LABEL_FOOT_L,		// ����
	MODEL_LABEL_BODYSEC,	// �� 
	MODEL_LABEL_MAX,
} MODEL_LABEL;

//===========================================================================================================
// �v���g�^�C�v�錾
//===========================================================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif

