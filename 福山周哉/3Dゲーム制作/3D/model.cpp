//===========================================================================================================
//
// �|���S���̐ݒ� [polygon.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "model.h"
#include "input.h"
#include "camera.h"

//===========================================================================================================
//�O���[�o���ϐ�
//===========================================================================================================
LPD3DXMESH g_pMeshModel = NULL;					//���b�V���ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;			//�}�e���A���ւ̃|�C���^
DWORD g_nNumMatModel = 1;						//�}�e���A���̐�
D3DXVECTOR3 g_posModel;							//�ʒu
D3DXVECTOR3 g_rotModel;							//����
D3DXMATRIX g_mtxWorldModel;						//���[���h�}�g���b�N�X

//===========================================================================================================
//������
//===========================================================================================================
void InitModel(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\hata.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMatModel,NULL,&g_nNumMatModel,&g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================================================================================
//�I��
//===========================================================================================================
void UninitModel(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
}

//===========================================================================================================
//�X�V����
//===========================================================================================================
void UpdateModel(void)
{
	g_rotModel.y = 0.5f;

	//���f���̈ړ�
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_posModel.z += sinf (g_rotModel.y) * 1;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_posModel.z -= sinf (g_rotModel.y) * 1;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_posModel.x -= cosf (g_rotModel.y) * 1;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_posModel.x += cosf (g_rotModel.y) * 1;
	}
}

//===========================================================================================================
//�`�揈��
//===========================================================================================================
void DrawModel(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�f�o�C�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixTranslation(&mtxRot, g_rotModel.x, g_rotModel.y, g_rotModel.z);
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

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

