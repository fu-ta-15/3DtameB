//=========================================================================================================================
//
// ���f�� [model.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "model.h"
#include "input.h"
#include "camera.h"

//
// �}�N����`
//
#define MODEL_SPD (2.0f)	// ���f���̈ړ���
#define SPD_DECAY (0.4f)	// �ړ��ʂ̌����W��

//
// �O���[�o���ϐ�
//
LPD3DXMESH g_pMeshModel = NULL;				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;		// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatModel = NULL;				// �}�e���A���̐�
MODEL g_Model;								// ���f���̏��

//
// ����������
//
void InitModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data\\MODEL\\car000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//
// �I������
//
void UninitModel(void)
{
	// ���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// �}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

}


//
// �X�V����
//
void UpdateModel(void)
{
	Camera pCamera = *GetCamera();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetKeyboardPress(DIK_UP) == true)
	{
		//if (pCamera.rot.y > 0.0f)
		//{
			g_Model.rot.y = (-D3DX_PI + pCamera.rot.y);

			//if (g_Model.rotObjective.y + g_Model.rot.y <= 0.0f)
			//{
			//	g_Model.rot.y += (g_Model.rotObjective.y - g_Model.rot.y) * 0.2f;
			//}
			//else if (g_Model.rotObjective.y + g_Model.rot.y > 0.0f)
			//{
			//	g_Model.rot.y += (g_Model.rotObjective.y + g_Model.rot.y) * 0.2f;
			//}
		//}
		//if (pCamera.rot.y <= 0.0f)
		//{
		//	g_Model.rotObjective.y = (D3DX_PI + pCamera.rot.y);

		//	if (g_Model.rotObjective.y + g_Model.rot.y <= 0.0f)
		//	{
		//		g_Model.rot.y += (g_Model.rotObjective.y + g_Model.rot.y) * 0.2f;
		//	}
		//	else if (g_Model.rotObjective.y + g_Model.rot.y > 0.0f)
		//	{
		//		g_Model.rot.y += (g_Model.rotObjective.y - g_Model.rot.y) * 0.2f;
		//	}
		//}

		if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y += D3DX_PI * 2.0f;
		}
		g_Model.move.x += sinf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z += cosf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.rot.y = (pCamera.rot.y);

		g_Model.move.x -= sinf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z -= cosf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.rot.y = (D3DX_PI / 2 - pCamera.rot.y);

		g_Model.move.x -= cosf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z += sinf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.rot.y = (-D3DX_PI / 2 - pCamera.rot.y);

		g_Model.move.x += cosf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z -= sinf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Model.rot.y -= 0.2f;
		if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Model.rot.y += 0.2f;
		if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y -= D3DX_PI * 2.0f;
		}
	}

	g_Model.move.x += (0.0f - g_Model.move.x) * SPD_DECAY;
	g_Model.move.z += (0.0f - g_Model.move.z) * SPD_DECAY;

	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.z += g_Model.move.z;
}


//
// �`�揈��
//
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Model.mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);

	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);

	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL *)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//
// ���f���̎擾
//
MODEL *GetModel(void)
{
	return &g_Model;
}
