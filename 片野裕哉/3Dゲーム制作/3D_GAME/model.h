////
////
//// ���f���w�b�_�[ [model.h]
////
////
////
//#ifndef _MODEL_H_
//#define _MODEL_H_
//#include "main.h"
//
////
//// �\����
////
//typedef struct
//{
//	D3DXVECTOR3 pos;			// �ʒu
//	D3DXVECTOR3 move;			// �ړ���
//	D3DXVECTOR3 rot;			// ����
//	D3DXVECTOR3 rotDest;		// �ړI�̌���
//	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
//} PLAYER;
//
//typedef struct
//{
//	D3DXVECTOR3 pos;			// �ʒu
//	D3DXVECTOR3 move;			// �ړ���
//	D3DXVECTOR3 rot;			// ����
//	D3DXVECTOR3 rotDest;		// �ړI�̌���
//	D3DXVECTOR3 vtxMinModel;	// ���f���̍ŏ��l
//	D3DXVECTOR3 vtxMaxModel;	// ���f���̍ő�l
//	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
//
//	LPD3DXMESH pMeshModel = NULL;		// ���b�V��(���_���)�ւ̃|�C���^
//	LPD3DXBUFFER pBuffMatModel = NULL;	// �}�e���A��(�ގ����)�ւ̃|�C���^
//	DWORD nNumMatModel = NULL;			// �}�e���A���̐�
//} MODEL;
//
////
//// �v���g�^�C�v�錾
////
//void InitModel(void);
//void UninitModel(void);
//void UpdateModel(void);
//void DrawModel(void);
//MODEL *GetModel(void);
//
//#endif