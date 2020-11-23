//=============================================================================
//
// �ǂ̏��� [wall.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "wall.h"
#include "input.h"					

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_WALL (4)							//�Ǎő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureWall = NULL;		//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posWall;							//�ʒu
D3DXVECTOR3 g_rotWall;							//����
D3DXMATRIX g_mtxWorldWall;						//���[���h�}�g���b�N�X
Wall g_aWall[MAX_WALL];							//�ǂ̏��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_3D *pVtx;			//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wall002.jpg", &g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�(Z�^)
		SetVertexWall(nCntWall);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//�e�N�X�`�����W
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Z�^
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�S�̒��_��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//�e�N�X�`���̊J��

	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	int nCntVertex = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldWall);

		//���C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		//�|���S���̕`��
		if (g_aWall[nCntWall].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		}
		//�S�i�߂�
		nCntVertex += 4;

		//���C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//=============================================================================
// 
//=============================================================================
void SetVertexWall(int nCntWall)
{
	VERTEX_3D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntWall * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - 180.0f, g_aWall[nCntWall].pos.y + 90.0f, g_aWall[nCntWall].pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + 180.0f, g_aWall[nCntWall].pos.y + 90.0f, g_aWall[nCntWall].pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - 180.0f, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + 180.0f, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//=============================================================================
//
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{

		if (g_aWall[nCntWall].bUse == false)
		{
			//�����̐ݒ�
			g_aWall[nCntWall].rot = rot;

			//�ʒu��ݒ�
			g_aWall[nCntWall].pos = pos;

			//���_���W�̐ݒ�
			SetVertexWall(nCntWall);

			//�G�̎g�p�̐ݒ�
			g_aWall[nCntWall].bUse = true;

			break;
		}
		//�S�̒��_��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}