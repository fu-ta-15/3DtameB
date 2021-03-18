//-----------------------------------------------------------------------------
//
// �X�J�C�{�b�N�X�̏��� [skybox.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "skybox.h"
#include "input.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define SKYBOX_FACES (6)	// �X�J�C�{�b�N�X�̖ʂ̐� (6��)
#define SPLIT_U (4.0f)		// �e�N�X�`���̕�����
#define SPLIT_V (3.0f)		//

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffSky = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;										// �|���S���̃e�N�X�`���ւ̃|�C���^
Skybox g_skybox[SKYBOX_FACES];													// �X�J�C�{�b�N�X�̏��

//-----------------------------------------------------------------------------
// Skybox����������
//-----------------------------------------------------------------------------
HRESULT InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); // device

	//�������ݒ�
	g_skybox[0].pos = D3DXVECTOR3(0.0f, 0.0f, SKYBOX_FACE_DISTANCE);
	g_skybox[1].pos = D3DXVECTOR3(0.0f, 0.0f, -SKYBOX_FACE_DISTANCE);
	g_skybox[2].pos = D3DXVECTOR3(SKYBOX_FACE_DISTANCE, 0.0f, 0.0f);
	g_skybox[3].pos = D3DXVECTOR3(-SKYBOX_FACE_DISTANCE, 0.0f, 0.0f);
	g_skybox[4].pos = D3DXVECTOR3(0.0f, SKYBOX_FACE_DISTANCE, 0.0f);
	g_skybox[5].pos = D3DXVECTOR3(0.0f, -SKYBOX_FACE_DISTANCE, 0.0f);
	
	g_skybox[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_skybox[1].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_skybox[2].rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f);
	g_skybox[3].rot = D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f);
	g_skybox[4].rot = D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f);
	g_skybox[5].rot = D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f);

	for (int nCntFace = 0; nCntFace < SKYBOX_FACES; nCntFace++)
	{
		g_skybox[nCntFace].bDraw = true;
	}

	//�e�N�X�`���ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//skybox.png", &g_pTextureSky);
	D3DXCreateTextureFromFileEx(pDevice, "data\\TEXTURE\\skybox1.png", 2048, 1536, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL, &g_pTextureSky);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT * SKYBOX_FACES,	//�T�C�Y
		D3DUSAGE_WRITEONLY,									//
		FVF_VERTEX_3D,										//�t�H�[�}�b�g
		D3DPOOL_MANAGED,									//
		&g_pVtxBuffSky,									//���_�o�b�t�@�ւ̃|�C���^
		NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_3D *pVertex;
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVertex, 0);

	//6�ʕ�
	for (int nCntFace = 0; nCntFace < SKYBOX_FACES; nCntFace++, pVertex += 4)
	{
		//���_���W�ݒ�
		pVertex[0].pos = D3DXVECTOR3(-SKYBOX_FACE_WIDTH / 2, -SKYBOX_FACE_HEIGHT / 2, 0.0f);
		pVertex[1].pos = D3DXVECTOR3(-SKYBOX_FACE_WIDTH / 2, SKYBOX_FACE_HEIGHT / 2, 0.0f);
		pVertex[2].pos = D3DXVECTOR3(SKYBOX_FACE_WIDTH / 2, -SKYBOX_FACE_HEIGHT / 2, 0.0f);
		pVertex[3].pos = D3DXVECTOR3(SKYBOX_FACE_WIDTH / 2, SKYBOX_FACE_HEIGHT / 2, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVertex[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVertex[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVertex[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVertex[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVertex[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVertex[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVertex[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVertex[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		switch (nCntFace)
		{
		case 0:	// ����
			pVertex[0].tex = D3DXVECTOR2(1.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(1.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(2.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(2.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 1:	// ���
			pVertex[0].tex = D3DXVECTOR2(3.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(3.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(4.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(4.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 2:	// �E
			pVertex[0].tex = D3DXVECTOR2(2.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(2.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(3.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(3.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 3:	// ��
			pVertex[0].tex = D3DXVECTOR2(0.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(0.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(1.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(1.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 4:	// ��
			pVertex[0].tex = D3DXVECTOR2(1.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(1.0f / SPLIT_U, 0.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(2.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(2.0f / SPLIT_U, 0.0f / SPLIT_V);
			break;
		case 5:	// ��
			pVertex[0].tex = D3DXVECTOR2(1.0f / SPLIT_U, 3.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(1.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(2.0f / SPLIT_U, 3.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(2.0f / SPLIT_U, 2.0f / SPLIT_V);
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSky->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Skybox�I������
//-----------------------------------------------------------------------------
void UninitSky(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}
}

//-----------------------------------------------------------------------------
// Skybox�X�V����
//-----------------------------------------------------------------------------
void UpdateSky(void)
{
	if (GetKeyboardPress(DIK_F) == true)
	{
		g_skybox[0].rot.x += 0.05f;
	}
}

//-----------------------------------------------------------------------------
// Skybox�`�揈��
//-----------------------------------------------------------------------------
void DrawSky(void)
{
	for (int nCntFace = 0; nCntFace < SKYBOX_FACES; nCntFace++)
	{
		if (g_skybox[nCntFace].bDraw == true)
		{
			LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
			D3DXMATRIX mtxView;					// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxTrans, mtxRot;		// �v�Z�p�}�g���b�N�X

			//�f�o�C�X�擾
			pDevice = GetDevice();

			//���C�e�B���O�̉e�����󂯂Ȃ�����
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//�T���v���[�X�e�[�g�̐ݒ�
			pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);	
			pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);	
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_skybox[nCntFace].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_skybox[nCntFace].rot.y, g_skybox[nCntFace].rot.x, g_skybox[nCntFace].rot.z);
			D3DXMatrixMultiply(&g_skybox[nCntFace].mtxWorld, &g_skybox[nCntFace].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_skybox[nCntFace].pos.x, g_skybox[nCntFace].pos.y, g_skybox[nCntFace].pos.z);
			D3DXMatrixMultiply(&g_skybox[nCntFace].mtxWorld, &g_skybox[nCntFace].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_skybox[nCntFace].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSky, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSky);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFace * 4, 2);

			//RS�߂�
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			//�T���v���[�X�e�[�g�̐ݒ�
			pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
			pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�
		}
	}
}