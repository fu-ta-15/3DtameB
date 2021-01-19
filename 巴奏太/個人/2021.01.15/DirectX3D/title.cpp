//-----------------------------------------------------------------------------
//
// �^�C�g���̏��� [title.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// �}�N��
//-----------------------------------------------------------------------------
#define TITLE_OBJ_AMOUNT (1)													//�^�C�g���̃I�u�W�F�N�g��

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffTitle = NULL;								//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_OBJ_AMOUNT] = { NULL };				//�|���S���̃e�N�X�`���ւ̃|�C���^
TITLE g_aTitle[TITLE_OBJ_AMOUNT];												//TITLE�\���̂̏��

//-----------------------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVertex;

	//TITLE�̏�����
	g_aTitle[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title_bg.jpg", &g_pTextureTitle[0]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * TITLE_OBJ_AMOUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntT = 0; nCntT < TITLE_OBJ_AMOUNT; nCntT++)
	{
		switch (nCntT)
		{
		case 0:
			//���_���W D3DXVECTOR3(X,Y, 0.0f);
			pVertex[0].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x, g_aTitle[nCntT].pos.y +SCREEN_HEIGHT, 0.0f);
			pVertex[1].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x, g_aTitle[nCntT].pos.y, 0.0f);
			pVertex[2].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x + SCREEN_WIDTH, g_aTitle[nCntT].pos.y + SCREEN_HEIGHT, 0.0f);
			pVertex[3].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x + SCREEN_WIDTH, g_aTitle[nCntT].pos.y, 0.0f);
			break;

		default:
			break;
		}

		//rhw�̐ݒ�
		pVertex[0].rhw = 1.0f;	//1.0f�Œ�
		pVertex[1].rhw = 1.0f;
		pVertex[2].rhw = 1.0f;
		pVertex[3].rhw = 1.0f;

		switch (nCntT)
		{
		case 0:
			//���_�J���[�̐ݒ�
			pVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //D3DCOLOR_RGBA(��, ��, ��, �����x);
			pVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;

		default:
			break;
		}

		//���_���̐ݒ�
		pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVertex += 4; //���_���炵
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�t�F�[�h�C��
	SetFade(FADE_IN, MODE_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTex = 0; nCntTex < TITLE_OBJ_AMOUNT; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}

}

//-----------------------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//-----------------------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntTex = 0; nCntTex < TITLE_OBJ_AMOUNT; nCntTex++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntTex]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}
}