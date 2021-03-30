//##################################################################################################################################################################//
//
// �Q�[�W�\�[�X�t�@�C�� [gauge.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "gauge.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GAUGE_TEX		(8)
#define GAUGE_TEX			(4)


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
GaugeCover g_aGC[GAUGE_TEX];
Gauge g_aG[GAUGE_TEX];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge;	//�e�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureGauge[GAUGE_TEX];
LPDIRECT3DTEXTURE9 g_apTextureGaugeCover[GAUGE_TEX];


//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT LodaInit(void);
HRESULT Vertex2D(GaugeCover GC, Gauge G);


HRESULT Vertex2D(GaugeCover GC, Gauge G)
{
	VERTEX_2D *pVtx;

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (4 * GC.type);

	pVtx[0].pos = D3DXVECTOR3(GC.pos.x, GC.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GC.pos.x, GC.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GC.pos.x + GC.size.x, GC.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GC.pos.x + GC.size.x, GC.pos.y, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = GC.col;
	pVtx[1].col = GC.col;
	pVtx[2].col = GC.col;
	pVtx[3].col = GC.col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

	GC.bset = true;

	g_pVtxBuffGauge->Unlock();

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (4 * G.type);

	pVtx[0].pos = D3DXVECTOR3(G.pos.x, G.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(G.pos.x, G.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(G.pos.x + G.size.x, G.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(G.pos.x + G.size.x, G.pos.y, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = G.col;
	pVtx[1].col = G.col;
	pVtx[2].col = G.col;
	pVtx[3].col = G.col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

	g_pVtxBuffGauge->Unlock();

	return S_OK;
}


HRESULT InitGauge(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Gauge *pGauge = GetGauge();
	GaugeCover *pGaugeCover = GetGaugeCover();

	// ������
	memset(pGauge, NULL, sizeof(Gauge) * GAUGE_TEX);
	memset(pGaugeCover, NULL, sizeof(GaugeCover) * GAUGE_TEX);

	//�e�N�X�`���ǂݍ���
	LodaInit();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\playergauge.png", &g_apTextureGauge[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\actiongauge.png", &g_apTextureGauge[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\portalgauge.png", &g_apTextureGauge[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossgauge.png", &g_apTextureGauge[3]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\playergaugecaver.png", &g_apTextureGaugeCover[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\actiongaugecaver.png", &g_apTextureGaugeCover[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\portalgaugecaver.png", &g_apTextureGaugeCover[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossgaugecover.png", &g_apTextureGaugeCover[3]);


		//���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGE_TEX*4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGauge, NULL)))
		{
			return E_FAIL;
		}


	return S_OK;
}

void UninitGauge(void)
{
	if (g_pVtxBuffGauge != NULL)
	{//�Q�[�W
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}

	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_apTextureGauge[nCntGau] != NULL)
		{//�Q�[�W
			g_apTextureGauge[nCntGau]->Release();
			g_apTextureGauge[nCntGau] = NULL;
		}

		if (g_apTextureGaugeCover[nCntGau] != NULL)
		{//�Q�[�W�J�o�[
			g_apTextureGaugeCover[nCntGau]->Release();
			g_apTextureGaugeCover[nCntGau] = NULL;
		}
	}
}

void UpdateGauge(void)
{

	VERTEX_2D *pVtx;

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_aGC[nCntGau].bset == true)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x, g_aGC[nCntGau].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x, g_aGC[nCntGau].pos.y + g_aGC[nCntGau].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x + g_aGC[nCntGau].size.x, g_aGC[nCntGau].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x + g_aGC[nCntGau].size.x, g_aGC[nCntGau].pos.y + g_aGC[nCntGau].size.y, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = g_aGC[nCntGau].col;
			pVtx[1].col = g_aGC[nCntGau].col;
			pVtx[2].col = g_aGC[nCntGau].col;
			pVtx[3].col = g_aGC[nCntGau].col;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		}
		pVtx += (4);
	}
	g_pVtxBuffGauge->Unlock();

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_aG[nCntGau].bset == true)
		{

			pVtx[0].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x, g_aG[nCntGau].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x, g_aG[nCntGau].pos.y + g_aG[nCntGau].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x + g_aG[nCntGau].size.x, g_aG[nCntGau].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x + g_aG[nCntGau].size.x, g_aG[nCntGau].pos.y + g_aG[nCntGau].size.y, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = g_aG[nCntGau].col;
			pVtx[1].col = g_aG[nCntGau].col;
			pVtx[2].col = g_aG[nCntGau].col;
			pVtx[3].col = g_aG[nCntGau].col;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		}
		pVtx += (4);
	}
	g_pVtxBuffGauge->Unlock();


}

