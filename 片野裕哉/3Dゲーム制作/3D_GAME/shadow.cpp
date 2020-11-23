//=========================================================================================================================
//
// �e(�V���h�E) [shadow.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "shadow.h"

//
// �}�N����`
//
#define MAX_SHADOW (512)
#define SHADOW_SIZE_VERTEX (15.0f)

//
// �\���̂̒�`
//
// �e�̍\����
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	bool bUse;
} Shadow;

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posShadow;								// �ʒu
D3DXVECTOR3 g_rotShadow;								// ����
D3DXMATRIX g_mtxWorldShadow;							// ���[���h�}�g���b�N�X
Shadow g_aShadow[MAX_SHADOW];							// �e(�V���h�E)�̏��

//
// ����������
//
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_pTextureShadow);

	g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	// 
	pVtx[0].pos = D3DXVECTOR3(g_posShadow.x - SHADOW_SIZE_VERTEX, g_posShadow.y, g_posShadow.z + SHADOW_SIZE_VERTEX);
	pVtx[1].pos = D3DXVECTOR3(g_posShadow.x + SHADOW_SIZE_VERTEX, g_posShadow.y, g_posShadow.z + SHADOW_SIZE_VERTEX);
	pVtx[2].pos = D3DXVECTOR3(g_posShadow.x - SHADOW_SIZE_VERTEX, g_posShadow.y, g_posShadow.z - SHADOW_SIZE_VERTEX);
	pVtx[3].pos = D3DXVECTOR3(g_posShadow.x + SHADOW_SIZE_VERTEX, g_posShadow.y, g_posShadow.z - SHADOW_SIZE_VERTEX);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitShadow(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}


//
// �X�V����
//
void UpdateShadow(void)
{

}


//
// �`�揈��
//
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�

	// �ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//
// �e�̐ݒ�
//
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	int nIdx = -1;

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{

			nIdx = nCntShadow;
			break;
		}
	}

	return nIdx;
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{

}
