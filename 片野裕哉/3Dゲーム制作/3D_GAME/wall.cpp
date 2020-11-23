//=========================================================================================================================
//
// ��(�E�H�[��) [wall.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "wall.h"

//
// �}�N����`
//
#define MAX_WALL (256)			// �ǂ̍ő吔
#define WALL_SIZE (200)			// �ǂ̑傫��

//
// �\���̂̒�`
//
typedef struct
{
	D3DXVECTOR3 pos;			// �ǂ̒��S���W
	D3DXVECTOR3 rot;			// �ǂ̌���
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Wall;

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;			// �e�N�X�`���ւ̃|�C���^
Wall g_aWall[MAX_WALL];								// �ǂ̏��

//
// ����������
//
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Wall *pWall = &g_aWall[0];						// �ǂ̍\���̂̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++, pWall++)
	{
		pWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field000.jpg", &g_pTextureWall);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		// ���_���W�̐ݒ�
		SetVertexWall(nCnt);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	for (int SetCntWall = 0; SetCntWall < 1; SetCntWall++)
	{
		SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	return S_OK;
}


//
// �I������
//
void UninitWall(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

}


//
// �X�V����
//
void UpdateWall(void)
{

}


//
// �`�揈��
//
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	Wall *pWall = &g_aWall[0];						// �ǂ̍\���̂̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�}�g���b�N�X


	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++, pWall++)
	{
		if (pWall->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pWall->mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				4 * nCnt,						// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
		}
	}
}


//
// �ǂ̔z�u
//
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �\���̂̃|�C���^�ϐ�
	Wall *pWall = &g_aWall[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{
			// �ʒu�̐ݒ�
			pWall->pos = pos;

			// �p�x�̐ݒ�
			pWall->rot = rot;

			// �g�p��Ԃ�true�ɂ���
			pWall->bUse = true;

			break;
		}
	}
}


//-----------------------------------------------------------------
// �ǂ̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexWall(int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_3D *pVtx;
	Wall *pWall = &g_aWall[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nIdx * 4;
	pWall += nIdx;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	pVtx[1].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	pVtx[2].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	pVtx[3].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}