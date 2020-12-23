//=========================================================================================================================
//
// �v���C���[ [player.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"

//
// �}�N����`
//
#define MODEL_SPD (2.0f)	// �v���C���[�̈ړ���
#define SPD_DECAY (0.4f)	// �ړ��ʂ̌����W��

//
// �O���[�o���ϐ�
//
PLAYER g_player;								// �v���C���[
char *g_aModelFile[MODEL_LABEL_MAX] =
{
	"data\\MODEL\\Katano_Model\\00_body_0.x",		// ����
	"data\\MODEL\\Katano_Model\\01_head_2.x",		// ����
	"data\\MODEL\\Katano_Model\\02_armR_T_0.x",		// �E�r(���`�I)
	"data\\MODEL\\Katano_Model\\03_armR_U_0.x",		// �E�r(�I�`���)
	"data\\MODEL\\Katano_Model\\04_handR_0.x",		// �E��
	"data\\MODEL\\Katano_Model\\05_armL_T_0.x",		// ���r(���`�I)
	"data\\MODEL\\Katano_Model\\06_armL_U_0.x",		// ���r(�I�`���)
	"data\\MODEL\\Katano_Model\\07_handL_0.x",		// ����
	"data\\MODEL\\Katano_Model\\08_legR_T_1.x",		// �E�r(��)
	"data\\MODEL\\Katano_Model\\09_legR_U_0.x",		// �E�r(����)
	"data\\MODEL\\Katano_Model\\10_footR_0.x",		// �E��
	"data\\MODEL\\Katano_Model\\11_legL_T_1.x",		// ���r(��)
	"data\\MODEL\\Katano_Model\\12_legL_U_0.x",		// ���r(����)
	"data\\MODEL\\Katano_Model\\13_footL_0.x",		// ����
};		// ���f���̃t�@�C���ꗗ
LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// �e�N�X�`���ւ̃|�C���^

//
// ����������
//
void InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			g_aModelFile[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntModel].pBuffMatModel,
			NULL,
			&g_player.aModel[nCntModel].nNumMatModel,
			&g_player.aModel[nCntModel].pMeshModel);

		int nNumvtx = 0;			// ���_��
		DWORD sizeFVF = NULL;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff = NULL;		// ���_�o�b�t�@�̃|�C���^

		D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

		g_player.aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
		g_player.aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);

		// ���_�����擾
		nNumvtx = g_player.aModel[nCntModel].pMeshModel->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMeshModel->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

			// ���S�Ă̒��_�����r���ăv���C���[�̍ŏ��l�E�ő�l�𔲂��o��
			if (g_player.aModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_player.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_player.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_player.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_player.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_player.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_player.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			// ���S�Ă̒��_�����r���ăv���C���[�̍ŏ��l�E�ő�l�𔲂��o��

			pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		g_player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
			}// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
		}

		g_player.nNumModel++;
	}

	// �S�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParent = -1;						// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);			// �ʒu�̏����ݒ�
	g_player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[1].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 27.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[2].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[2].pos = D3DXVECTOR3(-8.5f, 23.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[2].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[3].nIdxModelParent = 2;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[3].pos = D3DXVECTOR3(-11.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[3].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[4].nIdxModelParent = 3;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[4].pos = D3DXVECTOR3(-11.5f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[4].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[5].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[5].pos = D3DXVECTOR3(8.5f, 23.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[5].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[6].nIdxModelParent = 5;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[6].pos = D3DXVECTOR3(11.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[6].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[7].nIdxModelParent = 6;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[7].pos = D3DXVECTOR3(11.5f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[7].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[8].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[8].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[8].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[9].nIdxModelParent = 8;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -14.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[9].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[10].nIdxModelParent = 9;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -16.5f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[10].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[11].nIdxModelParent = 0;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[11].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[11].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[12].nIdxModelParent = 11;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -14.0f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[12].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.aModel[13].nIdxModelParent = 12;							// �e�̃C���f�b�N�X��ݒ�
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -16.5f, 0.0f);		// �ʒu�̏����ݒ�
	g_player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��ʂ̏����ݒ�
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����̏����ݒ�
	g_player.aModel[13].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̌����̏����ݒ�

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu�̏����ݒ�
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ��ʂ̏����ݒ�
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �����̏����ݒ�
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړI�̌����̏����ݒ�
}


//
// �I������
//
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// ���b�V���̔j��
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		// �}�e���A���̔j��
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}


//
// �X�V����
//
void UpdatePlayer(void)
{
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_player.rotDest.y = (-D3DX_PI + pCamera->rot.y);

		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}
		g_player.move.x += sinf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z += cosf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_player.rotDest.y = (pCamera->rot.y);
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}

		g_player.move.x -= sinf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z -= cosf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_player.rotDest.y = (D3DX_PI / 2 + pCamera->rot.y);
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}

		g_player.move.x -= cosf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z += sinf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_player.rotDest.y = (-D3DX_PI / 2 + pCamera->rot.y);
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}

		g_player.move.x += cosf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z -= sinf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_player.rotDest.y -= 0.2f;
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_player.rotDest.y += 0.2f;
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_I) == true)
	{
		g_player.move.y += MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_K) == true)
	{
		g_player.move.y -= MODEL_SPD;
	}




	if ((g_player.rotDest.y - g_player.rot.y) > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if ((g_player.rotDest.y - g_player.rot.y) < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}

	g_player.move.x += (0.0f - g_player.move.x) * SPD_DECAY;
	g_player.move.z += (0.0f - g_player.move.z) * SPD_DECAY;
	g_player.move.y += (0.0f - g_player.move.y) * SPD_DECAY;

	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;
	g_player.pos.y += g_player.move.y;
}


//
// �`�揈��
//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;			// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;							// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// �v���C���[�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

		// �v���C���[�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

		// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
							&g_player.aModel[nCntModel].mtxWorld,
							&mtxParent);

		// �e�p�[�c�̃��[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL *)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{// ���f��(�p�[�c)�̕`��
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

			// �v���C���[(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//
// �v���C���[�̎擾
//
PLAYER *GetPlayer(void)
{
	return &g_player;
}
