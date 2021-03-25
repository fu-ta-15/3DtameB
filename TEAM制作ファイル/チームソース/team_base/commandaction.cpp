//-----------------------------------------------------------------------------
//
// �R�}���h�A�N�V�����̏��� [commandaction.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "commandaction.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include <time.h>

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitCommandButton(void);	// �R�}���h�{�^��������
void DrawCommandButton(void);		// ���̕`��
HRESULT InitTimeRemain(void);		// ���͎c�莞�Ԃ̏�����
void DrawTimeRemain(void);			// ���̕`��
HRESULT InitActionCircle(void);		// �͈̓T�[�N���̏�����
void DrawActionCircle(void);		// ���̕`��

void SetCommandActionState(bool bActive);
void OnPlayerFinishAction(void);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
CommandAction g_commandAct;						// �R�}���h�A�N�V�����̏��
PWEAPON playerWeaponTest = PWEAPON_NAGINATA;		// �v���C���[�̎����Ă��镐�� (���player�\���̂̕����g���j

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾
	srand((unsigned)time(0));	// rand������

	//������
	g_commandAct.nActionNum = CA_BUTTON_NUM_NAGINATA;	// �\������{�^���̐�
	g_commandAct.nActionCounter = 0;					// �J�E���^�[������
	for (int nCntBtn = 0; nCntBtn < g_commandAct.nActionNum; nCntBtn++)
	{
		//�{�^���̐��ɂ���Ĉʒu��ς���
		g_commandAct.buttonInfo.pos[nCntBtn] = D3DXVECTOR3(nCntBtn * CA_BUTTON_SPACE + CA_BUTTON_POS_X - CA_BUTTON_SPACE * (float)g_commandAct.nActionNum / 2, CA_BUTTON_POS_Y, 0.0f);
	}
	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
	{
		//���Ԃ������_���Ō���
		g_commandAct.nActionOrder[nCntBtn] = rand() % CA_BUTTON_TYPE;

		//�����ꂽ���Ԃ�������
		g_commandAct.nActionOrderOut[nCntBtn] = 0;
	}

	//�R�}���h�{�^���̏�����
	InitCommandButton();

	//���͎c�莞�Ԃ̏�����
	InitTimeRemain();

	//�͈̓T�[�N��
	InitActionCircle();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitCommand(void)
{
	//�{�^���̉������
	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_TYPE; nCntBtn++)
	{
		//�e�N�X�`���̊J��
		if (g_commandAct.buttonInfo.pTexture[nCntBtn] != NULL)
		{
			g_commandAct.buttonInfo.pTexture[nCntBtn]->Release();
			g_commandAct.buttonInfo.pTexture[nCntBtn] = NULL;
		}
	}
	if (g_commandAct.buttonInfo.pVtxBuff != NULL)
	{
		g_commandAct.buttonInfo.pVtxBuff->Release();
		g_commandAct.buttonInfo.pVtxBuff = NULL;
	}

	//�c�莞�ԃQ�[�W�̉������
	for (int nCntOBJ = 0; nCntOBJ < CA_TIMEREMAIN_OBJ; nCntOBJ++)
	{
		if (g_commandAct.remainTimeInfo.pVtxBuff[nCntOBJ] != NULL)
		{
			g_commandAct.remainTimeInfo.pVtxBuff[nCntOBJ]->Release();
			g_commandAct.remainTimeInfo.pVtxBuff[nCntOBJ] = NULL;
		}
		if (g_commandAct.remainTimeInfo.pTexture[nCntOBJ] != NULL)
		{
			g_commandAct.remainTimeInfo.pTexture[nCntOBJ]->Release();
			g_commandAct.remainTimeInfo.pTexture[nCntOBJ] = NULL;
		}
	}

	//�͈̓T�[�N���̉������
	if (g_commandAct.actionCircle.pVtxBuff != NULL)
	{
		g_commandAct.actionCircle.pVtxBuff->Release();
		g_commandAct.actionCircle.pVtxBuff = NULL;
	}
	if (g_commandAct.actionCircle.pTexture != NULL)
	{
		g_commandAct.actionCircle.pTexture->Release();
		g_commandAct.actionCircle.pTexture = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateCommand(void)
{
	Player *pPlayer = GetPlayer();

	//�͈̓T�[�N���̈ʒu���v���C���[�̏ꏊ��
	g_commandAct.actionCircle.pos = pPlayer->pos;

	//�v���C���[�̎����Ă镐��ɂ���ăR�}���h�̐���ς���
	switch (playerWeaponTest)
	{
	case PWEAPON_KATANA:
		g_commandAct.nActionNum = CA_BUTTON_NUM_KATANA;
		break;

	case PWEAPON_NAGINATA:
		g_commandAct.nActionNum = CA_BUTTON_NUM_NAGINATA;
		break;
	default:
		break;
	}

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVertexButton;
	g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
	{
		//���_���W�̍X�V
		pVertexButton[0].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIP�Ŏl�p
		pVertexButton[1].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_commandAct.buttonInfo.pVtxBuff->Unlock();

	if (GetKeyboardTrigger(DIK_B) == true) SetCommandActionState(true);
	if (g_commandAct.nActionCounter >= g_commandAct.nActionNum) SetCommandActionState(false);

	//�R�}���h���͂̕���
	if (g_commandAct.bActive == true)
	{
		VERTEX_2D *pVertexButton1;
		//���_�o�b�t�@���b�N
		g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton1, 0);

		//����
		if (GetKeyboardTrigger(DIK_1) == true)			// A
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 0;	// ���͂����{�^��������
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;			// ���_�̃|�C���^���J�E���^�̏ꏊ�܂ł��炷
			g_commandAct.bPress = true;	// ���̓t���O�����
		}
		else if (GetKeyboardTrigger(DIK_2) == true)		// B
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 1;
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;
			g_commandAct.bPress = true;
		}
		else if (GetKeyboardTrigger(DIK_3) == true)		// X
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 2;
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;
			g_commandAct.bPress = true;
		}
		else if (GetKeyboardTrigger(DIK_4) == true)		// Y
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 3;
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;

			g_commandAct.bPress = true;
		}

		if (g_commandAct.nActionCounter >= 0 && g_commandAct.nActionCounter < g_commandAct.nActionNum && g_commandAct.bPress == true)
		{// �J�E���^���͈͓��Ŏw��L�[�������ꂽ��
			if (g_commandAct.nActionOrder[g_commandAct.nActionCounter] == g_commandAct.nActionOrderOut[g_commandAct.nActionCounter])
			{//	���͂̃{�^���Ǝw������v���Ă����ꍇ
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton1[nCntVtx].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);	// �F�ς���

				g_commandAct.nActionNumCorrect++;	// ���𐔂Ƀv���X

				g_commandAct.nActionCounter++;	// �J�E���g�A�b�v
				g_commandAct.bPress = false;	// ���̓t���O�؂�
			}
			else if (g_commandAct.nActionOrder[g_commandAct.nActionCounter] != g_commandAct.nActionOrderOut[g_commandAct.nActionCounter])
			{// ���͂̃{�^���Ǝw������v���Ă��Ȃ������ꍇ
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton1[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);	// �F�ς���

				g_commandAct.nActionCounter++;	// �J�E���g�A�b�v
				g_commandAct.bPress = false;	// ���̓t���O�؂�
			}
		}

		//�A�����b�N
		g_commandAct.buttonInfo.pVtxBuff->Unlock();


		/* �c�莞�Ԃ̏��� */
		float fValueTime = 1.0f;	// �c�莞�Ԃ̊���

		g_commandAct.remainTimeInfo.dwCurrentTime = timeGetTime();	// ���ݎ���

		//�c�莞�Ԃ��v�Z
		g_commandAct.remainTimeInfo.dwRemainTime = (g_commandAct.remainTimeInfo.dwCurrentTime - g_commandAct.remainTimeInfo.dwStartTime) - CA_TIMEREMAIN_TIMELIMIT * 2;
		g_commandAct.remainTimeInfo.dwRemainTime = g_commandAct.remainTimeInfo.dwRemainTime * -1;

		//�������v�Z
		fValueTime = (float)(g_commandAct.remainTimeInfo.dwRemainTime - CA_TIMEREMAIN_TIMELIMIT) / (float)CA_TIMEREMAIN_TIMELIMIT;

		//���_�o�b�t�@�̃��b�N
		VERTEX_2D *pVertexFront;
		g_commandAct.remainTimeInfo.pVtxBuff[1]->Lock(0, 0, (void**)&pVertexFront, 0);

		//���_���W�A�e�N�X�`�����W�̍X�V
		pVertexFront[0].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x - (CA_TIMEREMAIN_WIDTH * fValueTime), g_commandAct.remainTimeInfo.pos[1].y + CA_TIMEREMAIN_HEIGHT, 0.0f);
		pVertexFront[1].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x - (CA_TIMEREMAIN_WIDTH * fValueTime), g_commandAct.remainTimeInfo.pos[1].y - CA_TIMEREMAIN_HEIGHT, 0.0f);
		pVertexFront[2].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x, g_commandAct.remainTimeInfo.pos[1].y + CA_TIMEREMAIN_HEIGHT, 0.0f);
		pVertexFront[3].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x, g_commandAct.remainTimeInfo.pos[1].y - CA_TIMEREMAIN_HEIGHT, 0.0f);

		pVertexFront[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertexFront[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertexFront[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVertexFront[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//���_�o�b�t�@�̃A�����b�N
		g_commandAct.remainTimeInfo.pVtxBuff[1]->Unlock();

		//�c�莞�Ԃ�0�b�ɂȂ�����
		if (g_commandAct.remainTimeInfo.dwRemainTime <= CA_TIMEREMAIN_TIMELIMIT)
		{
			SetCommandActionState(false);
		}
	}



}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawCommand(void)
{
	if (g_commandAct.bActive == true)
	{
		//�R�}���h�{�^���̕`��
		DrawCommandButton();

		//���͎c�莞�Ԃ̕`��
		DrawTimeRemain();
	}
	
	//�͈̓T�[�N��
	DrawActionCircle();
}

//-----------------------------------------------------------------------------
// �R�}���h�A�N�V�����̏����擾
//-----------------------------------------------------------------------------
CommandAction *GetCAction(void)
{
	return &g_commandAct;
}

/* �R�}���h�{�^���̏����� */
HRESULT InitCommandButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command A00.png", &g_commandAct.buttonInfo.pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command B00.png", &g_commandAct.buttonInfo.pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command X00.png", &g_commandAct.buttonInfo.pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command Y00.png", &g_commandAct.buttonInfo.pTexture[3]);

	//���_�o�b�t�@�̐��� �{�^��
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * CA_BUTTON_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_commandAct.buttonInfo.pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexButton;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
	{
		//���_���W D3DXVECTOR3(X,Y, 0.0f);
		pVertexButton[0].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIP�Ŏl�p
		pVertexButton[1].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);

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
	g_commandAct.buttonInfo.pVtxBuff->Unlock();

	return S_OK;
}

