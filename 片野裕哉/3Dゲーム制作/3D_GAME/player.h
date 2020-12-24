//
//
// �v���C���[�w�b�_�[ [player.h]
//
//
//
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//
// �}�N����`
//
#define MAX_MODEL (14)		// ���f��(�p�[�c)�̍ő吔(����)

//
// �\����
//
//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,		// �j���[�g�������[�V����
	MOTIOBTYPE_MAX
}MOTIONTYPE;

// �L�[�̍\����
typedef struct
{
	float fPosX;			// �ʒuX
	float fPosY;			// �ʒuY
	float fPosZ;			// �ʒuZ
	float fRotX;			// ����X
	float fRotY;			// ����Y
	float fRotZ;			// ����Z
}KEY;

// �L�[���̍\����
typedef struct
{
	int nFlame;				// �Đ��t���[��
	KEY aKey[MAX_MODEL];	// �e���f���̃L�[�v�f
}KEY_INFO;

// ���[�V�������̍\����
typedef struct
{
	bool bLoop;				// ���[�v���邩�ǂ���
	int nNumKey;			// �L�[�̑���
	KEY_INFO aKeyInfo[4];	// �L�[���
}MOTION_INFO;

typedef struct
{
	LPD3DXMESH pMeshModel = NULL;		// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel = NULL;	// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMatModel = NULL;			// �}�e���A���̐�
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ړ���
	D3DXVECTOR3 rot;					// ����
	D3DXVECTOR3 rotDest;				// �ړI�̌���
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	int nIdxModelParent;				// �e�̃C���f�b�N�X
	D3DXVECTOR3 vtxMinModel;			// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;			// ���f���̍ő�l

} MODEL;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 rotDest;		// �ړI�̌���
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	MODEL aModel[MAX_MODEL];	// ���f��(�p�[�c)
	int nNumModel;				// ���f��(�p�[�c)�̐�

	MOTION_INFO aMotionInfo[1];	// ���[�V�������
	int nNumMotion;				// ���[�V������
	MOTIONTYPE motionType;		// ���[�V�����^�C�v
	bool bLoopMotion;			// ���[�v���邩�ǂ���
	int nNumKey;				// �L�[��
	int nKey;					// �L�[No.
	int nCounterMotion;			// ���[�V�����J�E���^�[
} PLAYER;

typedef enum
{
	MODEL_LABEL_BODY = 0,	// ����
	MODEL_LABEL_HEAD,		// ����
	MODEL_LABEL_ARM_T_R,	// �E�r(���`�I)
	MODEL_LABEL_ARM_U_R,	// �E�r(�I�`���)
	MODEL_LABEL_HAND_R,		// �E��
	MODEL_LABEL_ARM_T_L,	// ���r(���`�I)
	MODEL_LABEL_ARM_U_L,	// ���r(�I�`���)
	MODEL_LABEL_HAND_L,		// ����
	MODEL_LABEL_LEG_T_R,	// �E�r(��)
	MODEL_LABEL_LEG_U_R,	// �E�r(����)
	MODEL_LABEL_FOOT_R,		// �E��
	MODEL_LABEL_LEG_T_L,	// ���r(��)
	MODEL_LABEL_LEG_U_L,	// ���r(����)
	MODEL_LABEL_FOOT_L,		// ����
	MODEL_LABEL_MAX,
} MODEL_LABEL;

//
// �v���g�^�C�v�錾
//
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif