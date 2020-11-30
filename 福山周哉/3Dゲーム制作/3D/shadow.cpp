//===========================================================================================================
//
// �e�̐ݒ� [shadow.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "shadow.h"

//===========================================================================================================
//�}�N����`
//===========================================================================================================
#define MAX_SHADOW (1)					//�e�̍ő吔
#define MAX_SIZE (25.0f)				//�e�̃T�C�Y

//===========================================================================================================
//�e�̍\����
//=========================================================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	bool bUse;
}SHADOW;


//===========================================================================================================
//�O���[�o���ϐ�
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferShadow = NULL;				//�|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;						//�e�N�X�`��
D3DXVECTOR3 g_posShadow;										//�ʒu
D3DXVECTOR3 g_rotShadow;										//����
D3DXMATRIX g_mtxWorldShadow;									//���[���h�}�g���b�N�X
bool bUse;													//�g���Ă��邩�ǂ���

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT InitShadow(void)					//�f�o�C�X�̃|�C���^
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_pTextureShadow);

	//�|���S���̏�����
	g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferShadow, NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufferShadow->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posShadow.x - MAX_SIZE, g_posShadow.y, g_posShadow.z + MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posShadow.x + MAX_SIZE, g_posShadow.y, g_posShadow.z + MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posShadow.x - MAX_SIZE, g_posShadow.y, g_posShadow.z - MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posShadow.x + MAX_SIZE, g_posShadow.y, g_posShadow.z - MAX_SIZE);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufferShadow->Unlock();

	return S_OK;
}

//===========================================================================================================
//�I������
//===========================================================================================================
void UninitShadow(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBufferShadow != NULL)
	{
		g_pVtxBufferShadow->Release();
		g_pVtxBufferShadow = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//===========================================================================================================
//�X�V����
//===========================================================================================================
void UpdateShadow(void)
{
}

//===========================================================================================================
//�`�揈��
//===========================================================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X

	//���Y�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);
	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);
	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufferShadow, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,						//�`����J�n���钸�_�C���f�b�N�X
		2);						//�`�悷��v���~�e�B�u��

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}