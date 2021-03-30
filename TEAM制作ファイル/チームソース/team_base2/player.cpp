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
#include "meshfield.h"
#include "fade.h"
#include "result.h"
#include "motion.h"
#include "enemy.h"
#include "commandaction.h"
#include "bullet.h"
#include "Dinput.h"

#include <stdio.h>
#include <time.h>

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PLAYER_SMOOTHTURN_SPEED (0.1f)											// ���炩�ɐU��������x
#define PLAYER_SMOOTHTURN_SPEED_ATK (0.02f)

#define READROW (1028)	// �t�@�C���ǂݍ��݂œǂލő吔

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed);
HRESULT LoadXFile(const char* cXFileName, Model *modelInfo);
void PlayerSmoothTurn(void);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Player g_player;																		// �v���C���[�̏��
KEY g_playerDefaultKey[PLAYER_MODEL_AMOUNT];
CharacterPartsInfo g_ModelInfo;															// �ǂݍ��񂾃��f���̏��

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//�v���C���[�̏����ݒ�
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�̏����ݒ�
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����̏����ݒ�
	g_player.bHit = false;
	g_player.bInvincible = false;
	g_player.dwTime = NULL;
	g_player.nLife = PLAYER_HEALTH;
	g_player.nLifeMax = PLAYER_HEALTH;

	//�e�L�X�g�ǂݍ���
	ReadCharacterInfo(&g_ModelInfo, "data\\TXT\\motion_team_model1.txt");

	//�ǂݍ��񂾏����g����X�t�@�C���ǂݍ���
	for (int nCntModel = 0; nCntModel < g_ModelInfo.nModelNum; nCntModel++)
	{
		LoadXFile(&g_ModelInfo.cModelFileName[nCntModel][0], &g_player.aModel[nCntModel]);
	}

	//���f���̃p�[�c��
	g_player.nNumModel = g_ModelInfo.nModelNum;

	//�e�p�[�c�̊K�w�\���ݒ�
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		g_player.aModel[nCntModel].nIdxModelParent = g_ModelInfo.nModelParent[nCntModel];
		g_player.aModel[nCntModel].pos = D3DXVECTOR3(g_ModelInfo.fModelPos[nCntModel][0], g_ModelInfo.fModelPos[nCntModel][1], g_ModelInfo.fModelPos[nCntModel][2]);
		g_player.aModel[nCntModel].rot = D3DXVECTOR3(g_ModelInfo.fModelRot[nCntModel][0], g_ModelInfo.fModelRot[nCntModel][1], g_ModelInfo.fModelRot[nCntModel][2]);
	}

	//�����L�[
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		g_playerDefaultKey[nCnt] = KeyPosRot(g_player.aModel[nCnt].pos.x, g_player.aModel[nCnt].pos.y, g_player.aModel[nCnt].pos.z, 0, 0, 0);
	}

	LoadXFile("data//MODEL//naginata_fix.x", &g_player.AltWeapon);

	g_player.weaponPos = D3DXVECTOR3(-1.0f, -0.5f, 0.0f);
	g_player.weaponRot = D3DXVECTOR3(0.0f, 1.5f, -1.6f);

	g_player.posWeaponCol[0] = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_player.posWeaponCol[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_player.posWeaponCol[2] = D3DXVECTOR3(0.0f, 45.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < PLAYER_MODEL_AMOUNT; nCntModel++)
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
	DWORD dwCurrentTime = timeGetTime();	// ���ݎ���
	DIJOYSTATE2 *pController = pGetPadCont();

	//�ʒu�ۑ�
	g_player.posOld = g_player.pos;

	//�ړ��ʒǉ�
	g_player.pos += g_player.move;

	//�ړ��ʌ���
	g_player.move.x += (0 - g_player.move.x) * 0.2f;
	g_player.move.z += (0 - g_player.move.z) * 0.2f;

	//�d��
	g_player.move.y -= 0.2f;

	//�ړ�����
	//if (g_player.pos.x > FIELD_MAXSIZE) g_player.pos.x = FIELD_MAXSIZE;
	//if (g_player.pos.x < -FIELD_MAXSIZE) g_player.pos.x = -FIELD_MAXSIZE;
	//if (g_player.pos.z > FIELD_MAXSIZE) g_player.pos.z = FIELD_MAXSIZE;
	//if (g_player.pos.z < -FIELD_MAXSIZE) g_player.pos.z = -FIELD_MAXSIZE;
	if (g_player.pos.y <= 0.0f)
	{
		g_player.move.y = 0.0f;
		g_player.pos.y = 0.0f;
	}

	/* ���f���̈ړ� */
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_D) == true) MovePlayer(D3DXToRadian(45.0f), PLAYER_MOVESPEED);			// �E�O
		else if (GetKeyboardPress(DIK_A) == true) MovePlayer(D3DXToRadian (-45.0f), PLAYER_MOVESPEED);		// ���O
		else MovePlayer(0.0f, PLAYER_MOVESPEED);												// �O
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_D) == true) MovePlayer(D3DXToRadian(135.0f), PLAYER_MOVESPEED);			// �E���
		else if (GetKeyboardPress(DIK_A) == true) MovePlayer(D3DXToRadian(-135.0f), PLAYER_MOVESPEED);		// �����
		else MovePlayer(D3DXToRadian(-180.0f), PLAYER_MOVESPEED);												// ���
	}
	else if (GetKeyboardPress(DIK_A) == true) MovePlayer(D3DXToRadian(-90.0f), PLAYER_MOVESPEED);			// ��
	else if (GetKeyboardPress(DIK_D) == true) MovePlayer(D3DXToRadian(90.0f), PLAYER_MOVESPEED);			// �E

	/* �v���C���[�̐U����������炩�ɂ��� */
	PlayerSmoothTurn();

	//�s���Ƀ��[�V��������
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	if (g_player.weapon == PWEAPON_KATANA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_KATANA_ATTACK, NULL);
	//	else if (g_player.weapon == PWEAPON_NAGINATA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NAGINATA_ATTACK, NULL);
	//}
	//else if (GetKeyboardPress(DIK_W) ||
	//	GetKeyboardPress(DIK_S) ||
	//	GetKeyboardPress(DIK_A) ||
	//	GetKeyboardPress(DIK_D) == true)
	//{
	//	StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_WALK, NULL);
	//}
	//else
	//{
	//	StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NEUTRAL, NULL);
	//}

	if (pController->lX != 0 || pController->lY != 0)
	{//	�X�e�B�b�N���X������
		float fAngle = atan2f((float)pController->lX, -(float)pController->lY);
		MovePlayer(fAngle, PLAYER_MOVESPEED);

		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_WALK, NULL);
	}
	else
	{
		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NEUTRAL, NULL);
	}
	if (GetKeypadTrigger(D_BUUTON_A))
	{
		if (g_player.weapon == PWEAPON_KATANA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_KATANA_ATTACK, NULL);
		else if (g_player.weapon == PWEAPON_NAGINATA) StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_CYBORG_NAGINATA_ATTACK, NULL);
	}


	//�U�����͈ړ��O�ɂ���
	if (g_player.motionType == MOTIONTYPE_CYBORG_KATANA_ATTACK ||
		g_player.motionType == MOTIONTYPE_CYBORG_NAGINATA_ATTACK)
	{
		g_player.move = D3DXVECTOR3(0, 0, 0);
	}

	//���Ԍo�߂Ŗ��G���ԉ���
	if (dwCurrentTime - g_player.dwTime >= PLAYER_INVINCIBLE_TIME)
	{
		//���G����
		g_player.bInvincible = false;
	}


	if (GetKeyboardTrigger(DIK_H) == true)
	{
		if (g_player.weapon == PWEAPON_KATANA) g_player.weapon = PWEAPON_NAGINATA;
		else if (g_player.weapon == PWEAPON_NAGINATA) g_player.weapon = PWEAPON_KATANA;
	}
	if (GetKeypadTrigger(D_BUUTON_RB))
	{
		if (g_player.weapon == PWEAPON_KATANA) g_player.weapon = PWEAPON_NAGINATA;
		else if (g_player.weapon == PWEAPON_NAGINATA) g_player.weapon = PWEAPON_KATANA;
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

	//���f���p�[�c
	for (int nCntModel = 0; nCntModel < g_player.nNumModel - 1; nCntModel++)
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

		//���G��Ԃ����ă��f���̐F��ς���
		if (g_player.bInvincible == true)
		{//���G���
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				D3DXMATERIAL matDef[20];

				matDef[nCntMat] = pMat[nCntMat];

				pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);

				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f���p�[�c�̕`��
				g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);

				pMat[nCntMat] = matDef[nCntMat];
			}
		}
		else if (g_player.bInvincible == false)
		{//�ʏ���
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				//pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);

				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f���p�[�c�̕`��
				g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//����p�[�c
	D3DXMATRIX mtxRotWpn, mtxTransWpn;	// �v�Z�p
	D3DXMATRIX mtxParentWpn;			// �e�̃}�g���N�X

	if (g_player.weapon == PWEAPON_KATANA)
	{
		//�e�p�[�c�̃��[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxRotWpn);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxTransWpn);

		//�e�}�g���N�X�ݒ�
		mtxParentWpn = g_player.aModel[g_player.aModel[PLAYER_MODEL_AMOUNT - 1].nIdxModelParent].mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxParentWpn);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pBuffMatModel->GetBufferPointer();

		//�}�e���A���ݒ�ƕ`��
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[PLAYER_MODEL_AMOUNT - 1].nNumMatModel; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f���p�[�c�̕`��
			g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pMeshModel->DrawSubset(nCntMat);
		}
	}
	else if (g_player.weapon == PWEAPON_NAGINATA)
	{
		//�e�p�[�c�̃��[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxRotWpn);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransWpn, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.x, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.y, g_player.aModel[PLAYER_MODEL_AMOUNT - 1].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxTransWpn);

		//�e�}�g���N�X�ݒ�
		mtxParentWpn = g_player.aModel[g_player.aModel[PLAYER_MODEL_AMOUNT - 1].nIdxModelParent].mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld, &mtxParentWpn);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.AltWeapon.pBuffMatModel->GetBufferPointer();

		//�}�e���A���ݒ�ƕ`��
		for (int nCntMat = 0; nCntMat < (int)g_player.AltWeapon.nNumMatModel; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f���p�[�c�̕`��
			g_player.AltWeapon.pMeshModel->DrawSubset(nCntMat);
		}
	}


	//test
	for (int nCntCol = 0; nCntCol < PLAYER_WEAPON_COLLISION_COMPONENTS; nCntCol++)
	{
		//����p�[�c
		D3DXMATRIX mtxRotWpnC, mtxTransWpnC;	// �v�Z�p
		D3DXMATRIX mtxParentWpnC;			// �e�̃}�g���N�X

		//�e�p�[�c�̃��[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&g_player.mtxWeaponCol[nCntCol]);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransWpnC, g_player.posWeaponCol[nCntCol].x, g_player.posWeaponCol[nCntCol].y, g_player.posWeaponCol[nCntCol].z);
		D3DXMatrixMultiply(&g_player.mtxWeaponCol[nCntCol], &g_player.mtxWeaponCol[nCntCol], &mtxTransWpnC);

		//�e�}�g���N�X�ݒ�
		mtxParentWpnC = g_player.aModel[PLAYER_MODEL_AMOUNT - 1].mtxWorld;

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.mtxWeaponCol[nCntCol], &g_player.mtxWeaponCol[nCntCol], &mtxParentWpnC);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWeaponCol[nCntCol]);
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
//-----------------------------------------------------------------------------
// ���f���̏�����Ԃ��擾
//-----------------------------------------------------------------------------
KEY *GetDefKey(void)
{
	return &g_playerDefaultKey[0];
}

/* ���f�����ړ�������֐� */
void MovePlayer(float fMoveRad, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// �J�����̏��擾

	g_player.move.x += sinf(pCamera->rot.y + fMoveRad) * fMoveSpeed;
	g_player.move.z += cosf(pCamera->rot.y + fMoveRad) * fMoveSpeed;
	g_player.rotDest.y = pCamera->rot.y + fMoveRad + D3DX_PI;
}

/* X�t�@�C�����烂�f����ǂݍ��ފ֐�*/
HRESULT LoadXFile(const char* cXFileName, Model *modelInfo)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾
	HRESULT hres;

	//X�t�@�C���̓ǂݍ���
	hres = D3DXLoadMeshFromX(
		cXFileName,										// �ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,								// �Œ�
		pDevice,										// �f�o�C�X
		NULL,											// NULL�Œ�
		&modelInfo->pBuffMatModel,						// �}�e���A��
		NULL,											// NULL�Œ�
		&modelInfo->nNumMatModel,						// �}�e���A����
		&modelInfo->pMeshModel);						// ���b�V��
	return hres;
}

/* �L�����̉�]�����炩�ɂ���֐� */
void PlayerSmoothTurn(void)
{
	D3DXVECTOR3 RotDiff;
	float fTurnSpeed;

	if (g_player.motionType == MOTIONTYPE_ATTACK) fTurnSpeed = PLAYER_SMOOTHTURN_SPEED_ATK;
	else if (g_player.motionType == MOTIONTYPE_CYBORG_KATANA_ATTACK) fTurnSpeed = PLAYER_SMOOTHTURN_SPEED_ATK;
	else if (g_player.motionType == MOTIONTYPE_CYBORG_NAGINATA_ATTACK) fTurnSpeed = PLAYER_SMOOTHTURN_SPEED_ATK;
	else fTurnSpeed = PLAYER_SMOOTHTURN_SPEED;

	//�����v�Z
	RotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//������D3DX_PI�ȏ�(�����ȏ�)�̏ꍇ�A�t��]
	if (RotDiff.y > D3DX_PI)
	{
		g_player.rot.y -= ((D3DX_PI * 2) - RotDiff.y) * fTurnSpeed;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		g_player.rot.y += ((D3DX_PI * 2) + RotDiff.y) * fTurnSpeed;
	}
	else
	{
		g_player.rot.y += RotDiff.y * fTurnSpeed;
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

/* �L�����N�^�[�̃��f������ǂݍ��ފ֐� */
void ReadCharacterInfo(CharacterPartsInfo *characterInfo, char* fileName)
{
	FILE *pFile;
	char cCharRead[READROW][128];
	char cEqual[2];

	int nCountModelNum = 0;
	int nCountModelIdx = 0;
	int nCountModelParent = 0;
	int nCountModelPos = 0;
	int nCountModelRot = 0;

	pFile = fopen(fileName, "r");
	if (pFile != NULL)
	{
		//1028�s�T��
		for (int nCntRow = 0; nCntRow < READROW; nCntRow++)
		{
			//������ǂݍ���
			fscanf(pFile, "%s", &cCharRead[nCntRow][0]);

			//SCRIPT�̕��������������
			if (strcmp(&cCharRead[nCntRow][0], "SCRIPT") == 0)
			{
				for (int nCntRow = 0; nCntRow < READROW; nCntRow++)
				{
					//���̕�����ǂݍ���
					fscanf(pFile, "%s", &cCharRead[nCntRow][0]);

					if (strcmp(&cCharRead[nCntRow][0], "NUM_MODEL") == 0)
					{
						//���̕�����
						fscanf(pFile, "%s", &cEqual[0]);

						//�C�R�[������������
						if (strcmp(&cEqual[0], "=") == 0)
						{
							//�C�R�[���̎��̐�����ϐ��ɓ����
							fscanf(pFile, "%d", &characterInfo->nModelNum);
						}
					}

					if (strcmp(&cCharRead[nCntRow][0], "MODEL_FILENAME") == 0)
					{
						//���̕�����
						fscanf(pFile, "%s", &cEqual[0]);

						//�C�R�[����������
						if (strcmp(&cEqual[0], "=") == 0)
						{
							//�C�R�[���̎��̕������z��ɓ����
							fscanf(pFile, "%s", &characterInfo->cModelFileName[nCountModelNum][0]);

							//�J�E���g�A�b�v
							nCountModelNum++;
						}
					}

					if (strcmp(&cCharRead[nCntRow][0], "CHARACTERSET") == 0)
					{
						for (int nCntCSET = 0; nCntCSET < READROW; nCntCSET++)
						{
							fscanf(pFile, "%s", &cCharRead[nCntCSET][0]);

							//PARTSSET������
							if (strcmp(&cCharRead[nCntCSET][0], "PARTSSET") == 0)
							{
								for (int nCntPSET = 0; nCntCSET < READROW; nCntCSET++)
								{
									fscanf(pFile, "%s", &cCharRead[nCntCSET][0]);

									//INDEX
									if (strcmp(&cCharRead[nCntCSET][0], "INDEX") == 0)
									{
										//���̕�����
										fscanf(pFile, "%s", &cEqual[0]);

										//�C�R�[����������
										if (strcmp(&cEqual[0], "=") == 0)
										{
											fscanf(pFile, "%d", &characterInfo->nModelIdx[nCountModelIdx]);

											nCountModelIdx++;
										}
									}

									//PARENT
									if (strcmp(&cCharRead[nCntCSET][0], "PARENT") == 0)
									{
										//���̕�����
										fscanf(pFile, "%s", &cEqual[0]);

										//�C�R�[����������
										if (strcmp(&cEqual[0], "=") == 0)
										{
											fscanf(pFile, "%d", &characterInfo->nModelParent[nCountModelParent]);

											nCountModelParent++;
										}
									}

									//POS
									if (strcmp(&cCharRead[nCntCSET][0], "POS") == 0)
									{
										//���̕�����
										fscanf(pFile, "%s", &cEqual[0]);

										//�C�R�[����������
										if (strcmp(&cEqual[0], "=") == 0)
										{
											for (int nCntVector3 = 0; nCntVector3 < 3; nCntVector3++)
											{
												fscanf(pFile, "%f", &characterInfo->fModelPos[nCountModelPos][nCntVector3]);
											}
											nCountModelPos++;
										}
									}

									//ROT
									if (strcmp(&cCharRead[nCntCSET][0], "ROT") == 0)
									{
										//���̕�����
										fscanf(pFile, "%s", &cEqual[0]);

										//�C�R�[����������
										if (strcmp(&cEqual[0], "=") == 0)
										{
											for (int nCntVector3 = 0; nCntVector3 < 3; nCntVector3++)
											{
												fscanf(pFile, "%f", &characterInfo->fModelRot[nCountModelRot][nCntVector3]);
											}
											nCountModelRot++;
										}
									}

									//END_PARTSSET�������烋�[�v������
									if (strcmp(&cCharRead[nCntCSET][0], "END_PARTSSET") == 0)
									{
										break;
									}
								}
							}

							//END_CHARACTERSET�������烋�[�v������
							if (strcmp(&cCharRead[nCntCSET][0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}
					}
				}
				break;
			}
		}
	}
}