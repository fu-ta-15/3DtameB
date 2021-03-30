//=========================================================================================================================
//
// HP�Q�[�W [hpgauge.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "hpgauge.h"
#include "player.h"

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHPGauge = NULL;		// ���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureGaugeBG = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGauge = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGaugeFlame = NULL;

//=========================================================================================================================
// HPGauge�̏���������
//=========================================================================================================================
HRESULT InitHPGauge(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HPGaugeBG.png", &g_pTextureGaugeBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HPGauge.png", &g_pTextureGauge);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HPGaugeFrame.png", &g_pTextureGaugeFlame);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TYPE_HPGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHPGauge,
		NULL)))
	{
		return E_FAIL;
	}



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHPGauge = 0; nCntHPGauge < MAX_TYPE_HPGAUGE; nCntHPGauge++)
	{
		// ���_���W�̐ݒ�
		switch (nCntHPGauge)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_BG_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_BG_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_BG_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_BG_Y / 2, 0.0f);
			break;
		case 1:
			pVtx[0].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
			break;
		case 2:
			pVtx[0].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_FRAME_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_FRAME_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_FRAME_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_FRAME_Y / 2, 0.0f);
			break;
		}

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = DEFAULT_COLOR;
		pVtx[1].col = DEFAULT_COLOR;
		pVtx[2].col = DEFAULT_COLOR;
		pVtx[3].col = DEFAULT_COLOR;

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHPGauge->Unlock();

	return S_OK;
}

//=========================================================================================================================
// HPGauge�̏I������
//=========================================================================================================================
void UninitHPGauge(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffHPGauge != NULL)
	{
		g_pVtxBuffHPGauge->Release();
		g_pVtxBuffHPGauge = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureGaugeBG != NULL)
	{
		g_pTextureGaugeBG->Release();
		g_pTextureGaugeBG = NULL;
	}

	if (g_pTextureGauge != NULL)
	{
		g_pTextureGauge->Release();
		g_pTextureGauge = NULL;
	}

	if (g_pTextureGaugeFlame != NULL)
	{
		g_pTextureGaugeFlame->Release();
		g_pTextureGaugeFlame = NULL;
	}
}

//=========================================================================================================================
// HPGauge�̍X�V����
//=========================================================================================================================
void UpdateHPGauge(void)
{
	ManageGauge();
}

//=========================================================================================================================
// HPGauge�̕`�揈��
//=========================================================================================================================
void DrawHPGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHPGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�\�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TYPE_HPGAUGE; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureGaugeBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureGauge);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTextureGaugeFlame);
			break;
		}

		// HPGauge�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
			nCnt * 4,								// �`����J�n���钸�_�C���f�b�N�X
			2);								// �`�悷��v���~�e�B�u�̐�
	}
}


//=========================================================================================================================
// ����Q�[�W�̊Ǘ�
//=========================================================================================================================
void ManageGauge(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	Player *pPlayer = GetPlayer();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->nLife == PLAYER_HEALTH)
	{
		pVtx[4].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
	}
	else if (pPlayer->nLife >= 0 || pPlayer->nLife < PLAYER_HEALTH)
	{
		pVtx[4].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2 + GAUGE_X * (pPlayer->nLife / (PLAYER_HEALTH*1.0f)), HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2 + GAUGE_X * (pPlayer->nLife / (PLAYER_HEALTH*1.0f)), HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHPGauge->Unlock();
}
