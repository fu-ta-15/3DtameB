//-----------------------------------------------------------------------------
//
// �{�X�̏��� �w�b�_�[ [boss.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include <time.h>

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define BOSS_MODEL_PARTS (8)
#define BOSS_COL_HEIGHT (50)	// �{�X�̍��� (����p)
#define BOSS_COL_WIDTH (35)		// ��

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
	Model aModel[BOSS_MODEL_PARTS];		// �p�[�c
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
	KEY DefKey[BOSS_MODEL_PARTS];	// �����z�u

	int nLifeMax;								// �ő�̗�
	int nLife;									// �̗�
	bool bUse;									// �g�p����
	bool bHit;									// �U�����蒆��
	bool bInvincible;							// ���G���
	bool bAttack;								// �U������
	DWORD dwTimeInv;							// ���G���Ԍv�Z�p
	DWORD dwTimeAtk;							// �U�����Ԍv�Z�p
} Boss;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
Boss *GetBoss(void);
void SetBoss(D3DXVECTOR3 pos, ENEMYTYPE type);
#endif


