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
	Camera *pCamera;
	pCamera = GetCamera();


	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Model.pos.x += sinf(pCamera->rot.y);
		g_Model.pos.z += cosf(pCamera->rot.y);
		g_Model.rot.y = pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.pos.x -= sinf(pCamera->rot.y);
		g_Model.pos.z -= cosf(pCamera->rot.y);
		g_Model.rot.y = pCamera->rot.y + D3DXToRadian(180.0f);
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.pos.x -= sinf(pCamera->rot.y + D3DXToRadian(90));
		g_Model.pos.z -= cosf(pCamera->rot.y + D3DXToRadian(90));
		g_Model.rot.y = pCamera->rot.y + D3DXToRadian(-90.0f);
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.pos.x -= sinf(pCamera->rot.y + D3DXToRadian(-90));
		g_Model.pos.z -= cosf(pCamera->rot.y + D3DXToRadian(-90));
		g_Model.rot.y = pCamera->rot.y + D3DXToRadian(90.0f);
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
		pDevice->SetTexture(0, NULL);

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

D3DXMATRIX *GetModelMTX(void)
{
	return &g_Model.mtxWorld;
}