/* ���͎c�莞�Ԃ̏����� */
HRESULT InitTimeRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	//������
	g_commandAct.remainTimeInfo.pos[0] = D3DXVECTOR3(SCREEN_WIDTH / 2 - CA_TIMEREMAIN_WIDTH / 2, 900, 0.0f);
	g_commandAct.remainTimeInfo.pos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2 + CA_TIMEREMAIN_WIDTH / 2, 900, 0.0f);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, NULL, &g_commandAct.remainTimeInfo.pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, NULL, &g_commandAct.remainTimeInfo.pTexture[1]);

	/* ��둤�̃o�[ */
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_commandAct.remainTimeInfo.pVtxBuff[0], NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexBack;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_commandAct.remainTimeInfo.pVtxBuff[0]->Lock(0, 0, (void**)&pVertexBack, 0);

	//���_���W D3DXVECTOR3(X,Y, 0.0f);
	pVertexBack[0].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[0].x, g_commandAct.remainTimeInfo.pos[0].y + CA_TIMEREMAIN_HEIGHT, 0.0f);		 //TRIANGLESTRIP�Ŏl�p
	pVertexBack[1].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[0].x, g_commandAct.remainTimeInfo.pos[0].y - CA_TIMEREMAIN_HEIGHT, 0.0f);
	pVertexBack[2].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[0].x + CA_TIMEREMAIN_WIDTH, g_commandAct.remainTimeInfo.pos[0].y + CA_TIMEREMAIN_HEIGHT, 0.0f);
	pVertexBack[3].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[0].x + CA_TIMEREMAIN_WIDTH, g_commandAct.remainTimeInfo.pos[0].y - CA_TIMEREMAIN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexBack[nCntVtx].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexBack[nCntVtx].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//���_���̐ݒ�
	pVertexBack[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertexBack[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertexBack[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertexBack[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_commandAct.remainTimeInfo.pVtxBuff[0]->Unlock();

	/* ��O�̃o�[ */
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_commandAct.remainTimeInfo.pVtxBuff[1], NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexFront;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_commandAct.remainTimeInfo.pVtxBuff[1]->Lock(0, 0, (void**)&pVertexFront, 0);

	//���_���W D3DXVECTOR3(X,Y, 0.0f);
	pVertexFront[0].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x, g_commandAct.remainTimeInfo.pos[1].y + CA_TIMEREMAIN_HEIGHT, 0.0f);
	pVertexFront[1].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x, g_commandAct.remainTimeInfo.pos[1].y - CA_TIMEREMAIN_HEIGHT, 0.0f);
	pVertexFront[2].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x + CA_TIMEREMAIN_WIDTH, g_commandAct.remainTimeInfo.pos[1].y + CA_TIMEREMAIN_HEIGHT, 0.0f);
	pVertexFront[3].pos = D3DXVECTOR3(g_commandAct.remainTimeInfo.pos[1].x + CA_TIMEREMAIN_WIDTH, g_commandAct.remainTimeInfo.pos[1].y - CA_TIMEREMAIN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexFront[nCntVtx].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexFront[nCntVtx].col = D3DXCOLOR(0.5f, 1.0f, 0.0, 1.0f);

	//���_���̐ݒ�
	pVertexFront[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertexFront[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertexFront[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertexFront[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@�A�����b�N
	g_commandAct.remainTimeInfo.pVtxBuff[1]->Unlock();

	return S_OK;
}

/* �͈̓T�[�N���̏����� */
HRESULT InitActionCircle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|�[�^���̏�񏉊���
	g_commandAct.actionCircle.pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//circle.png", &g_commandAct.actionCircle.pTexture);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT,		//�T�C�Y
		D3DUSAGE_WRITEONLY,												//
		FVF_VERTEX_3D,													//�t�H�[�}�b�g
		D3DPOOL_MANAGED,												//
		&g_commandAct.actionCircle.pVtxBuff,							//���_�o�b�t�@�ւ̃|�C���^
		NULL);

	VERTEX_3D *pVertex;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_commandAct.actionCircle.pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);

	//���_���W�ݒ�
	pVertex[0].pos = D3DXVECTOR3(-CA_CIRCLE_RADIUS, 0.0f, -CA_CIRCLE_RADIUS);
	pVertex[1].pos = D3DXVECTOR3(-CA_CIRCLE_RADIUS, 0.0f, CA_CIRCLE_RADIUS);
	pVertex[2].pos = D3DXVECTOR3(CA_CIRCLE_RADIUS, 0.0f, -CA_CIRCLE_RADIUS);
	pVertex[3].pos = D3DXVECTOR3(CA_CIRCLE_RADIUS, 0.0f, CA_CIRCLE_RADIUS);

	//�@���x�N�g���̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_commandAct.actionCircle.pVtxBuff->Unlock();

	return S_OK;
}

/* �R�}���h�{�^���̕`�� */
void DrawCommandButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	for (int nCntBtn = 0; nCntBtn < g_commandAct.nActionNum; nCntBtn++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_commandAct.buttonInfo.pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_commandAct.buttonInfo.pTexture[g_commandAct.nActionOrder[nCntBtn]]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBtn * 4, 2);
	}
}

/* ���͎c�莞�Ԃ̕`�� */
void DrawTimeRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	for (int nCntOBJ = 0; nCntOBJ < CA_TIMEREMAIN_OBJ; nCntOBJ++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_commandAct.remainTimeInfo.pVtxBuff[nCntOBJ], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_commandAct.remainTimeInfo.pTexture[nCntOBJ]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
	}
}

