//=========================================================================================================================
//
// ���b�V���t�B�[���h [meshfield.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "meshfield.h"

//
// �}�N����`
//
#define MAX_FIELD (256)			// ���̍ő吔
#define FIELD_SIZE (200.0f)		// ��1���̑傫��
#define FIELD_X (2)				// ���̉�
#define FIELD_Z (2)				// ���̉��s

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;			// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshField;								// �ʒu
D3DXVECTOR3 g_rotMeshField;								// ����
D3DXMATRIX g_mtxWorldMeshField;							// ���[���h�}�g���b�N�X

//
// ����������
//
HRESULT InitMeshField(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field003.jpg", &g_pTextureMeshField);

	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * ((FIELD_X + 1) * (FIELD_Z + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	// 
	//for (int nCntZ = 0; nCntZ < FIELD_Z + 1; nCntZ++)
	//{
	//	for (int nCntX = 0; nCntX < FIELD_X + 1; nCntX++)
	//	{
	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].pos = 
	//			D3DXVECTOR3(g_posMeshField.x - ((FIELD_SIZE / 2) * FIELD_X) / (1 - (float)nCntX),
	//						g_posMeshField.y, g_posMeshField.z + ((FIELD_SIZE / 2) * FIELD_Z)) / (1 - (float)nCntZ);

	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		pVtx[nCntX + nCntZ * (FIELD_X + 1)].tex = D3DXVECTOR2(0.0f + (float)nCntX, 0.0f + (float)nCntZ);
	//	}
	//}
	pVtx[0].pos = D3DXVECTOR3(g_posMeshField.x - FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + FIELD_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posMeshField.x - 0.0f, g_posMeshField.y, g_posMeshField.z + FIELD_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshField.x + FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + FIELD_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshField.x - FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + 0.0f);
	pVtx[4].pos = D3DXVECTOR3(g_posMeshField.x + 0.0f, g_posMeshField.y, g_posMeshField.z - 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshField.x + FIELD_SIZE, g_posMeshField.y, g_posMeshField.z + 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshField.x - FIELD_SIZE, g_posMeshField.y, g_posMeshField.z - FIELD_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posMeshField.x - 0.0f, g_posMeshField.y, g_posMeshField.z - FIELD_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshField.x + FIELD_SIZE, g_posMeshField.y, g_posMeshField.z - FIELD_SIZE);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();


	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * ((FIELD_X * FIELD_Z) * 3 + (FIELD_Z - 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL)))
	{
		return E_FAIL;
	}

	WORD *pIdx;					// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}


//
// �X�V����
//
void UpdateMeshField(void)
{

}


//
// �`�揈��
//
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,							// �v���~�e�B�u�̎��
		0,												// 
		0,												// 
		((FIELD_X + 1) * (FIELD_Z + 1)),				// ���_�̐�
		0,												// �`����J�n���钸�_�C���f�b�N�X
		FIELD_X * FIELD_Z * 2  + (FIELD_Z - 1) * 4);	// �`�悷��v���~�e�B�u�̐�
}