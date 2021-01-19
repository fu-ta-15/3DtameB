//-----------------------------------------------------------------------------
//
// �Q�[���̏��� [game.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "game.h"
#include "fade.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
#include "meshfield.h"
#include "bullet.h"
#include "wall.h"
#include "billboard.h"
#include "shadow.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �Q�[���̏���������
//-----------------------------------------------------------------------------
HRESULT InitGame(void)
{
	//���C�g�̏���������
	InitLight();

	//�J�����̏���������
	InitCamera();

	//���f���̏���������
	//InitModel();

	//�v���C���[�̏���������
	InitPlayer();

	//�|���S���̏���������
	//InitPolygon();

	//�n�ʂ̏���������
	InitMeshfield();

	//�e�̏���������
	InitBullet();

	//�ǂ̏���������
	InitWall();

	//�r���{�[�h�̏���������
	InitBillboard();

	//�e�̏���������
	InitShadow();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �Q�[���̏I������
//-----------------------------------------------------------------------------
void UninitGame(void)
{
	//�e�̏I������
	UninitShadow();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//�ǂ̏I������
	UninitWall();

	//�e�̏I������
	UninitBullet();

	//�n�ʂ̏I������
	UninitMeshfield();

	//�|���S���̏I������
	//UninitPolygon();

	//�v���C���[�̏I������
	UninitPlayer();

	//���f���̏I������
	//UninitModel();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();
}

//-----------------------------------------------------------------------------
// �Q�[���̍X�V����
//-----------------------------------------------------------------------------
void UpdateGame(void)
{
	//���C�g�̍X�V����
	UpdateLight();

	//�J�����̍X�V����
	UpdateCamera();

	//���f���̍X�V����
	//UpdateModel();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�|���S���̍X�V����
	//UpdatePolygon();

	//�n�ʂ̍X�V����
	UpdateMeshfield();

	//�e�̍X�V����
	UpdateBullet();

	//�ǂ̍X�V����
	UpdateWall();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	//�e�̍X�V����
	UpdateShadow();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//-----------------------------------------------------------------------------
// �Q�[���̕`�揈��
//-----------------------------------------------------------------------------
void DrawGame(void)
{
	//�J�����̐ݒ�
	SetCamera();

	//���f���̕`�揈��
	//DrawModel();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�|���S���̕`�揈��
	//DrawPolygon();

	//�n�ʂ̕`�揈��
	DrawMeshfield();

	//�e�̕`�揈��
	DrawBullet();

	//�ǂ̕`�揈��
	DrawWall();

	//�r���{�[�h�̕`�揈��
	DrawBillboard();

	//�e�̕`�揈��
	DrawShadow();
}

//-----------------------------------------------------------------------------
// �|�[�Y�Z�b�g
//-----------------------------------------------------------------------------
void SetPause(bool bPause)
{

}