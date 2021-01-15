//===================================================================
//
// �J�����̏����@[camera.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "Player.h"

//=================================================================================================
//�}�N����`
//=================================================================================================
#define MAX_POINT (150.0f)			//�J�����̈ʒu

//=================================================================================================
//�O���[�o���ϐ�
//=================================================================================================
Camera g_camera;					//�J�����̏��

//=================================================================================================
//����������
//=================================================================================================
void InitCamera(void)
{
	//�J�����̏�����
	g_camera.posV = D3DXVECTOR3(0.0f, MAX_POINT, - MAX_POINT);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================================================================================================
//�I������
//=================================================================================================
void UninitCamera(void)
{

}

//=================================================================================================
//�X�V����
//=================================================================================================
void UpdateCamera(void)
{
	//���f���̎擾
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	//�J�����̒Ǐ]
	g_camera.posR = pPlayer->pos;

	g_camera.posV.x = g_camera.posR.x;
	g_camera.posV.z = g_camera.posR.z - 200.0f;
	g_camera.posV.y = g_camera.posR.y + 200.0f;

	//�J�����̏㉺���E�ړ�
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posV.x += sinf (g_camera.rot.y) * 1;
		g_camera.posR.z += cosf (g_camera.rot.y) * 1;
		g_camera.posR.x += sinf (g_camera.rot.y) * 1;
		g_camera.posV.z += cosf (g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posV.x -= sinf (g_camera.rot.y) * 1;
		g_camera.posR.z -= cosf (g_camera.rot.y) * 1;
		g_camera.posR.x -= sinf (g_camera.rot.y) * 1;
		g_camera.posV.z -= cosf (g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posV.x -= cosf (g_camera.rot.y) * 1;
		g_camera.posV.z -= sinf (g_camera.rot.y) * 1;
		g_camera.posR.x -= cosf (g_camera.rot.y) * 1;
		g_camera.posR.z -= sinf (g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posV.x += cosf(g_camera.rot.y) * 1;
		g_camera.posV.z += sinf(g_camera.rot.y) * 1;
		g_camera.posR.x += cosf(g_camera.rot.y) * 1;
		g_camera.posR.z += sinf(g_camera.rot.y) * 1;
	}

	//�J�����̒����_�̉�]
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y -= 0.06f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * MAX_POINT;
	}

	//�J�����̋t��]
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y += 0.06f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * MAX_POINT;
	}

	//�J�����̎��_�̉�]
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.y += 0.06f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * MAX_POINT;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= 0.06f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * MAX_POINT;
	}

	//�����_����
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.posR.z += cosf(g_camera.rot.y) * 1;
		g_camera.posV.z += sinf(g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.posR.z -= cosf(g_camera.rot.y) * 1;
		g_camera.posV.z -= sinf(g_camera.rot.y) * 1;
	}

	//���_����
	if (GetKeyboardPress(DIK_Y) == true)
	{

	}

	//������]
	/*g_camera.rot.y -= 0.007f;

	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * MAX_POINT;
	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * MAX_POINT;*/
}

//=================================================================================================
//�ݒ菈��
//=================================================================================================
void SetCamera(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMatrixIdentity(&g_camera.mtxPlojection);

	//�v���W�F�N�V�������쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxPlojection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxPlojection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxPlojection);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxPlojection, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxPlojection);
}

//=================================================================================================
//�J�����̎擾
//=================================================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}