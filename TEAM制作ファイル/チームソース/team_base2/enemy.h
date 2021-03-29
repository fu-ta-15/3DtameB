//-----------------------------------------------------------------------------
//
// �G�̏��� �w�b�_�[ [enemy.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "game.h"
#include "player.h"
#include <time.h>

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define ENENY_AMOUNT_SNAKE (32)		// �ւ̓G��p�ӂ��鐔
#define ENEMY_AMOUNT_ROBOT (32)		// ���{�b�g
#define ENEMY_AMOUNT_MAX (ENENY_AMOUNT_SNAKE + ENEMY_AMOUNT_ROBOT)			// �p�ӂ��Ă���G�̍ő吔
#define ENEMY_MODEL_PARTS_MAX (10)	// �g�p�ł���ő�p�[�c��
#define ENEMY_ROBOT_MODELPARTS (10)	// amount of parts of robot model
#define ENEMY_ROBOT001_MODELPARTS (8)	

#define ENEMY_ROBOT000_COL_HEIGHT (20)				// ���{�b�g000�̍��� (����p)
#define ENEMY_ROBOT000_COL_WIDTH (20)				// ��
#define ENEMY_ROBOT001_COL_HEIGHT (35)				// 001
#define ENEMY_ROBOT001_COL_WIDTH (35)				// 

#define ENEMY_KNOCKBACK (10)			// �m�b�N�o�b�N��
#define ENEMY_INVINCIBLE_TIME (500)		// �U�����ꂽ���̖��G����
#define ENEMY_FALLSPEED (0.4f)			// �������x
#define ENEMY_DETECT_RADIUS (200)		// �G���m����
#define ENEMY_DETECT_RADIUS_RANGED (500)
#define ENEMY_MOVESPEED (0.2f)			// �ړ����x
#define ENEMY_ATTACK_RADIUS (35)		// �U���͈�
#define ENEMY_ATTACK_RADIUS_RANGED (300)
#define ENEMY_ATTACK_COOLTIME (1000)	// �U��CT
#define ENEMY_ATTACK_BULLETSPEED (2)
#define ENEMY_HP_MAX (3)				// �G�̗̑�

//-----------------------------------------------------------------------------
// enemy type
//-----------------------------------------------------------------------------
typedef enum
{
	ENEMYTYPE_ROBOT000,	// robot
	ENEMYTYPE_ROBOT001,
	ENEMYTYPE_BOSS,
	ENEMYTYPE_MAX
} ENEMYTYPE;

//-----------------------------------------------------------------------------
// �G�̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;							// �ʒu
	D3DXVECTOR3 posOld;							// �O��̈ʒu
	D3DXVECTOR3 move;							// �ړ�
	D3DXVECTOR3 rot;							// ����
	D3DXVECTOR3 rotDest;						// �ڕW�̌���
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	ENEMYTYPE type;								// �G�̎��
	Model aModel[ENEMY_MODEL_PARTS_MAX];		// �p�[�c
	float fWidth;								// ��
	float fDepth;								// ���s
	float fHeight;								// ����

	bool bPlayMotion;							// ���[�V�����Đ����
	MOTION_INFO aMotionInfo[MOTION_MAX];		// ���[�V�������	 (���[�V�����̍ő吔)
	MOTIONTYPE motionType;						// ���[�V�����^�C�v
	bool bLoopMotion;							// ���[�v�̗L��
	int nCurrentMotion;							// ���݂̃��[�V����
	int nNumMotion;								// ���[�V������
	int nNumKey;								// �L�[��
	int nKey;									// �L�[�i���o�[
	int nCounterMotion;							// ���[�V�����J�E���^�[
	KEY DefKey[ENEMY_MODEL_PARTS_MAX];	// �����z�u

	int nLifeMax;								// �ő�̗�
	int nLife;									// �̗�
	int nIdx;									// ������ID
	bool bUse;									// �g�p����
	bool bHit;									// �U�����蒆��
	bool bInvincible;							// ���G���
	bool bAttack;								// �U������
	DWORD dwTimeInv;							// ���G���Ԍv�Z�p
	DWORD dwTimeAtk;							// �U�����Ԍv�Z�p
} Enemy;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy *GetEnemy(void);
Model *GetEnemyModelParts(ENEMYTYPE type);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type);
void SetTextEnemy(void);

#endif

