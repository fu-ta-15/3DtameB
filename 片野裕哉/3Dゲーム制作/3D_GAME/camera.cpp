//
//
// �J���� [camera.cpp]
//
//
//
#include "camera.h"
#include "input.h"

//
// �}�N����`
//
#define CAMERA_SPD (3.0f)

//
// �O���[�o���ϐ�
//
Camera g_camera;		// �J�����̏��

//
// ����������
//
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 90.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;
}


//
// �I������
//
void UninitCamera(void)
{

}


//
// �X�V����
//
void UpdateCamera(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 90.0f, -200.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;
	}

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.x += sinf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.z += cosf(g_camera.rot.y) * CAMERA_SPD;
	}

	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.x -= sinf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.z -= cosf(g_camera.rot.y) * CAMERA_SPD;
	}

	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posV.x -= cosf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.x -= cosf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posV.z += sinf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.z += sinf(g_camera.rot.y) * CAMERA_SPD;
	}

	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posV.x += cosf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.x += cosf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posV.z -= sinf(g_camera.rot.y) * CAMERA_SPD;
		g_camera.posR.z -= sinf(g_camera.rot.y) * CAMERA_SPD;
	}

	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.posV.y += 2.0f;
	}

	if (GetKeyboardPress(DIK_N) == true)
	{
		g_camera.posV.y -= 2.0f;
	}

	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.y += 0.02f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= 0.02f;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.posR.y += 2.0f;
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.posR.y -= 2.0f;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y -= 0.02f;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y += 0.02f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_U) == true)
	{
		if (g_camera.fDistance > 100.0f)
		{
			g_camera.fDistance -= 1.0f;
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}
	}

	if (GetKeyboardPress(DIK_M) == true)
	{
		if (g_camera.fDistance < 300.0f)
		{
			g_camera.fDistance += 1.0f;
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}
	}
}


//
// �ݒ�
//
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxPrjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxPrjection,
		D3DXToRadian(45.0f),							// ��p(45�x)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// ��ʔ䗦
		10.0f,											// Z�̎�O
		1000.0f);										// Z�̉�

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxPrjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}


//
// �J�����̎擾
//
Camera *GetCamera(void)
{
	return &g_camera;
}
