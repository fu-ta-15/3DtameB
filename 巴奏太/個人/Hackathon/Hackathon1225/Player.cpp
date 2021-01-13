#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// �v���C���[�̏��� [player.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "player.h"
#include "camera.h"
#include "input.h"
#include "Xinput.h"
#include <stdio.h>

//----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PLAYER_MODEL_AMOUNT (10)
#define PLAYER_SMOOTHTURN_SPEED (0.1f)											// ���炩�ɐU��������x

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed);
void LoadXFile(const char* cXFileName, int nCountModel);
KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
void PlayerSmoothTurn(void);
void PlayMotion(bool bPlayMotion);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Player g_player;																// �v���C���[�̏��
D3DXVECTOR3 g_MotionKey[4][10];													// ���[�V�����̃L�[
bool g_bMotionStart;															// ���[�V�����J�n
int g_nMotionNum;																// ���݂̃��[�V����

void SetPlayer(void)
{
	g_player.nScore = 0;
	g_player.nHp = 3;
	g_player.nTime = 90;
	g_player.bMotionStart = false;
	g_player.bHit = false;
	g_player.nCntHit = 0;
}
//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	SetPlayer();
	LoadXFile("data\\MODEL\\00_robot_body.x", 0);
	LoadXFile("data\\MODEL\\01_robot_head.x", 1);
	LoadXFile("data\\MODEL\\02_robot_armR.x", 2);
	LoadXFile("data\\MODEL\\03_robot_handR.x", 3);
	LoadXFile("data\\MODEL\\04_robot_armL.x", 4);
	LoadXFile("data\\MODEL\\05_robot_handL.x", 5);
	LoadXFile("data\\MODEL\\06_robot_legR.x", 6);
	LoadXFile("data\\MODEL\\07_robot_footR.x", 7);
	LoadXFile("data\\MODEL\\08_robot_legL.x", 8);
	LoadXFile("data\\MODEL\\09_robot_footL.x", 9);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data\Model\00_robot_body.x",					// �ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,								// �Œ�
		pDevice,										// �f�o�C�X
		NULL,											// NULL�Œ�
		&g_player.aModel[0].pBuffMatModel,				// �}�e���A��
		NULL,											// NULL�Œ�
		&g_player.aModel[0].nNumMatModel,				// �}�e���A����
		&g_player.aModel[0].pMeshModel);				// ���b�V��

	g_player.nNumModel = 10;

	//�e�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-7.5f, 12.0f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[4].nIdxModelParent = 0;
	g_player.aModel[4].pos = D3DXVECTOR3(7.5f, 12.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[5].nIdxModelParent = 4;
	g_player.aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[6].nIdxModelParent = 0;
	g_player.aModel[6].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�v���C���[�̏����ݒ�
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu�̏����ݒ�
	g_player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);		// �����̏����ݒ�
	g_player.rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// �����̖ڕW�����ݒ�

															//���[�V�����̐ݒ�
	g_player.nNumMotion = 2;

	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey = 2;
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].bLoop = true;
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].nFrame = 65;
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].nFrame = 65;

	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.07f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.75f, 1.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.06f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.22f, 0.79f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.53f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.22f, -0.79f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, -0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.18f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.06f, 0.0f, 0.09f);
	g_player.aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].nNumKey = 4;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].bLoop = false;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].nFrame = 10;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].nFrame = 10;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].nFrame = 10;
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].nFrame = 30;

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.48f, 0.25f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.44f, -0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -0.97f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.07f, -1.17f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.85f, -0.35f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.4f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.5f, -0.35f, 0.13f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[0].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.59f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.41f, 0.35f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.31f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.19f, 0.66f, -0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, -1.45f, -0.82f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.16f, 1.07f, -1.16f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.72f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.19f, -0.41f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.41f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.5f, -0.41f, 0.13f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[1].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.60f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.41f, -0.44f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.62f, 0.06f, -1.16f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[2].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[0] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.44f, -0.44f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[1] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[2] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.13f, -1.23f, -0.41f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[3] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[4] = KeyPosRot(0.0f, 0.0f, 0.0f, -1.13f, 0.47f, -1.16f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[5] = KeyPosRot(0.0f, 0.0f, 0.0f, 0.0f, 1.38f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[6] = KeyPosRot(0.0f, 0.0f, 0.0f, 1.41f, 0.72f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[7] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.97f, 0.0f, 0.0f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[8] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.38f, 0.28f, 0.31f);
	g_player.aMotionInfo[MOTIONTYPE_ATTACK].aKeyInfo[3].aKey[9] = KeyPosRot(0.0f, 0.0f, 0.0f, -0.66f, 0.0f, 0.0f);

	g_player.motionType = MOTIONTYPE_ATTACK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		//���b�V���̔j��
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		//�}�e���A���̔j��
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	GAMEPAD *pPad = GetGamePad();

	/* ���f���̈ړ�
	if (GetkeyboardPress(DIK_UP) == true)
	{
	if (GetkeyboardPress(DIK_RIGHT) == true) MovePlayer(45.0f, PLAYER_MOVESPEED);			// �E�O
	else if (GetkeyboardPress(DIK_LEFT) == true) MovePlayer(-45.0f, PLAYER_MOVESPEED);		// ���O
	else MovePlayer(0.0f, PLAYER_MOVESPEED);												// �O
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	}
	else if (GetkeyboardPress(DIK_DOWN) == true)
	{
	if (GetkeyboardPress(DIK_RIGHT) == true) MovePlayer(135.0f, PLAYER_MOVESPEED);			// �E���
	else if (GetkeyboardPress(DIK_LEFT) == true) MovePlayer(-135.0f, PLAYER_MOVESPEED);		// �����
	else MovePlayer(-180.0f, PLAYER_MOVESPEED);												// ���
	}
	else if (GetkeyboardPress(DIK_LEFT) == true) MovePlayer(-90.0f, PLAYER_MOVESPEED);			// ��
	else if (GetkeyboardPress(DIK_RIGHT) == true) MovePlayer(90.0f, PLAYER_MOVESPEED);			// �E
	*/

	/* �v���C���[�̐U����������炩�ɂ��� */
	PlayerSmoothTurn();

	//M�L�[�Ń��[�V�����J�n
	if (GetkeyboardTrigger(DIK_M) == true || pPad->bA == true || pPad->bB == true || pPad->bX == true || pPad->bY == true || pPad->bStart)
	{
		g_bMotionStart = true;

		pPad->bA = false;
		pPad->bStart = false;
	}

	/* ���[�V�����Đ� */
	PlayMotion(g_player.bMotionStart);

	//�L�����̉�]���Z�b�g
	if (GetkeyboardTrigger(DIK_N) == true)
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			g_player.aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		g_bMotionStart = false;
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// �f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans;												// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;														// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;															// �}�e���A���f�[�^�ւ̃|�C���^

																				//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�v���C���[�̌������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu���f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//�v���C���[�̃��[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

												//�e�p�[�c�̃��[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f���p�[�c�̕`��
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

//-----------------------------------------------------------------------------
// �v���C���[�̏����擾
//-----------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;
}

/* ���f�����ړ�������֐� */
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// �J�����̏��擾

	g_player.pos.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_player.pos.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_player.rotDest.y = pCamera->rot.y + D3DXToRadian(fMoveAngleDegree) + D3DX_PI;
}

