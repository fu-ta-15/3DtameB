//===========================================================================================================
//
// �r���{�[�h�̐ݒ� [wall.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "billboard.h"

//===========================================================================================================
//�}�N����`
//===========================================================================================================
#define MAX_SIZE (50.0f)				//�r���{�[�h�̃T�C�Y

//===========================================================================================================
//�O���[�o���ϐ�
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBillboard = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;					//�e�N�X�`��
D3DXVECTOR3 g_posBillboard;										//�ʒu
D3DXMATRIX g_mtxWorldBillboard;									//���[���h�}�g���b�N�X

//===========================================================================================================
// ����������
//===========================================================================================================
HRESULT InitBillboard(void)					//�f�o�C�X�̃|�C���^
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cube.png", &g_pTextureBillboard);

	//�|���S���̏�����
	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferBillboard, NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBufferBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x + 20, g_posBillboard.y + 45, g_posBillboard.z);
	pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 20, g_posBillboard.y, g_posBillboard.z);
	pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 20, g_posBillboard.y + 45, g_posBillboard.z);
	pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x - 20, g_posBillboard.y, g_posBillboard.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	g_pVtxBufferBillboard->Unlock();

	return S_OK;
}

//===========================================================================================================
//�I������
//===========================================================================================================
void UninitBillboard(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBufferBillboard != NULL)
	{
		g_pVtxBufferBillboard->Release();
		g_pVtxBufferBillboard = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//===========================================================================================================
//�X�V����
//===========================================================================================================
void UpdateBillboard(void)
{
}

//===========================================================================================================
//�`�揈��
//===========================================================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;								//�r���[�}�g���b�N�X�擾�p				
	D3DXMATRIX mtxTrans;							//�v�Z�p�}�g���b�N�X

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//�r���[�}�g���b�N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);				//�t�s������߂�

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufferBillboard, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,						//�`����J�n���钸�_�C���f�b�N�X
		2);						//�`�悷��v���~�e�B�u��

}