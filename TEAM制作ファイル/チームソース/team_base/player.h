//-----------------------------------------------------------------------------
//
// �v���C���[�̏��� �w�b�_�[ [player.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PLAYER_MOVESPEED (0.5f)													// �v���C���[�̈ړ����x
#define PLAYER_MODEL_AMOUNT (11)
#define PLAYER_ATTACK_RADIUS (12.0f)											// �v���C���[�̍U���͈�
#define PlAYER_WIDTH (7.5f)
#define PLAYER_HEIGHT (50.0f)
#define PLAYER_INVINCIBLE_TIME (500)	// �U�����ꂽ���̖��G����
#define PLAYER_HEALTH (10)				// �v���C���[�̗̑�

#define PLAYER_WEAPON_TYPE (2)			// �v���C���[�̕���̎��
#define PLAYER_WEAPON_COLLISION_COMPONENTS (3)

//-----------------------------------------------------------------------------
// �v���C���[�������Ă��镐��
//-----------------------------------------------------------------------------
typedef enum
{
	PWEAPON_KATANA,		// ��
	PWEAPON_NAGINATA,	// �㓁
	PWEAPON_MAX
} PWEAPON;

//-----------------------------------------------------------------------------
// �t�@�C������ǂ�ł���L�����N�^�[�̃��f�����̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	int nModelNum;						// ���f���̐�	
	int nModelIdx[20];					// ���f���̔ԍ�
	int nModelParent[20];				// ���f���̐e
	char cModelFileName[20][256];		// ���f���̃t�@�C����
	float fModelPos[20][3];				// ���f���̈ʒu(�I�t�Z�b�g)
	float fModelRot[20][3];				// ���f���̌���

} CharacterPartsInfo;

//-----------------------------------------------------------------------------
// ���f���̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMeshModel;				// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel;			// �}�e���A���ւ̃|�C���^
	DWORD nNumMatModel;					// �}�e���A���̐�
	D3DXVECTOR3 pos;					// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	int nIdxModelParent;				// �e���f���̃C���f�b�N�X
	LPDIRECT3DTEXTURE9 pTexture[10];	// texture
	int nNumModel;
} Model;

//-----------------------------------------------------------------------------
// �v���C���[�̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 posOld;						// �O��̈ʒu
	D3DXVECTOR3 move;						// �ړ��l
	D3DXVECTOR3 rot;						// ����
	D3DXVECTOR3 rotDest;					// �ڕW�̌���
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	Model aModel[PLAYER_MODEL_AMOUNT];		// ���f��(�p�[�c)
	Model AltWeapon;						// ����i�p�[�c�j
	int nNumModel;							// ���f��(�p�[�c)��

	bool bPlayMotion;						// ���[�V�����Đ����
	MOTION_INFO aMotionInfo[MOTION_MAX];	// ���[�V�������	 (���[�V�����̍ő吔)
	MOTIONTYPE motionType;					// ���[�V�����^�C�v
	bool bLoopMotion;						// ���[�v�̗L��
	int nCurrentMotion;						// ���݂̃��[�V����
	int nNumMotion;							// ���[�V������
	int nNumKey;							// �L�[��
	int nKey;								// �L�[�i���o�[
	int nCounterMotion;						// ���[�V�����J�E���^�[

	bool bBlendMotion;						// �u�����h���邩�ǂ���
	MOTIONTYPE motionTypeBlend;				// ���̃��[�V�������
	bool bLoopMotionBlend;					// 
	int nNumKeyBlend;						//
	int nKeyBlend;							//
	int nCounterMotionBlend;				//
	int nCounterBlend;
	int nFrameBlend;

	PWEAPON weapon;					// ���ݎ����Ă��镐��
	D3DXMATRIX mtxWeaponCol[PLAYER_WEAPON_COLLISION_COMPONENTS];	// 
	D3DXVECTOR3 posWeaponCol[PLAYER_WEAPON_COLLISION_COMPONENTS];	// 

	int nLifeMax;					// �ő�̗�
	int nLife;						// �̗�
	bool bHit;						// �U������Ă�����
	bool bInvincible;				// ���G���
	DWORD dwTime;					// ���Ԍv�Z�p
} Player;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
KEY *GetDefKey(void);
void ReadCharacterInfo(CharacterPartsInfo *characterInfo, char* fileName);
#endif