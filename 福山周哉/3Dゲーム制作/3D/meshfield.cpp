//===========================================================================================================
//
// ���b�V���t�B�[���h�̐ݒ� [meshfield.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "meshfield.h"

//===========================================================================================================
//�}�N����`
//===========================================================================================================
#define MAX_POLYGON (1)					//�|���S���̍ő吔
#define MAX_SIZE (100.0f)				//�|���S���̃T�C�Y

//===========================================================================================================
//�O���[�o���ϐ�
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferMeshField = NULL;			//���_�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;				//�C���f�b�N�X�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;					//�e�N�X�`��
D3DXVECTOR3 g_posMeshField;										//�ʒu
D3DXVECTOR3 g_rotMeshField;										//����
D3DXMATRIX g_mtxWorldMeshField;									//���[���h�}�g���b�N�X

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT InitMeshField(void)					//�f�o�C�X�̃|�C���^
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field001.jpg", &g_pTextureMeshField);

	//�|���S���̏�����
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferMeshField, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshField, NULL);

	WORD * pIdx;				//�C���f�b�N�X���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufferMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posMeshField.x - MAX_SIZE, g_posMeshField.y, g_posMeshField.z + MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posMeshField.x, g_posMeshField.y, g_posMeshField.z + MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshField.x + MAX_SIZE, g_posMeshField.y, g_posMeshField.z + MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshField.x - MAX_SIZE, g_posMeshField.y, g_posMeshField.z);
	pVtx[4].pos = D3DXVECTOR3(g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshField.x + MAX_SIZE, g_posMeshField.y, g_posMeshField.z);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshField.x - MAX_SIZE, g_posMeshField.y, g_posMeshField.z - MAX_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posMeshField.x, g_posMeshField.y, g_posMeshField.z - MAX_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshField.x + MAX_SIZE, g_posMeshField.y, g_posMeshField.z - MAX_SIZE);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufferMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//�ԍ��f�[�^�̐ݒ�
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

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();

	return S_OK;
}

//===========================================================================================================
//�I������
//===========================================================================================================
void UninitMeshField(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBufferMeshField != NULL)
	{
		g_pVtxBufferMeshField->Release();
		g_pVtxBufferMeshField = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//�C���f�b�N�X�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//===========================================================================================================
//�X�V����
//===========================================================================================================
void UpdateMeshField(void)
{
}

//===========================================================================================================
//�`�揈��
//===========================================================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	pDevice = GetDevice();						//�f�o�C�X�̎擾
	
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufferMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0 ,0, 9, 0,14);
}