void DrawGauge(void)
{
	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_aG[nCntGau].bset == true)
		{
			LPDIRECT3DDEVICE9 pDevice;
			//�f�o�C�X�̎擾
			pDevice = GetDevice();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			pDevice->SetTexture(0, g_apTextureGauge[g_aG[nCntGau].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntGau, 2);
		}
	}
}

void DrawGaugeCover(void)
{
	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_aGC[nCntGau].bset == true)
		{
			LPDIRECT3DDEVICE9 pDevice;
			//�f�o�C�X�̎擾
			pDevice = GetDevice();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			pDevice->SetTexture(0, g_apTextureGaugeCover[g_aGC[nCntGau].type]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntGau, 2);
		}
	}
}

void SetGeauge(GAUGE_TYPE Gtype, GAUGE_COVER GCtype, D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_aGC[nCntGau].bset == false)
		{


			g_aGC[nCntGau].pos = pos;
			g_aGC[nCntGau].size = size;
			g_aGC[nCntGau].col = col;

			pVtx[0].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x, g_aGC[nCntGau].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x, g_aGC[nCntGau].pos.y + g_aGC[nCntGau].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x + g_aGC[nCntGau].size.x, g_aGC[nCntGau].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aGC[nCntGau].pos.x + g_aGC[nCntGau].size.x, g_aGC[nCntGau].pos.y + g_aGC[nCntGau].size.y, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = g_aGC[nCntGau].col;
			pVtx[1].col = g_aGC[nCntGau].col;
			pVtx[2].col = g_aGC[nCntGau].col;
			pVtx[3].col = g_aGC[nCntGau].col;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

			g_aGC[nCntGau].type = GCtype;

			g_aGC[nCntGau].bset = true;

		}
		pVtx += (4);
	}
	g_pVtxBuffGauge->Unlock();

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGau = 0; nCntGau < GAUGE_TEX; nCntGau++)
	{
		if (g_aG[nCntGau].bset == false)
		{


			g_aG[nCntGau].pos = pos;
			g_aG[nCntGau].size = size;
			g_aG[nCntGau].col = col;


			pVtx[0].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x, g_aG[nCntGau].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x, g_aG[nCntGau].pos.y + g_aG[nCntGau].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x + g_aG[nCntGau].size.x, g_aG[nCntGau].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aG[nCntGau].pos.x + g_aG[nCntGau].size.x, g_aG[nCntGau].pos.y + g_aG[nCntGau].size.y, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = g_aG[nCntGau].col;
			pVtx[1].col = g_aG[nCntGau].col;
			pVtx[2].col = g_aG[nCntGau].col;
			pVtx[3].col = g_aG[nCntGau].col;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

			g_aG[nCntGau].type = Gtype;

			g_aG[nCntGau].bset = true;



		}
		pVtx += (4);
	}
	g_pVtxBuffGauge->Unlock();

}

HRESULT LodaInit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	return S_OK;
}


Gauge * GetGauge(void)
{
	return &g_aG[0];
}

GaugeCover * GetGaugeCover(void)
{
	return &g_aGC[0];
}

