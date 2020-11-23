//
//
// ���C�g [light.cpp]
//
//
//
#include "light.h"

//
// �O���[�o���ϐ�
//
D3DLIGHT9 g_alight[3];		// ���C�g�̏��

//
// ����������
//
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;								// �f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir0;									// �ݒ�p�����x�N�g��
	D3DXVECTOR3 vecDir1;									// �ݒ�p�����x�N�g��
	D3DXVECTOR3 vecDir2;									// �ݒ�p�����x�N�g��

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���C�g���N���A����
	ZeroMemory(&g_alight, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{

		// ���C�g�̎�ނ�ݒ�
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		g_alight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕�����ݒ�
		vecDir0 = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir0, &vecDir0);					// ���K������

		vecDir1 = D3DXVECTOR3(0.5f, -0.8f, 0.4f);
		D3DXVec3Normalize(&vecDir1, &vecDir1);					// ���K������

		vecDir2 = D3DXVECTOR3(-0.2f, 0.5f, 0.2f);
		D3DXVec3Normalize(&vecDir2, &vecDir2);					// ���K������

		switch (nCntLight)
		{
		case 0:
			g_alight[nCntLight].Direction = vecDir0;
			break;
		case 1:
			g_alight[nCntLight].Direction = vecDir1;
			break;
		case 2:
			g_alight[nCntLight].Direction = vecDir2;
			break;
		default:
			break;
		}

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_alight[nCntLight]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}

	
}


//
// �I������
//
void UninitLight(void)
{

}


//
// �X�V����
//
void UpdateLight(void)
{

}
