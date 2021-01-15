//=================================================================================================================
//
// �J�����̏����@�kcamera.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
Camera g_camera;
D3DXVECTOR3 g_Difference;

//*****************************************************************************************************************
//	�J�����̏���������
//*****************************************************************************************************************
void InitCamera(void)
{
	//������
	g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -550.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̎��_
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�̒����_
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�قڂ�����Ȃ�
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�J�����̌���
}

//*****************************************************************************************************************
//	�J�����̏I������
//*****************************************************************************************************************
void UninitCamera(void)
{
}

//*****************************************************************************************************************
//	�J�����̍X�V����
//*****************************************************************************************************************
void UpdateCamera(void)
{
	Model *pModel;
	pModel = GetModel();

	g_camera.posRDest = pModel->pos;

	g_camera.posV.x = pModel->pos.x + sinf(g_camera.rot.y) * LONG;
	g_camera.posV.z = pModel->pos.z - cosf(g_camera.rot.y) * LONG;
	g_camera.posV.y = pModel->pos.y + 500.0f;

	g_Difference.x = g_camera.posRDest.x - g_camera.posR.x;
	g_Difference.z = g_camera.posRDest.z - g_camera.posR.z;

	g_camera.posR.x += g_Difference.x * 0.1f;
	g_camera.posR.z += g_Difference.z * 0.1f;

	//�J����
	ControlCamera();

}

//*****************************************************************************************************************
//	�ݒ菈��
//*****************************************************************************************************************
void SetCamera(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬(  �A��p�A�@�A��O�̈ʒu�A���̈ʒu�j
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
//*****************************************************************************************************************
//	�ݒ菈��
//*****************************************************************************************************************
void ControlCamera(void)
{
	//A�L�[�������ꂽ�Ƃ�
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posR.x = g_camera.posR.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z + cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z + cosf(g_camera.rot.y) * SPEED;
	}

	//D�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posR.x = g_camera.posR.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z - cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z - cosf(g_camera.rot.y) * SPEED;
	}

	//S�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posR.x = g_camera.posR.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z - cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z - cosf(g_camera.rot.y) * SPEED;
	}

	//W�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posR.x = g_camera.posR.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z + cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z + cosf(g_camera.rot.y) * SPEED;
	}

	//*******************************************
	// �����_ (R)
	//*******************************************

		//Q�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y += 0.01f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * LONG;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * LONG;
	}

	//E�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y -= 0.01f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * LONG;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * LONG;
	}

	//T�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.posR.z -= sinf(D3DX_PI) * SPEED;
		g_camera.posR.y += cosf(D3DX_PI) * SPEED;
	}

	//B�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.posR.z += sinf(D3DX_PI) * SPEED;
		g_camera.posR.y -= cosf(D3DX_PI) * SPEED;
	}

	//*******************************************
	// ���_(V)
	//*******************************************

		//Z�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.y += 0.01f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * LONG;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * LONG;
	}

	//C�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= 0.01f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * LONG;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * LONG;
	}

	//Y�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.posV.z += sinf(D3DX_PI) * SPEED;
		g_camera.posV.y -= cosf(D3DX_PI) * SPEED;
	}

	//N�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_camera.posV.z -= sinf(D3DX_PI) * SPEED;
		g_camera.posV.y += cosf(D3DX_PI) * SPEED;
	}

}

//*****************************************************************************************************************
//	�J����
//*****************************************************************************************************************
Camera *GetCamera(void)
{
	return &g_camera;
}