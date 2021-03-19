//-----------------------------------------------------------------------------
//
// �R�}���h�A�N�V���� �w�b�_�[ [commandaction.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _COMMANDACTION_H_
#define _COMMANDACTION_H_
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define CA_BUTTON_NUM_KATANA (4)
#define CA_BUTTON_NUM_NAGINATA (5)
#define CA_BUTTON_NUM (5)
#define CA_BUTTON_TYPE (4)
#define CA_BUTTON_WIDTH (50.0f)
#define CA_BUTTON_HEIGHT (50.0f)
#define CA_BUTTON_SPACE (75.0f)
#define CA_BUTTON_POS_X (SCREEN_WIDTH / 2)
#define CA_BUTTON_POS_Y (SCREEN_WIDTH / 2)
#define CA_ATTACK_RADIUS (500.0f)
#define CA_ATTACK_KNOCKBACK (50.0f)

//-----------------------------------------------------------------------------
// �{�^���\����
//-----------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;				// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 pTexture[CA_BUTTON_TYPE];	// �e�N�X�`��
	D3DXVECTOR3 pos[CA_BUTTON_NUM];					// �ʒu
} CAButton;

//-----------------------------------------------------------------------------
// �R�}���h�A�N�V�����\����
//-----------------------------------------------------------------------------
typedef struct
{
	CAButton buttonInfo;				// �{�^���̏��
	int nActionOrder[CA_BUTTON_NUM];	// �{�^������������
	int nActionOrderOut[CA_BUTTON_NUM];	// ���ۂɉ����ꂽ����
	int nActionNum;						// �{�^����������
	int nActionNumCorrect;				// �������{�^��������������
	int nActionCounter;					// �J�E���^�[
	bool bPress;						// ���͂̃t���O�Ǘ�
	bool bActive;						// �A�N�e�B�u���ǂ���
	int nTest;
} CommandAction;

//-----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitCommand(void);
void UninitCommand(void);
void UpdateCommand(void);
void DrawCommand(void);
CommandAction *GetCAction(void);

#endif


