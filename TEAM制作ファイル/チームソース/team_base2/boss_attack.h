//-----------------------------------------------------------------------------
//
// �{�X�U���̏��� �w�b�_�[ [boss_attack.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _BOSS_ATK_H_
#define _BOSS_ATK_H_
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define BOSS_ATTACK_MAX (8)	// �����ɏo����ő吔
#define BOSS_ATTACK_OBJ (2)	// �K�v�ȃI�u�W�F��
#define BOSS_ATTACK_DMG (3)
#define BOSS_ATTACK_RADIUS (100.0f)
//-----------------------------------------------------------------------------
// �U�����̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	LPDIRECT3DVERTEXBUFFER9 pVtx;	// ���_�o�b�t�@

	float fFloorRatio;		// �����L���鎞�̊���
	bool bDraw;				// �`��t���O
	bool bAttackFlag;		// �U���t���O
} AttackFloor;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitBossATK(void);
void UninitBossATK(void);
void UpdateBossATK(void);
void DrawBossATK(void);
void BeginBossAttack(D3DXVECTOR3 pos);

#endif
