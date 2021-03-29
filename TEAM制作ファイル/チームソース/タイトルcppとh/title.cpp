//=================================================================================================================
//
// �^�C�g���̏����@�ktitle.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "title.h"
#include "input.h"
#include "player.h"
#include "fade.h"
//#include "sound.h"

//=================================================================================================================
// �}�N����`
//=================================================================================================================

//=================================================================================================================
//�@�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexResult[MAX_TITLE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
int g_nPatternAnim;
int g_nCounterAnim;
float g_TitleMove;		// ���S�̕ϐ�
int g_CntMove;			// ���S�̕ϐ�
bool g_bPush;			// �v�b�V���������ꂽ��
int g_nCntPush;			// �v�b�V���{�^���̕ϐ�
int g_nCntEnter;		// �v�b�V���{�^���̕ϐ�
bool g_bEnter;			// �v�b�V���������ꂽ��

//*****************************************************************************************************************
// �^�C�g���̏���������
//*****************************************************************************************************************
HRESULT InitTitle(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������
	g_nPatternAnim = 0;
	g_nCounterAnim = 0;
	g_TitleMove = 2.0f;
	g_CntMove = 0;
	g_nCntPush = 0;
	g_nCntEnter = 40;
	g_bPush = true;
	g_bEnter = false;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\BG31.jpeg", &g_apTexResult[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\Titil logo00.png", &g_apTexResult[TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\ENTER05.png", &g_apTexResult[TITLE_PUSH]);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_BG)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}
		else if (nCntTitle == TITLE_LOGO)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

		else if (nCntTitle == TITLE_PUSH)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(325, 700, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(325, 550, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(925, 700, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(925, 550, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

		//rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`���[���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//PlaySound(SOUND_LABEL_BGM000);	//�^�C�g�����̃T�E���h

	return S_OK;
}

//*****************************************************************************************************************
// �^�C�g���̏I������
//*****************************************************************************************************************
void UninitTitle(void)
{

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̊J��
		if (g_apTexResult[nCntTitle] != NULL)
		{
			g_apTexResult[nCntTitle]->Release();
			g_apTexResult[nCntTitle] = NULL;
		}
	}
}

//*****************************************************************************************************************
//�@�^�C�g���̍X�V����
//*****************************************************************************************************************
void UpdataTitle(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_bEnter = true;	//�G���^�[�������ꂽ

		//StopSound(SOUND_LABEL_BGM000);	//�T�E���h���~�߂� 
		SetFade(FADE_OUT, MODE_GAME);	//�Q�[����ʂɔ�ԁ��t�F�[�h�A�E�g
	}
	if (g_bEnter == true)
	{
		g_nCntEnter = 5;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_LOGO)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(50.0f, 0.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(50.0f, -370.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800.0f, 0.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, -370.0f + g_TitleMove * g_CntMove, 0.0f);

			if (g_TitleMove * g_CntMove <= 400)
			{
				g_CntMove++;
			}
		}

		//�v�b�V���G���^�[�̓_�ŏ���
		if (nCntTitle == TITLE_PUSH)
		{
			g_nCntPush++;

			if (g_nCntPush >= g_nCntEnter)
			{
				if (g_bPush == true)
				{
					//���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					g_bPush = false;
				}
				else if (g_bPush == false)
				{
					//���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPush = true;
				}
				g_nCntPush = 0;

			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}


//*****************************************************************************************************************
// �^�C�g���̕`�揈��
//*****************************************************************************************************************
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexResult[nCntTitle]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}
}
