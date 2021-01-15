//===================================================================
//
// �v���C���[�̏����@[player.cpp]
// Author: fukuyama syuya
//
//===================================================================

#include "Player.h"
#include "input.h"
#include "camera.h"

//===========================================================================================================
// �O���[�o���ϐ�
//===========================================================================================================
PLAYER g_Player;											//���f���̏��

char *g_aModelFile[MODEL_LABEL_MAX] =
{
	"data\\MODEL\\DANB_MODEL\\body1.x",		// ����
	"data\\MODEL\\DANB_MODEL\\danbo.x",		// ����
	"data\\MODEL\\DANB_MODEL\\armR1.x",		// �E�r(���`�I)
	"data\\MODEL\\DANB_MODEL\\armR.x",		// �E�r(�I�`���)
	"data\\MODEL\\DANB_MODEL\\handR.x",		// �E��
	"data\\MODEL\\DANB_MODEL\\armL1.x",		// ���r(���`�I)
	"data\\MODEL\\DANB_MODEL\\armL.x",		// ���r(�I�`���)
	"data\\MODEL\\DANB_MODEL\\handL.x",		// ����
	"data\\MODEL\\DANB_MODEL\\legR.x",		// �E�r(��)
	"data\\MODEL\\DANB_MODEL\\legR.x",		// �E�r(����)
	"data\\MODEL\\DANB_MODEL\\footR.x",		// �E��
	"data\\MODEL\\DANB_MODEL\\legR.x",		// ���r(��)
	"data\\MODEL\\DANB_MODEL\\legR.x",		// ���r(����)
	"data\\MODEL\\DANB_MODEL\\footR.x",		// ����
	"data\\MODEL\\DANB_MODEL\\body2.x"		// ��
};		// ���f���̃t�@�C���ꗗ

//===========================================================================================================
// ������
//===========================================================================================================
void InitPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		D3DXLoadMeshFromX(g_aModelFile[nCntModel], D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[nCntModel].pBuffMatModel, NULL, &g_Player.aModel[nCntModel].nNumMatModel, &g_Player.aModel[nCntModel].pMeshModel);

		D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Player.aModel[nCntModel].apTextureModel[nCntMat]);
			}
		}

		int nNumVtx;					//���_��

		DWORD sizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y

		BYTE *pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^

										//���_�����擾
		nNumVtx = g_Player.aModel[nCntModel].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMeshModel->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;				//���_���W�̑��



			pVtxBuff += sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@�̃A�����b�N
		g_Player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		g_Player.nNumModel++;
	}
	//�e�p�[�c�̊K�w�\���̐ݒ�
	g_Player.aModel[0].nIdxModelParent = -1;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0, 16.0, 0.0);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//�e�p�[�c�̊K�w�\���̐ݒ�
	g_Player.aModel[1].nIdxModelParent = 0;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0, 23.0, 0.0);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//�e�p�[�c�̊K�w�\���̐ݒ�
	g_Player.aModel[2].nIdxModelParent = 0;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[2].pos = D3DXVECTOR3(-7.0, 18.0, 0.0);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[3].nIdxModelParent = 2;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[3].pos = D3DXVECTOR3(-5.0, 0.0, 0.0);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[4].nIdxModelParent = 3;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[4].pos = D3DXVECTOR3(-8.0, 0.0, 0.0);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[5].nIdxModelParent = 0;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[5].pos = D3DXVECTOR3(7.0, 18.0, 0.0);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[6].nIdxModelParent = 5;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[6].pos = D3DXVECTOR3(5.0, 0.0, 0.0);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[7].nIdxModelParent = 6;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[7].pos = D3DXVECTOR3(8.0, 0.0, 0.0);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[8].nIdxModelParent = 0;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[8].pos = D3DXVECTOR3(-4.0, 8.0, 0.0);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[9].nIdxModelParent = 8;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0, -7.3, 0.0);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[10].nIdxModelParent = 9;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[10].pos = D3DXVECTOR3(0.0, -10.0, 0.0);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[11].nIdxModelParent = 0;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[11].pos = D3DXVECTOR3(4.0, 8.0, 0.0);
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[12].nIdxModelParent = 11;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[12].pos = D3DXVECTOR3(0.0, -7.3, 0.0);
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[13].nIdxModelParent = 12;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[13].pos = D3DXVECTOR3(0.0, -10.0, 0.0);
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[14].nIdxModelParent = 0;

	//�ʒu�ƌ����̏����ݒ�
	g_Player.aModel[14].pos = D3DXVECTOR3(0.0, 7.0, 0.0);
	g_Player.aModel[14].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//���f���̏�����
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================================================================================
// �I��
//===========================================================================================================
void UninitPlayer(void)
{
	//���_�o�b�t�@�̊J��
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMatModel->Release();
			g_Player.aModel[nCntModel].pBuffMatModel = NULL;
		}

		//�e�N�X�`���̊J��
		if (g_Player.aModel[nCntModel].nNumMatModel != NULL)
		{
			g_Player.aModel[nCntModel].pMeshModel->Release();
			g_Player.aModel[nCntModel].pMeshModel = NULL;
		}
	}
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;

	pCamera = GetCamera();

	//���f���̈ړ�
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Player.pos.x += sinf(pCamera->rot.y) * 1;
		g_Player.pos.z += cosf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = D3DX_PI + pCamera->rot.y;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Player.pos.z -= cosf(pCamera->rot.y) * 1;
		g_Player.pos.x -= sinf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = 0.0f + pCamera->rot.y;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.pos.x -= cosf(pCamera->rot.y) * 1;
		g_Player.pos.z += sinf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = D3DX_PI / 2 + pCamera->rot.y;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.pos.x += cosf(pCamera->rot.y) * 1;
		g_Player.pos.z -= sinf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = -D3DX_PI / 2 + pCamera->rot.y;
	}

	g_Player.rot.y = g_Player.rotDest.y;

	//���f���̌���
}

//===========================================================================================================
// �`�揈��
//===========================================================================================================
void DrawPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�f�o�C�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�̃|�C���^

	pDevice = GetDevice();						//�f�o�C�X�̎擾

	// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// �v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �v���C���[�̃}�e���A���f�[�^�ւ̃|�C���^���擾
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;				//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;								//�e�̃}�g���b�N�X

		// ���f���̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// ���f���̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		// ���f���̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		//�e�̃}�g���b�N�X��ݒ�
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;
		}

		//�Z�o�������f���̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
						   &g_Player.aModel[nCntModel].mtxWorld,
			               &mtxParent);

		// ���f���̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Player.aModel[nCntModel].apTextureModel[nCntMat]);

			//���f���p�[�c�̕`��
			g_Player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//===========================================================================================================
// ���f���̎擾
//===========================================================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}