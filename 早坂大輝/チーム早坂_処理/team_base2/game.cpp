//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author:Taiki Hayasaka, Sota Tomoe
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "enemy.h"
#include "portal.h"
#include "collision.h"
#include "skybox.h"
#include "object.h"
#include "commandaction.h"
#include "score.h"
#include "pause.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
Stage g_stage;
int g_nCntFrame;
bool g_bPause = false;		//�|�[�Y�����ǂ���

//=============================================================================
// �Q�[����ʂ̏���������
//=============================================================================
HRESULT InitGame(void)
{
	//���f���̏���������
	InitPlayer();

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�|�[�^���̏���������
	InitPortal();
	
	//�R�}���h�A�N�V��������������
	InitCommand();

	//---�X�e�[�W�Ɉ˂����----

	//�G�̏���������
	InitEnemy();

	//�I�u�W�F�N�g�̏���������
	InitObject();

	//���b�V���t�B�[���h�̏���������
	InitMeshfield(g_stage.nStageNum);

	//��(���b�V��)�̏���������
	InitMeshwall();

	//�ǂ̔z�u
	SetWall();
	
	//�X�J�C�{�b�N�X�̏���
	InitSky();

	//�X�R�A�̏���
	InitScore();

	//�|�[�Y�̏���������
	InitPause();
	
	//-----------------------

	//�R���W���������̏�����
	InitCollision();

	//���[�V�����̏���������
	InitMotion();

	return S_OK;
}

//=============================================================================
// �Q�[����ʂ̏I������
//=============================================================================
void UninitGame(void)
{
	//�X�J�C�{�b�N�X�̏I������
	UninitSky();

	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	//�G�̏I������
	UninitEnemy();

	//�I�u�W�F�N�g�̏I������
	UninitObject();

	//��(���b�V��)�̏I������
	UninitMeshwall();

	//�R�}���h�A�N�V�����I������
	UninitCommand();

	//���f���̏I������
	UninitPlayer();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�R���W�����I������	
	UninitCollision();

	//�|�[�^���̏I������
	UninitPortal();

	//�X�R�A�̏I������
	UninitScore();

	//�|�[�Y�̏I������
	UninitPause();
}

//=============================================================================
// �Q�[����ʂ̍X�V����
//=============================================================================
void UpdateGame(void)
{
	g_nCntFrame++;
	CommandAction *pCmd = GetCAction();

	//�|�[�Y
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		//���ʉ�


		g_bPause = g_bPause ? false : true;	//1�sVer.
	}

	if (g_bPause == true)
	{
		//�|�[�Y�̍X�V����
		UpdatePause();
	}

	if (g_bPause == false)
	{

		if (pCmd->bActive == true)
		{
			if (g_nCntFrame % 4 == 0)
			{
				//�R���W�����̍X�V����
				UpdateCollision();

				//���b�V���t�B�[���h�̍X�V����
				UpdateMeshfield();

				//��(���b�V��)�̍X�V����
				UpdateMeshwall();

				//���[�V�����̍X�V����
				UpdateMotion();

				//���f���̍X�V����
				UpdatePlayer();

				//�G�̍X�V����
				UpdateEnemy();

				//�I�u�W�F�N�g�̍X�V����
				UpdateObject();

				//�J�����̍X�V����
				UpdateCamera();

				//���C�g�̍X�V����
				UpdateLight();

				//�|�[�^���̍X�V����
				UpdatePortal();

				//�X�J�C�{�b�N�X�̍X�V����
				UpdateSky();

				//�X�R�A�̍X�V����
				UpdateScore();

				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					g_stage.nStageNum += 1;
					SetFade(FADE_OUT, MODE_GAME);
				}
			}
			//�R�}���h�A�N�V�����̍X�V����
			UpdateCommand();
		}
		else
		{
			//�R���W�����̍X�V����
			UpdateCollision();

			//���b�V���t�B�[���h�̍X�V����
			UpdateMeshfield();

			//��(���b�V��)�̍X�V����
			UpdateMeshwall();

			//���f���̍X�V����
			UpdatePlayer();

			//�G�̍X�V����
			UpdateEnemy();

			//�I�u�W�F�N�g�̍X�V����
			UpdateObject();

			//�J�����̍X�V����
			UpdateCamera();

			//���[�V�����̍X�V����
			UpdateMotion();

			//���C�g�̍X�V����
			UpdateLight();

			//�|�[�^���̍X�V����
			UpdatePortal();

			//�X�J�C�{�b�N�X�̍X�V����
			UpdateSky();

			//�R�}���h�A�N�V�����̍X�V����
			UpdateCommand();

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				g_stage.nStageNum += 1;
				SetFade(FADE_OUT, MODE_GAME);
			}
		}
	}
}

//=============================================================================
// �Q�[����ʂ̕`�揈��
//=============================================================================
void DrawGame(void)
{
		//�R���W�����̕`�揈��
		DrawCollision();

		//���b�V���t�B�[���h�̕`�揈��
		DrawMeshfield();

		//��(���b�V��)�̕`�揈��
		DrawMeshwall();

		//���f���̕`�揈��
		DrawPlayer();

		//�G�̕`�揈��
		DrawEnemy();

		//�I�u�W�F�N�g�̕`�揈��
		DrawObject();

		//�X�J�C�{�b�N�X�̕`��
		DrawSky();

		//�|�[�^���̕`�揈��
		DrawPortal();

		//�R�}���h�A�N�V�����`�揈��
		DrawCommand();

		//�X�R�A�̕`�揈��
		DrawScore();

		//�|�[�Y�̕`�揈��
		if (g_bPause == true)
		{
			DrawPause();
		}
}

//=============================================================================
// �X�e�[�W�ԍ����擾
//=============================================================================
Stage *GetStage(void)
{
	return &g_stage;
}

//=============================================================================
// �ǂ̔z�u
//=============================================================================
void SetWall(void)
{
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 700.0f, 50.0f);
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 700.0f, 50.0f);
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), 700.0f, 50.0f);
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 700.0f, 50.0f);
}

//=============================================================================
// �|�[�Y�̐ݒ�
//=============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}