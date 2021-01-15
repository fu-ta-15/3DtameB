#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// ���f���̏��� [model.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include <stdio.h>

//
// �v���g�^�C�v�錾
//
void MoveModel(float fMoveAngleDegree, float fMoveSpeed);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;													// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel;													// �}�e���A��(�ގ�)�ւ̃|�C���^
DWORD g_nNumMatModel = 0;														// �}�e���A���̐�
Model g_Model;																	// ���f���̏��
D3DXVECTOR3 g_posModel;															// �ʒu
D3DXVECTOR3 g_rotModel;															// ����
D3DXMATRIX g_mtxWorldModel;														// ���[���h�}�g���b�N�X
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;										// ���f���̍ő�l�A�ŏ��l
LPDIRECT3DTEXTURE9 g_apTextureModel[10] = { NULL };								// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_RotDiff[2];														// test

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();														// �f�o�C�X�̎擾

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\chair_wood00.x",			// �ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,						// �Œ�
		pDevice,								// �f�o�C�X
		NULL,									// NULL�Œ�
		&g_pBuffMatModel,						// �}�e���A��
		NULL,									// NULL�Œ�
		&g_nNumMatModel,						// �}�e���A����
		&g_pMeshModel);							// ���b�V��

	//�����ʒu�A����
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����ʒu
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��������

	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W���
		
		//�ő�l�ŏ��l�𔲂��o��
		if (vtx.x > g_vtxMaxModel.x) g_vtxMaxModel.x = vtx.x;	// X�ő�l
		if (vtx.x < g_vtxMinModel.x) g_vtxMinModel.x = vtx.x;	// X�ŏ��l
		if (vtx.y > g_vtxMaxModel.y) g_vtxMaxModel.y = vtx.y;	// Y�ő�l
		if (vtx.y < g_vtxMinModel.y) g_vtxMinModel.y = vtx.y;	// Y�ŏ��l
		if (vtx.z > g_vtxMaxModel.z) g_vtxMaxModel.z = vtx.z;	// Z�ő�l
		if (vtx.z < g_vtxMinModel.z) g_vtxMinModel.z = vtx.z;	// Z�ŏ��l

		pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y�������|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

	//�}�e���A�����ւ̃|�C���^
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
		}
	}
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	Camera *pCamera = GetCamera();
	D3DXVECTOR3 RotDiff;

	//�����v�Z
	RotDiff.y = g_Model.rotDest.y - g_Model.rot.y;

	//�e�X�g
	g_RotDiff[0].y = g_Model.rotDest.y - g_Model.rot.y;
	g_RotDiff[1].y = (D3DX_PI * 2) + g_RotDiff[0].y;

	//�����̈ꕔ�𑫂��Ă���
	//if (g_Model.rot.y < -D3DX_PI / 2 + pCamera->rot.y)
	//{
	//	if (g_Model.rotDest.y > 0)
	//	{
	//		g_Model.rot.y += -RotDiff2.y * 0.05f;
	//	}
	//	else
	//	{
	//		g_Model.rot.y += RotDiff.y * 0.05f;
	//	}
	//}
	//else if (g_Model.rot.y > D3DX_PI / 2 + pCamera->rot.y)
	//{
	//	if (g_Model.rotDest.y < 0)
	//	{
	//		g_Model.rot.y += ((D3DX_PI * 2) + RotDiff.y) * 0.05f;
	//	}
	//	else
	//	{
	//		g_Model.rot.y += RotDiff.y * 0.05f;
	//	}
	//}
	//else
	//{
	//	g_Model.rot.y += RotDiff.y * 0.05f;
	//}
	//g_Model.rot.y += RotDiff.y * 0.05f;

	//�e�X�g1
	//if (g_RotDiff[0].y > g_RotDiff[1].y)
	//{
	//	g_Model.rot.y += g_RotDiff[1].y * 0.05f;
	//}
	//else
	//{
	//	g_Model.rot.y += g_RotDiff[0].y * 0.05f;
	//}

	//������D3DX_PI�ȏ�(�����ȏ�)�̏ꍇ�A�t��]
	if (g_RotDiff[0].y > D3DX_PI)
	{
		g_Model.rot.y -= ((D3DX_PI * 2) - g_RotDiff[0].y) * MODEL_SMOOTHTURNSPEED;
	}
	else if (g_RotDiff[0].y < -D3DX_PI)
	{
		g_Model.rot.y += ((D3DX_PI * 2) + g_RotDiff[0].y) * MODEL_SMOOTHTURNSPEED;
	}
	else
	{
		g_Model.rot.y += g_RotDiff[0].y * MODEL_SMOOTHTURNSPEED;
	}

	//���f���̉�]
	if (GetKeyboardPress(DIK_Q) == true)
	{// ����]
		g_Model.rotDest.y -= MODEL_SMOOTHTURNSPEED;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//	�E��]
		g_Model.rotDest.y += MODEL_SMOOTHTURNSPEED;
	}

	/* ���f���̈ړ� */
	if (GetKeyboardPress(DIK_UP) == true)
	{
		if (GetKeyboardPress(DIK_RIGHT) == true) MoveModel(45.0f, MODEL_MOVESPEED);				// �E�O
		else if (GetKeyboardPress(DIK_LEFT) == true) MoveModel(-45.0f, MODEL_MOVESPEED);		// ���O
		else MoveModel(180.0f, MODEL_MOVESPEED);													// �O
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		if (GetKeyboardPress(DIK_RIGHT) == true) MoveModel(135.0f, MODEL_MOVESPEED);			// �E���
		else if (GetKeyboardPress(DIK_LEFT) == true) MoveModel(-135.0f, MODEL_MOVESPEED);		// �����
		else MoveModel(0.0f, MODEL_MOVESPEED);												// ���
	}
	else if (GetKeyboardPress(DIK_LEFT) == true) MoveModel(-90.0f, MODEL_MOVESPEED);			// ��
	else if (GetKeyboardPress(DIK_RIGHT) == true) MoveModel(90.0f, MODEL_MOVESPEED);			// �E

	/* 3.14��������}�t�� */
	//���f������
	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}
	//���f���ڕW����
	if (g_Model.rotDest.y > D3DX_PI)
	{
		g_Model.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_Model.rotDest.y < -D3DX_PI)
	{
		g_Model.rotDest.y += D3DX_PI * 2.0f;
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;												// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;														// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;															// �}�e���A���f�[�^�ւ̃|�C���^
	pDevice = GetDevice();														// �f�o�C�X�̎擾

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Model.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

Model *GetModel(void)
{
	return &g_Model;
}

D3DXVECTOR3 *GetVariableTest(void)
{
	return &g_RotDiff[0];
}

void MoveModel(float fMoveAngleDegree, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// �J�����̏��擾

	g_Model.pos.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_Model.pos.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_Model.rotDest.y = (pCamera->rot.y - D3DXToRadian(fMoveAngleDegree) * fMoveSpeed) * -1 ;
}