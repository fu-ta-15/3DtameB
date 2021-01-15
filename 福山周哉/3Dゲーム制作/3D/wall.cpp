//===========================================================================================================
//
// �ǂ̐ݒ� [wall.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "wall.h"

//===========================================================================================================
//�}�N����`
//===========================================================================================================
#define MAX_WALL (1)					//�ǂ̍ő吔
#define MAX_SIZE (100.0f)				//�ǂ̃T�C�Y

//===========================================================================================================
//�O���[�o���ϐ�
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferWall = NULL;			//�|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;				//�C���f�b�N�X�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;					//�e�N�X�`��
D3DXVECTOR3 g_posWall;										//�ʒu
D3DXVECTOR3 g_rotWall;										//����
D3DXMATRIX g_mtxWorldWall;									//���[���h�}�g���b�N�X

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT InitWall(void)					//�f�o�C�X�̃|�C���^
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureWall);

	//�|���S���̏�����
	g_rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferWall, NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffWall, NULL);

	WORD * pIdx;				//�C���f�b�N�X���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufferWall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[4].pos = D3DXVECTOR3(g_posWall.x, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[5].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[6].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y, g_posWall.z + MAX_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posWall.x, g_posWall.y, g_posWall.z + MAX_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y, g_posWall.z + MAX_SIZE);

	/*pVtx[0].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z - MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z - MAX_SIZE);
	pVtx[4].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z);
	pVtx[5].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[6].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y - MAX_SIZE, g_posWall.z - MAX_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y - MAX_SIZE, g_posWall.z);
	pVtx[8].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y - MAX_SIZE, g_posWall.z + MAX_SIZE);*/

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBufferWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffWall->Unlock();

	return S_OK;
}

//===========================================================================================================
//�I������
//===========================================================================================================
void UninitWall(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBufferWall  != NULL)
	{
		g_pVtxBufferWall->Release();
		g_pVtxBufferWall = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//�C���f�b�N�X�̊J��
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//===========================================================================================================
//�X�V����
//===========================================================================================================
void UpdateWall(void)
{
}

//===========================================================================================================
//�`�揈��
//===========================================================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X

													//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldWall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotWall.y, g_rotWall.x, g_rotWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posWall.x, g_posWall.y, g_posWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufferWall, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffWall);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureWall);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 
													   0, 
													   9,			//���_��
													   0, 
													  14);			//�`�悷��v���~�e�B�u��
}