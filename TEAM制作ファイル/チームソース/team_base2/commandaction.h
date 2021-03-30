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

#define CA_ATTACK_RADIUS (150.0f)
#define CA_ATTACK_KNOCKBACK_KATANA (10.0f)
#define CA_ATTACK_KNOCKBACK_NAGINATA (20.0f)
#define CA_ATTACK_DAMAGE (3)

#define CA_TIMEREMAIN_OBJ (2)			// �c�莞�ԂŎg���I�u�W�F�N�g��
#define CA_TIMEREMAIN_WIDTH (600)		// �c�莞�Ԃ̃o�[��
#define CA_TIMEREMAIN_HEIGHT (15)		// �c�莞�Ԃ̃o�[����
#define CA_TIMEREMAIN_TIMELIMIT (3000)	// ���͂̐�������(�~���b)

#define CA_USEPOWER_MAX (2)
#define CA_CIRCLE_RADIUS (150.0f)	// circle radius

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
// �c�莞�ԃo�[�̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff[CA_TIMEREMAIN_OBJ];	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 pTexture[CA_TIMEREMAIN_OBJ];			// �e�N�X�`��
	D3DXVECTOR3 pos[CA_TIMEREMAIN_OBJ];						// �ʒu
	DWORD dwStartTime;										// �J�n����
	DWORD dwCurrentTime;									// ���ݎ���
	DWORD dwRemainTime;										// �c�莞��
} TimeRemain;

//-----------------------------------------------------------------------------
// �͈̓T�[�N���̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX	mtxWorld;				// worldmtx
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 pTexture;		// �e�N�X�`��
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// rot
} ActionCircle;

//-----------------------------------------------------------------------------
// �R�}���h�A�N�V�����\����
//-----------------------------------------------------------------------------
typedef struct
{
	CAButton buttonInfo;				// �{�^���̏��
	TimeRemain remainTimeInfo;			// �c�莞�Ԃ̏��
	ActionCircle actionCircle;			// �͈̓T�[�N���̏��
	int nActionOrder[CA_BUTTON_NUM];	// �{�^������������
	int nActionOrderOut[CA_BUTTON_NUM];	// ���ۂɉ����ꂽ����
	int nActionNum;						// �{�^����������
	int nActionNumCorrect;				// �������{�^��������������
	int nActionCounter;					// �J�E���^�[
	bool bPress;						// ���͂̃t���O�Ǘ�
	bool bActive;						// �A�N�e�B�u���ǂ���
	bool bUsable;
	int nUsePower;
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


