//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author:Taiki Hayasaka, Sota Tomoe
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_CAMERA (4.0f)				// �ړ���
#define CAMERA_DISTANCE (600.0f)		// ����
#define CAMERA_MOUSE_SENSITIVITY (550)	// �}�E�X�̊��x
#define CAMERA_ROT_LIMIT_UPPER
#define CAMERA_ROT_LIMIT_LOWER


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
Camera g_camera;					//�J�����̏��

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	//������
	g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -CAMERA_DISTANCE);
	g_camera.posVDest = g_camera.posV;
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = g_camera.posR;
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();

	//�}�E�X�̈ړ��ʂ����_�̉�]�ɒǉ�
	g_camera.rot.y += GetMouseVelocity().x / 550;
	g_camera.rot.z -= GetMouseVelocity().y / 550;

	if (g_camera.rot.z > D3DX_PI / 2.0f) g_camera.rot.z = D3DX_PI / 2.0f;
	else if (g_camera.rot.z < -D3DX_PI / 2.0f) g_camera.rot.z = -D3DX_PI / 2.0f;
	if (g_camera.rot.z > 0) g_camera.rot.z = 0.0f;	// ���ɓ˂������Ȃ��悤�ɂ���

	//D3DXPI���������̑Ώ�
	if (g_camera.rot.x > D3DX_PI) g_camera.rot.x -= D3DX_PI * 2.0f;
	if (g_camera.rot.x < -D3DX_PI) g_camera.rot.x += D3DX_PI * 2.0f;
	if (g_camera.rot.y > D3DX_PI) g_camera.rot.y -= D3DX_PI * 2.0f;
	if (g_camera.rot.y < -D3DX_PI) g_camera.rot.y += D3DX_PI * 2.0f;
	if (g_camera.rot.z > D3DX_PI) g_camera.rot.z -= D3DX_PI * 2.0f;
	if (g_camera.rot.z < -D3DX_PI) g_camera.rot.z += D3DX_PI * 2.0f;

	//�Ǐ]
	FollowCamera();
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

							  //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),								//��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,												//��O�̕`��
		100000.0f);											//���̕`��

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

//=============================================================================
// ���f���̒Ǐ]
//=============================================================================
void FollowCamera(void)
{
	Player *pPlayer = GetPlayer();

	g_camera.posR = pPlayer->pos;

	//----------------------�c��]�o�[�W����(3�����ɍ��W(�����W))---------------------------------
	//�����_�����f����
	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 10;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 10;
	g_camera.posR.y = pPlayer->pos.y + 30.0f;

	//���_�����f������J�����̌����ɒ���������
	g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.z) * CAMERA_DISTANCE;
	g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.z) * CAMERA_DISTANCE;
	g_camera.posV.y = pPlayer->pos.y - sinf(g_camera.rot.z) * CAMERA_DISTANCE;
	//---------------------------------------------------------------------
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}