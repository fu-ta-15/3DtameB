//===================================================================
//
// ���C�g�̏����@[light.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "light.h"

//=================================================================================================
//�O���[�o���ϐ�
//=================================================================================================
D3DLIGHT9 g_light[3];					//���C�g�̏��

//=================================================================================================
//����������
//=================================================================================================�@
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir;							//�ݒ�p�����x�N�g��

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���C�g���N���A����
	ZeroMemory(&g_light,sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;					//�g�U��
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;					//�g�U��
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;					//�g�U��

	//���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);					//���K������
	g_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.2f);
	D3DXVec3Normalize(&vecDir, &vecDir);					//���K������
	g_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.2f, 0.8f, 0.8f);
	D3DXVec3Normalize(&vecDir, &vecDir);					//���K������
	g_light[2].Direction = vecDir;

	//���C�g��ݒ肷��
	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=================================================================================================
//�I������
//=================================================================================================
void UninitLight(void)
{
}

//=================================================================================================
//�X�V����
//=================================================================================================�@
void UpdateLight(void)
{
}