/* X�t�@�C�����烂�f����ǂݍ��ފ֐�*/
void LoadXFile(const char* cXFileName, int nCountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

												//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		cXFileName,										// �ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,								// �Œ�
		pDevice,										// �f�o�C�X
		NULL,											// NULL�Œ�
		&g_player.aModel[nCountModel].pBuffMatModel,		// �}�e���A��
		NULL,											// NULL�Œ�
		&g_player.aModel[nCountModel].nNumMatModel,		// �}�e���A����
		&g_player.aModel[nCountModel].pMeshModel);		// ���b�V��
}

/* �L�[��Pos,Rot���ȈՓI�ɓ��͂�����֐�*/
KEY KeyPosRot(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	KEY key;

	key.fPosX = posX;
	key.fPosY = posY;
	key.fPosZ = posZ;

	key.fRotX = rotX;
	key.fRotY = rotY;
	key.fRotZ = rotZ;

	return key;
}

/* �L�����̉�]�����炩�ɂ���֐� */
void PlayerSmoothTurn(void)
{
	D3DXVECTOR3 RotDiff;

	//�����v�Z
	RotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//������D3DX_PI�ȏ�(�����ȏ�)�̏ꍇ�A�t��]
	if (RotDiff.y > D3DX_PI)
	{
		g_player.rot.y -= ((D3DX_PI * 2) - RotDiff.y) * PLAYER_SMOOTHTURN_SPEED;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		g_player.rot.y += ((D3DX_PI * 2) + RotDiff.y) * PLAYER_SMOOTHTURN_SPEED;
	}
	else
	{
		g_player.rot.y += RotDiff.y * PLAYER_SMOOTHTURN_SPEED;
	}

	// ��]�̏C�� (3.14��������}�t��)
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_player.rotDest.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
}

