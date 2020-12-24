//=========================================================================================================================
//
// ���� [Solid.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "Solid.h"

//
// �}�N����`
//
#define MAX_SOLID (256)			// ���̂̍ő吔
#define SOLID_SIZE (200)			// ���̂̑傫��
#define SOLID_X (2)				// ���̂̉�
#define SOLID_Y (2)				// ���̂̏c

//
// �\���̂̒�`
//
typedef struct
{
	D3DXVECTOR3 pos;			// ���S���W
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	bool bUse;					// �g�p���Ă��邩�ǂ���
}SOLID;

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSolid = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSolid = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSolid = NULL;			// �e�N�X�`���ւ̃|�C���^
SOLID g_aSolid[MAX_SOLID];								// ���̂̏��

													//
													// ����������
													//
HRESULT InitSolid(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	SOLID *pSolid = &g_aSolid[0];						// ���̂̍\���̂̃|�C���^

													// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++, pSolid++)
	{
		pSolid->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pSolid->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pSolid->bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall003.jpg", &g_pTextureSolid);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * ((SOLID_X + 1) * (SOLID_Y + 1)) * MAX_SOLID,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSolid,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

										// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSolid->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
		pVtx[4].pos = D3DXVECTOR3(pSolid->pos.x + 0.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
		pVtx[5].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
		pVtx[6].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
		pVtx[7].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y, pSolid->pos.z);
		pVtx[8].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);

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

		pVtx += ((SOLID_X + 1) * (SOLID_Y + 1));
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSolid->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((SOLID_X * SOLID_Y) * 3 + (SOLID_Y - 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSolid,
		NULL)))
	{
		return E_FAIL;
	}

	WORD *pIdx;					// �C���f�b�N�X���ւ̃|�C���^

								// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffSolid->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffSolid->Unlock();

	for (int SetCntSolid = 0; SetCntSolid < 2; SetCntSolid++)
	{
		SetSolid(D3DXVECTOR3(-50.0f + SOLID_SIZE * SetCntSolid, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetSolid(D3DXVECTOR3(50.0f + -SOLID_SIZE * SetCntSolid, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		SetSolid(D3DXVECTOR3(100.0f, 0.0f, 50.0f + -SOLID_SIZE * SetCntSolid), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
		SetSolid(D3DXVECTOR3(-100.0f, 0.0f, -50.0f + SOLID_SIZE * SetCntSolid), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	}

	return S_OK;
}


//
// �I������
//
void UninitSolid(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureSolid != NULL)
	{
		g_pTextureSolid->Release();
		g_pTextureSolid = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSolid != NULL)
	{
		g_pVtxBuffSolid->Release();
		g_pVtxBuffSolid = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pVtxBuffSolid != NULL)
	{
		g_pIdxBuffSolid->Release();
		g_pIdxBuffSolid = NULL;
	}
}


//
// �X�V����
//
void UpdateSolid(void)
{

}


//
// �`�揈��
//
void DrawSolid(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	SOLID *pSolid = &g_aSolid[0];						// ���̂̍\���̂̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�}�g���b�N�X


	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++, pSolid++)
	{
		if (pSolid->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pSolid->mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pSolid->rot.y, pSolid->rot.x, pSolid->rot.z);
			D3DXMatrixMultiply(&pSolid->mtxWorld, &pSolid->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pSolid->pos.x, pSolid->pos.y, pSolid->pos.z);
			D3DXMatrixMultiply(&pSolid->mtxWorld, &pSolid->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pSolid->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSolid, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSolid);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSolid);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,							// �v���~�e�B�u�̎��
				0,												// 
				0,												// 
				((SOLID_X + 1) * (SOLID_Y + 1)),				// ���_�̐�
				0,												// �`����J�n���钸�_�C���f�b�N�X
				SOLID_X * SOLID_Y * 2 + (SOLID_Y - 1) * 4);		// �`�悷��v���~�e�B�u�̐�
		}
	}
}


//
// ���̂̔z�u
//
void SetSolid(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �\���̂̃|�C���^�ϐ�
	SOLID *pSolid = &g_aSolid[0];

	for (int nCnt = 0; nCnt < MAX_SOLID; nCnt++, pSolid++)
	{
		if (pSolid->bUse == false)
		{
			// �ʒu�̐ݒ�
			pSolid->pos = pos;

			// �p�x�̐ݒ�
			pSolid->rot = rot;

			// ���_���W�̐ݒ�
			SetVertexSolid(nCnt);

			// �g�p��Ԃ�true�ɂ���
			pSolid->bUse = true;

			break;
		}
	}
}


//-----------------------------------------------------------------
// ���̂̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexSolid(int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_3D *pVtx;
	SOLID *pSolid = &g_aSolid[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSolid->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nIdx * ((SOLID_X + 1) * (SOLID_Y + 1));
	pSolid += nIdx;

	// ���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
	//pVtx[1].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	//pVtx[2].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
	//pVtx[3].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[0].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[1].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[2].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE, pSolid->pos.z);
	pVtx[3].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
	pVtx[4].pos = D3DXVECTOR3(pSolid->pos.x + 0.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
	pVtx[5].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y + SOLID_SIZE / 2, pSolid->pos.z);
	pVtx[6].pos = D3DXVECTOR3(pSolid->pos.x - SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);
	pVtx[7].pos = D3DXVECTOR3(pSolid->pos.x - 0.0f, pSolid->pos.y, pSolid->pos.z);
	pVtx[8].pos = D3DXVECTOR3(pSolid->pos.x + SOLID_SIZE / 2.0f, pSolid->pos.y, pSolid->pos.z);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSolid->Unlock();
}