/* �͈̓T�[�N���̕`�� */
void DrawActionCircle(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxTrans, mtxRot;		// �v�Z�p�}�g���b�N�X

	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�����̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X�i�`�挳�j�̍������@�̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	//�f�X�e�B�l�[�V�����i�`���j�̍������@�̐ݒ�

	//�J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_commandAct.actionCircle.mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_commandAct.actionCircle.rot.y, g_commandAct.actionCircle.rot.x, g_commandAct.actionCircle.rot.z);
	D3DXMatrixMultiply(&g_commandAct.actionCircle.mtxWorld, &g_commandAct.actionCircle.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_commandAct.actionCircle.pos.x, g_commandAct.actionCircle.pos.y, g_commandAct.actionCircle.pos.z);
	D3DXMatrixMultiply(&g_commandAct.actionCircle.mtxWorld, &g_commandAct.actionCircle.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_commandAct.actionCircle.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_commandAct.actionCircle.pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_commandAct.actionCircle.pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�J�����O�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X�i�`�挳�j�̍������@�̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�f�X�e�B�l�[�V�����i�`���j�̍������@�̐ݒ�
}

/* �R�}���h�A�N�V�����̏�Ԃ�ݒ肷�� */
void SetCommandActionState(bool bActive)
{
	if (bActive == true)
	{// �J�n
		srand((unsigned)time(0));

		g_commandAct.bActive = true;		// ��A�N�e�B�u��
		g_commandAct.bPress = false;		// ���̓t���O���Z�b�g
		g_commandAct.nActionCounter = 0;	// �J�E���^�[���Z�b�g
		g_commandAct.nActionNumCorrect = 0;	// ���������Z�b�g
		g_commandAct.remainTimeInfo.dwStartTime = timeGetTime();	// ���݂̎��Ԃ��擾

		for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
		{//	�{�^���̐�����
			g_commandAct.nActionOrder[nCntBtn] = rand() % CA_BUTTON_TYPE;		// �������ԃ����_���ݒ�
			g_commandAct.nActionOrderOut[nCntBtn] = 0;						// ���������ԃ��Z�b�g
		}

		//�����{�^������ݒ�
		if (playerWeaponTest == PWEAPON_KATANA) g_commandAct.nActionNum = CA_BUTTON_NUM_KATANA;
		else if (playerWeaponTest == PWEAPON_NAGINATA) g_commandAct.nActionNum = CA_BUTTON_NUM_NAGINATA;
	}
	else
	{//	�I��
		OnPlayerFinishAction();

		g_commandAct.bActive = false;		// ��A�N�e�B�u��
		g_commandAct.bPress = false;		// ���̓t���O���Z�b�g
		g_commandAct.nActionCounter = 0;	// �J�E���^�[���Z�b�g
		g_commandAct.nActionNum = 0;		// ���������Z�b�g
		g_commandAct.nActionNumCorrect = 0;	// ���������Z�b�g
		g_commandAct.remainTimeInfo.dwRemainTime = 0;	// �c�莞�ԃ��Z�b�g

		for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
		{//	�{�^���̐�����
			g_commandAct.nActionOrder[nCntBtn] = 0;		// �������ԃ��Z�b�g
			g_commandAct.nActionOrderOut[nCntBtn] = 0;	// ���������ԃ��Z�b�g
		}

		//���_�o�b�t�@���b�N
		VERTEX_2D *pVertexButton;
		g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

		for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
		{
			for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�A�����b�N
		g_commandAct.buttonInfo.pVtxBuff->Unlock();
	}
}

/* �R�}���h�A�N�V�����I����ɌĂ΂�� */
void OnPlayerFinishAction(void)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_ATTACK, NULL);

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//�G�Ƃ̋��� �������l���Ȃ�
		float fDistanceToEnemy = sqrtf((pPlayer->pos.x - pEnemy[nCntEnemy].pos.x) * ((pPlayer->pos.x) - pEnemy[nCntEnemy].pos.x) + (pPlayer->pos.z - pEnemy[nCntEnemy].pos.z) * (pPlayer->pos.z - pEnemy[nCntEnemy].pos.z));

		//���������m�͈͈ȓ���������
		if (fDistanceToEnemy <= CA_ATTACK_RADIUS)
		{
			//�v���C���[����G�ւ̒P�ʃx�N�g��
			D3DXVECTOR3 vecPtoE = pEnemy[nCntEnemy].pos - pPlayer->pos;
			D3DXVec3Normalize(&vecPtoE, &vecPtoE);

			//�G�m�b�N�o�b�N
			pEnemy[nCntEnemy].move.x += vecPtoE.x * CA_ATTACK_KNOCKBACK;
			pEnemy[nCntEnemy].move.y += 10.0f;
			pEnemy[nCntEnemy].move.z += vecPtoE.z * CA_ATTACK_KNOCKBACK;
			
		}
	}
}

