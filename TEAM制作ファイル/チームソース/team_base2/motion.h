//-----------------------------------------------------------------------------
//
// ���[�V�����̏��� �w�b�_�[ [motion.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MOTION_MAX (20) // max amount of motion

//-----------------------------------------------------------------------------
// ���[�V�����̎��
//-----------------------------------------------------------------------------
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,			// �j���[�g�������[�V����
	MOTIONTYPE_ATTACK,				// �U�����[�V����
	MOTIONTYPE_SLASH,
	MOTIONTYPE_WALK,				// �������[�V����

	MOTIONTYPE_ROBOT000_NEUTRAL,
	MOTIONTYPE_ROBOT000_WALK,
	MOTIONTYPE_ROBOT000_ATTACK,
	MOTIONTYPE_ROBOT000_DAMAGED,

	MOTIONTYPE_ROBOT001_NEUTRAL,
	MOTIONTYPE_ROBOT001_WALK,
	MOTIONTYPE_ROBOT001_ATTACK,
	MOTIONTYPE_ROBOT001_DAMAGED,

	MOTIONTYPE_BOSS_NEUTRAL,
	MOTIONTYPE_BOSS_WALK,
	MOTIONTYPE_BOSS_ATTACK,

	MOTIONTYPE_CYBORG_NEUTRAL,
	MOTIONTYPE_CYBORG_WALK,
	MOTIONTYPE_CYBORG_KATANA_ATTACK,
	MOTIONTYPE_CYBORG_NAGINATA_ATTACK,

	MOTIONTYPE_MAX
} MOTIONTYPE;

//-----------------------------------------------------------------------------
// �I��p
//-----------------------------------------------------------------------------
typedef enum
{
	SELECTMOTION_PLAYER,		// �֐����g�����ɑI������p
	SELECTMOTION_PLAYERBLEND,
	SELECTMOTION_ENEMY,
	SELECTMOTION_BOSS,
	SELECTMOTION_MAX
} SELECTMOTION;

//-----------------------------------------------------------------------------
// �L�[�̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	float fPosX;		// �ʒuX
	float fPosY;		// �ʒuY
	float fPosZ;		// �ʒuZ
	float fRotX;		// ����X
	float fRotY;		// ����Y
	float fRotZ;		// ����Z
} KEY;

//-----------------------------------------------------------------------------
// �L�[���̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	int nFrame;			// �Đ��t���[��
	KEY aKey[20];		// �L�[ (�p�[�c�ő吔��)
} KEY_INFO;

//-----------------------------------------------------------------------------
// ���[�V�������̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	bool bLoop;					// ���[�v�̗L��
	int nNumKey;				// �L�[�̑���
	KEY_INFO aKeyInfo[20];		// �L�[���	(�L�[�̍ő吔)
} MOTION_INFO;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitMotion(void);
void UninitMotion(void);
void UpdateMotion(void);
void DrawMotion(void);
KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
void StartMotion(SELECTMOTION motionSelect, MOTIONTYPE motionType, int nIdxEnemy);
void MotionText(const char* cXFileName);
void InitMotionRobot000(void);
void InitMotionRobot001(void);
void ResetMotion(SELECTMOTION resetType, bool bPartsReset, bool bCounterReset, bool bKeyReset, bool bMotionTrig, int nIdxEnemy);

#endif