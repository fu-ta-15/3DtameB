//=========================================================================================================================
//
// �r���{�[�h [Billboard.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "Billboard.h"
#include "input.h"
#include "camera.h"

//
//
//
#define BILLBOARD_SPD (2.0f)
#define BILLBOARD_SPD_DECAY (0.4f)

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			// �e�N�X�`���ւ̃|�C���^
BILLBOARD g_Billboard;

//
// ����������
//
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tree000.png", &g_pTextureBillboard);

	g_Billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Billboard.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_Billboard.pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	// 
	pVtx[0].pos = D3DXVECTOR3(g_Billboard.pos.x - 25.0f, g_Billboard.pos.y, g_Billboard.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Billboard.pos.x - 25.0f, g_Billboard.pos.y + 50.0f, g_Billboard.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Billboard.pos.x + 25.0f, g_Billboard.pos.y, g_Billboard.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Billboard.pos.x + 25.0f, g_Billboard.pos.y + 50.0f, g_Billboard.pos.z);

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

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitBillboard(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

}


//
// �X�V����
//
void UpdateBillboard(void)
{
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_Billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Billboard.move.x += sinf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z += cosf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Billboard.move.x -= sinf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z -= cosf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Billboard.move.x -= cosf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z += sinf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Billboard.move.x += cosf(pCamera->rot.y) * BILLBOARD_SPD;
		g_Billboard.move.z -= sinf(pCamera->rot.y) * BILLBOARD_SPD;
	}

	g_Billboard.move.x += (0.0f - g_Billboard.move.x) * BILLBOARD_SPD_DECAY;
	g_Billboard.move.z += (0.0f - g_Billboard.move.z) * BILLBOARD_SPD_DECAY;

	g_Billboard.pos.x += g_Billboard.move.x;
	g_Billboard.pos.z += g_Billboard.move.z;
}


//
// �`�揈��
//
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxView;								// �r���[�}�g���b�N�X�擾�p

	D3DXMATRIX mtxTrans;							// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�̍X�V
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Billboard.mtxWorld);

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_Billboard.mtxWorld, NULL, &mtxView);	// �t�s������߂�
	g_Billboard.mtxWorld._41 = 0.0f;
	g_Billboard.mtxWorld._42 = 0.0f;
	g_Billboard.mtxWorld._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Billboard.pos.x, g_Billboard.pos.y, g_Billboard.pos.z);

	D3DXMatrixMultiply(&g_Billboard.mtxWorld, &g_Billboard.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Billboard.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,								// �`����J�n���钸�_�C���f�b�N�X
		2);								// �`�悷��v���~�e�B�u�̐�


	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}