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
#define WALL_SIZE (200)			// �ǂ̑傫��
#define WALL_X (2)				// �ǂ̉�
#define WALL_Y (2)				// �ǂ̏c

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall002.jpg", &g_pTextureWall);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * ((WALL_X + 1) * (WALL_Y + 1)) * MAX_WALL,
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
		pVtx[0].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pWall->pos.x - 0.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE / 2, pWall->pos.z);
		pVtx[4].pos = D3DXVECTOR3(pWall->pos.x + 0.0f, pWall->pos.y + WALL_SIZE / 2, pWall->pos.z);
		pVtx[5].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE / 2, pWall->pos.z);
		pVtx[6].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
		pVtx[7].pos = D3DXVECTOR3(pWall->pos.x - 0.0f, pWall->pos.y, pWall->pos.z);
		pVtx[8].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
		pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

		pVtx += ((WALL_X + 1) * (WALL_Y + 1));
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((WALL_X * WALL_Y) * 3 + (WALL_Y - 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffWall,
		NULL)))
	{
		return E_FAIL;
	}

	WORD *pIdx;					// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

	// �ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffWall->Unlock();

	for (int SetCntWall = 0; SetCntWall < 2; SetCntWall++)
	{
		SetWall(D3DXVECTOR3(-50.0f + WALL_SIZE * SetCntWall, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetWall(D3DXVECTOR3(50.0f + -WALL_SIZE * SetCntWall, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		SetWall(D3DXVECTOR3(100.0f, 0.0f, 50.0f + -WALL_SIZE * SetCntWall), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
		SetWall(D3DXVECTOR3(-100.0f, 0.0f, -50.0f + WALL_SIZE * SetCntWall), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
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

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
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

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffWall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,							// �v���~�e�B�u�̎��
				0,												// 
				0,												// 
				((WALL_X + 1) * (WALL_Y + 1)),				// ���_�̐�
				0,												// �`����J�n���钸�_�C���f�b�N�X
				WALL_X * WALL_Y * 2 + (WALL_Y - 1) * 4);		// �`�悷��v���~�e�B�u�̐�
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

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++, pWall++)
	{
		if (pWall->bUse == false)
		{
			// �ʒu�̐ݒ�
			pWall->pos = pos;

			// �p�x�̐ݒ�
			pWall->rot = rot;

			// ���_���W�̐ݒ�
			SetVertexWall(nCnt);

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
	pVtx += nIdx * ((WALL_X + 1) * (WALL_Y + 1));
	pWall += nIdx;

	// ���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	//pVtx[1].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	//pVtx[2].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	//pVtx[3].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	pVtx[0].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	pVtx[1].pos = D3DXVECTOR3(pWall->pos.x - 0.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	pVtx[2].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	pVtx[3].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE / 2, pWall->pos.z);
	pVtx[4].pos = D3DXVECTOR3(pWall->pos.x + 0.0f, pWall->pos.y + WALL_SIZE / 2, pWall->pos.z);
	pVtx[5].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE / 2, pWall->pos.z);
	pVtx[6].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	pVtx[7].pos = D3DXVECTOR3(pWall->pos.x - 0.0f, pWall->pos.y, pWall->pos.z);
	pVtx[8].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}


//
// �ǂ̎擾
//
Wall *GetWall(void)
{
	return &g_aWall[0];
}
