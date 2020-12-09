//-----------------------------------------------------------------------------
//
// �J�����̏��� [camera.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "camera.h"
#include "input.h"
#include "model.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define CAMERA_DISTANCE (50.0f)													// ���_�ƒ����_�܂ł̋���
#define CAMERA_SPEED (0.1f)														// �J�����̐��񑬓x

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Camera g_camera;		// �J�����̏��

//-----------------------------------------------------------------------------
// �J�����̏���������
//-----------------------------------------------------------------------------
void InitCamera(void)
{
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �J�����̌���
	g_camera.posV = D3DXVECTOR3(0.0f, 150.0f, -100.0f);				// ���_
	g_camera.posR = D3DXVECTOR3(g_camera.posV.x + sinf(g_camera.rot.x) * CAMERA_DISTANCE, 0.0f, g_camera.posV.z + cosf(g_camera.rot.z) * CAMERA_DISTANCE);					// �����_
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// ������x�N�g��
}

//-----------------------------------------------------------------------------
// �J�����̏I������
//-----------------------------------------------------------------------------
void UninitCamera(void)
{

}

//-----------------------------------------------------------------------------
// �J�����̍X�V����
//-----------------------------------------------------------------------------
void UpdateCamera(void)
{
	Model *pModel;
	pModel = GetModel();

	//�����_�����f����
	g_camera.posR = pModel->pos;

	//���_�����f������J�����̌����ɒ���������
	g_camera.posV.x = pModel->pos.x - sinf(g_camera.rot.y) * 100;
	g_camera.posV.z = pModel->pos.z - cosf(g_camera.rot.y) * 100;

	////�O�i
	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	//���_�̈ʒu�ړ��Ag_camera.rot�̌�����
	//	g_camera.posV.x += sinf(g_camera.rot.y);
	//	g_camera.posV.z += cosf(g_camera.rot.y);

	//	//�����_�̈ʒu�Œ�Ag_camera.rot�̌�����
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////���
	//if (GetKeyboardPress(DIK_S) == true)
	//{
	//	g_camera.posV.x -= sinf(g_camera.rot.y);
	//	g_camera.posV.z -= cosf(g_camera.rot.y);
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////�E
	//if (GetKeyboardPress(DIK_D) == true)
	//{
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////��
	//if (GetKeyboardPress(DIK_A) == true)
	//{
	//	g_camera.posV.x -= sinf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posV.z -= cosf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}

	////�����_�@�E����
	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_camera.rot.y += CAMERA_SPEED;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////�����_�@������
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	//�����̈ړ�
	//	g_camera.rot.y -= CAMERA_SPEED;

	//	//�����_�̈ʒu�Œ�Ag_camera.rot�̌�����
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////�����_�@�㏸
	//else if (GetKeyboardPress(DIK_T) == true)
	//{
	//	g_camera.posR.y += CAMERA_SPEED * 10;
	//}
	////�����_�@���~
	//else if (GetKeyboardPress(DIK_B) == true)
	//{
	//	g_camera.posR.y -= CAMERA_SPEED * 10;
	//}

	////���_�@������
	//if (GetKeyboardPress(DIK_Z) == true)
	//{
	//	//���_�̈ʒu�ړ�
	//	g_camera.rot.y += CAMERA_SPEED;

	//	//���_�̌Œ�Ag_camera.rot�̌�����
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////���_�@�E����
	//else if (GetKeyboardPress(DIK_C) == true)
	//{
	//	g_camera.rot.y -= CAMERA_SPEED;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////���_�@�㏸
	//else if (GetKeyboardPress(DIK_Y) == true)
	//{
	//	g_camera.posV.y += CAMERA_SPEED * 10;
	//}
	////���_�@���~
	//else if (GetKeyboardPress(DIK_N) == true)
	//{
	//	g_camera.posV.y -= CAMERA_SPEED * 10;
	//}

}

//-----------------------------------------------------------------------------
// �J�����̐ݒ�
//-----------------------------------------------------------------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//-----------------------------------------------------------------------------
// �J�����̏��擾
//-----------------------------------------------------------------------------
Camera *GetCamera(void)
{
	return &g_camera;
}