/* ���[�V�����̍Đ��֐� */
void PlayMotion(bool bPlayMotion)
{
	if (bPlayMotion == true)
	{
		//���[�v
		g_player.bLoopMotion = g_player.aMotionInfo[g_player.motionType].bLoop;

		//���[�V�����J�E���g�A�b�v
		g_player.nCounterMotion++;

		//���f��������
		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			//�����v�Z�p
			KEY keyDiff[20];

			//���݂̃L�[�Ǝ��̃L�[�Ƃ̍������v�Z
			if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey - 1 && g_player.bLoopMotion == true)
			{	// ���[�v�̏ꍇ
				keyDiff[nCntModel].fPosX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fPosX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosX;
				keyDiff[nCntModel].fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fPosY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosY;
				keyDiff[nCntModel].fPosZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosZ;
				keyDiff[nCntModel].fRotX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fRotX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotX;
				keyDiff[nCntModel].fRotY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fRotY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotY;
				keyDiff[nCntModel].fRotZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotZ;
			}
			else
			{	// ����ȊO
				keyDiff[nCntModel].fPosX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fPosX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosX;
				keyDiff[nCntModel].fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fPosY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosY;
				keyDiff[nCntModel].fPosZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fPosZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosZ;
				keyDiff[nCntModel].fRotX = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fRotX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotX;
				keyDiff[nCntModel].fRotY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fRotY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotY;
				keyDiff[nCntModel].fRotZ = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey + 1].aKey[nCntModel].fRotZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotZ;
			}

			//���݂̃L�[�ɍ��������[�V�����J�E���g�Ŋ��������𑫂������̂�rot�ɑ��
			//g_player.aModel[nCntModel].pos.x = g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosX + keyDiff[nCntModel].fPosX * (g_player.nCounterMotion / g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].nFrame);
			//g_player.aModel[nCntModel].pos.y = g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosY + keyDiff[nCntModel].fPosY * (g_player.nCounterMotion / g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].nFrame);
			//g_player.aModel[nCntModel].pos.z = g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].aKey[nCntModel].fPosZ + keyDiff[nCntModel].fPosX * (g_player.nCounterMotion / g_player.aMotionInfo[0].aKeyInfo[g_player.nKey].nFrame);
			g_player.aModel[nCntModel].rot.x = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotX + keyDiff[nCntModel].fRotX * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame);
			g_player.aModel[nCntModel].rot.y = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotY + keyDiff[nCntModel].fRotY * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame);
			g_player.aModel[nCntModel].rot.z = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntModel].fRotZ + keyDiff[nCntModel].fRotZ * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame);
		}

		//���݃L�[�̍Đ��t���[�����ɓ��B������
		if (g_player.nCounterMotion >= g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame)
		{
			//���̃L�[��
			g_player.nKey++;

			//���[�V�����J�E���^���Z�b�g
			g_player.nCounterMotion = 0;
		}

		//���݃L�[�����[�V�����̃L�[���ɓ��B������
		if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey - 1 && g_player.bLoopMotion == false)
		{//���[�v���Ȃ��ꍇ

		 //���[�V������Ԃ��I���
			g_player.bMotionStart = false;

			//���[�V�����J�E���^���Z�b�g
			g_player.nCounterMotion = 0;

			//���݃L�[��������
			g_player.nKey = 0;

			for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
			{
				g_player.aModel[nCntModel].rot.x = g_player.aMotionInfo[0].aKeyInfo[0].aKey[nCntModel].fRotX;
				g_player.aModel[nCntModel].rot.y = g_player.aMotionInfo[0].aKeyInfo[0].aKey[nCntModel].fRotY;
				g_player.aModel[nCntModel].rot.z = g_player.aMotionInfo[0].aKeyInfo[0].aKey[nCntModel].fRotZ;
			}
		}
		else if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey && g_player.bLoopMotion == true)
		{//���[�v�̏ꍇ

		 //���[�V�����J�E���^���Z�b�g
			g_player.nCounterMotion = 0;

			//���݃L�[��������
			g_player.nKey = 0;
		}
	}
}