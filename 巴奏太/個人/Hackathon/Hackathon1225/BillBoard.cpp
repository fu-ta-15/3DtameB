////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �r���{�[�h�̏��� [Billboard.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/20
//
////////////////////////////////////////////////////////////////////////////////
#include "Billboard.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_BILLBOARD (16)

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		//�e�N�X�`�����
BILLBOARD g_aBillboard[MAX_BILLBOARD];

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBillboard(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\hoshi.png", &g_pTextureBillboard);

	g_aBillboard[0].pos = D3DXVECTOR3(0.0f, 100.0f, 750.0f);
	g_aBillboard[1].pos = D3DXVECTOR3(750.0f, 100.0f, 0.0f);
	g_aBillboard[2].pos = D3DXVECTOR3(-750.0f, 100.0f, 0.0f);
	g_aBillboard[3].pos = D3DXVECTOR3(0.0f, 100.0f, -750.0f);

	g_aBillboard[4].pos = D3DXVECTOR3(500.0f, 100.0f, 500.0f);
	g_aBillboard[5].pos = D3DXVECTOR3(500.0f, 100.0f, -500.0f);
	g_aBillboard[6].pos = D3DXVECTOR3(-500.0f, 100.0f, 500.0f);
	g_aBillboard[7].pos = D3DXVECTOR3(-500.0f, 100.0f, -500.0f);

	g_aBillboard[8].pos = D3DXVECTOR3(0.0f, -200.0f, 750.0f);
	g_aBillboard[9].pos = D3DXVECTOR3(750.0f, -200.0f, 0.0f);
	g_aBillboard[10].pos = D3DXVECTOR3(-750.0f, -200.0f, 0.0f);
	g_aBillboard[11].pos = D3DXVECTOR3(0.0f, -200.0f, -750.0f);

	g_aBillboard[12].pos = D3DXVECTOR3(500.0f, -200.0f, 500.0f);
	g_aBillboard[13].pos = D3DXVECTOR3(500.0f, -200.0f, -500.0f);
	g_aBillboard[14].pos = D3DXVECTOR3(-500.0f, -200.0f, 500.0f);
	g_aBillboard[15].pos = D3DXVECTOR3(-500.0f, -200.0f, -500.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBoard = 0; nCntBoard < MAX_BILLBOARD; nCntBoard++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-500, -300, 0);
		pVtx[1].pos = D3DXVECTOR3(-500, 300, 0);
		pVtx[2].pos = D3DXVECTOR3(500, -300, 0);
		pVtx[3].pos = D3DXVECTOR3(500, 300, 0);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitBillboard(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();	//�J��
		g_pVtxBuffBillboard = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();	//�J��
		g_pTextureBillboard = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateBillboard(void)
{
	for (int nCnt = 0; nCnt < 15; nCnt++)
	{
		g_aBillboard[nCnt].pos.z -= 1.5f;
		if (g_aBillboard[nCnt].pos.z < -100.0f) 
			g_aBillboard[nCnt].pos.z = 1000.0f;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawBillboard(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	//���C�e�B���O�̖���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBoard = 0; nCntBoard < MAX_BILLBOARD; nCntBoard++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBillboard[nCntBoard].mtxworld);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

#if 1
		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		//�t�s������߂�
		D3DXMatrixInverse(&g_aBillboard[nCntBoard].mtxworld, NULL, &mtxView);

		//���s�ړ��̕����͖�������
		g_aBillboard[nCntBoard].mtxworld._41 = 0.0f;
		g_aBillboard[nCntBoard].mtxworld._42 = 0.0f;
		g_aBillboard[nCntBoard].mtxworld._43 = 0.0f;
#endif

#if 0
		g_aBillboard[nCntBoard].mtxworld._11 = mtxView._11;
		g_aBillboard[nCntBoard].mtxworld._12 = mtxView._21;
		g_aBillboard[nCntBoard].mtxworld._13 = mtxView._31;
		g_aBillboard[nCntBoard].mtxworld._21 = mtxView._12;
		g_aBillboard[nCntBoard].mtxworld._22 = mtxView._22;
		g_aBillboard[nCntBoard].mtxworld._23 = mtxView._32;
		g_aBillboard[nCntBoard].mtxworld._31 = mtxView._13;
		g_aBillboard[nCntBoard].mtxworld._32 = mtxView._23;
		g_aBillboard[nCntBoard].mtxworld._33 = mtxView._33;
#endif

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBoard].pos.x, g_aBillboard[nCntBoard].pos.y, g_aBillboard[nCntBoard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBoard].mtxworld, &g_aBillboard[nCntBoard].mtxworld, &mtxTrans);

		//���[���h�}�g���b�N�X
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBoard].mtxworld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBillboard);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBoard * 4, 2);
	}

	//���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���C�e�B���O��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}