//===========================================================================================================
//
// �|���S���̐ݒ� [polygon.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "polygon.h"

//===========================================================================================================
//�}�N����`
//===========================================================================================================
#define MAX_POLYGON (1)					//�|���S���̍ő吔
#define MAX_SIZE (50.0f)				//�|���S���̃T�C�Y

//===========================================================================================================
//�O���[�o���ϐ�
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferPolygon = NULL;
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;					//�e�N�X�`��
D3DXVECTOR3 g_posPolygon;										//�ʒu
D3DXVECTOR3 g_rotPolygon;										//����
D3DXMATRIX g_mtxWorldPolygon;									//���[���h�}�g���b�N�X

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT InitPolygon(void)					//�f�o�C�X�̃|�C���^
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field001.jpg", &g_pTexturePolygon);

	//�|���S���̏�����
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferPolygon, NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufferPolygon->Lock(0,0,(void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - MAX_SIZE, g_posPolygon.y, g_posPolygon.z + MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + MAX_SIZE, g_posPolygon.y, g_posPolygon.z + MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - MAX_SIZE, g_posPolygon.y, g_posPolygon.z - MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + MAX_SIZE, g_posPolygon.y, g_posPolygon.z - MAX_SIZE);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,  0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufferPolygon->Unlock();

	return S_OK;
}

//===========================================================================================================
//�I������
//===========================================================================================================
void UninitPolygon(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBufferPolygon != NULL)
	{
		g_pVtxBufferPolygon->Release();
		g_pVtxBufferPolygon = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//===========================================================================================================
//�X�V����
//===========================================================================================================
void UpdatePolygon(void)
{
}

//===========================================================================================================
//�`�揈��
//===========================================================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�|�C���^
	D3DXMATRIX mtxRot,mtxTrans;					//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufferPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,						//�`����J�n���钸�_�C���f�b�N�X
		2);						//�`�悷��v���~�e�B�u��

}