//=============================================================================
//
// ���f���̏��� [model.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH g_pMeshModel = NULL;			//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	//�}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatModel = 0;				//�}�e���A���̐�
D3DXVECTOR3 g_posModel;					//�ʒu
D3DXVECTOR3 g_rotModel;					//����
D3DXVECTOR3 g_moveModel;				//�ړ���
D3DXMATRIX g_mtxWorldModel;				//���[���h�}�g���b�N�X
int nCntBoost;

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/sieldcell000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̏����ݒ�
	nCntBoost = 0.0f;
}

//=============================================================================
// �I������
//=============================================================================
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

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	//�u�[�X�g�c��
	if (nCntBoost < 100)
	{
		nCntBoost++;
	}

	//�ʒu�̍X�V
	g_posModel.x += g_moveModel.x;
	g_posModel.y += g_moveModel.y;
	g_posModel.z += g_moveModel.z;

	//�ړ��ʂ̌���
	g_moveModel.x += (0.0f - g_moveModel.x) * 0.2f;
	g_moveModel.y += (0.0f - g_moveModel.y) * 0.2f;
	g_moveModel.z += (0.0f - g_moveModel.z) * 0.2f;

	//�d��
	if (g_posModel.y > 0.0f)
	{
		g_moveModel.y -= 0.5;
	}
	if (g_posModel.y < 0.0f)
	{
		g_posModel.y = 0.0f;
	}

	//���V
	if (GetKeyboardPress(DIK_J) == true)
	{
		if (nCntBoost > 0)
		{
			g_moveModel.y += 1;
			nCntBoost -= 3;
		}
	}

	//���f���̈ړ�
	if (GetKeyboardPress(DIK_UP) == true)		//����������
	{
		//�O�ړ�
		g_posModel.x += sinf(pCamera->rot.y) * 2.0f;
		g_posModel.x += sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z += cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z += cosf(pCamera->rot.y) * 2.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)		//����������
	{
		//��ړ�
		g_posModel.x -= sinf(pCamera->rot.y) * 2.0f;
		g_posModel.x -= sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= cosf(pCamera->rot.y) * 2.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)	//����������
	{
		//�E�ړ�
		g_posModel.x += cosf(pCamera->rot.y) * 2.0f;
		g_posModel.x += cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= sinf(pCamera->rot.y) * 2.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)		//����������
	{
		//���ړ�
		g_posModel.x -= cosf(pCamera->rot.y) * 2.0f;
		g_posModel.x -= cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z += sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z += sinf(pCamera->rot.y) * 2.0f;
	}


	//���f���̌���
	if (GetKeyboardPress(DIK_LSHIFT) == true)	//���V�t�g��������
	{
		//����]
		g_rotModel.y -= 0.05f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)	//�E�V�t�g��������
	{
		//�E��]
		g_rotModel.y += 0.05f;
	}

	//���Z�b�g
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

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

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}