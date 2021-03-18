//-----------------------------------------------------------------------------
//
// �R�}���h�A�N�V�����̏��� [commandaction.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "commandaction.h"
#include "input.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitCommand(void);
void UninitCommand(void);
void UpdateCommand(void);
void DrawCommand(void);

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
CAButton g_button;

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT InitCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	//������
	g_button.pos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_button.pos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_button.pos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_button.pos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandA00.png", &g_button.pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandB00.png", &g_button.pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandX00.png", &g_button.pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandY00.png", &g_button.pTexture[3]);

	//���_�o�b�t�@�̐��� �{�^��
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * CA_BUTTON_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_button.pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexButton;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_button.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntButton = 0; nCntButton < CA_BUTTON_NUM; nCntButton++, pVertexButton += 4)
	{
		//���_���W D3DXVECTOR3(X,Y, 0.0f);
		pVertexButton[0].pos = D3DXVECTOR3(0.0f, CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIP�Ŏl�p
		pVertexButton[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(CA_BUTTON_WIDTH, CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(CA_BUTTON_WIDTH, 0.0f, 0.0f);

		//rhw�̐ݒ�
		for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���_���̐ݒ�
		pVertexButton[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertexButton[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertexButton[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVertexButton[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_button.pVtxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitCommand(void)
{

}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void UpdateCommand(void)
{

}

//-----------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------
void DrawCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	for (int nCntButton = 0; nCntButton < CA_BUTTON_NUM; nCntButton++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_button.pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_button.pTexture[nCntButton]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntButton * 4, 2);
	}
}