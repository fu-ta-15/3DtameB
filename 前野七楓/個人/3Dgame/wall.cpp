//=================================================================================================================
//
// �ǂ̏����@�kwall.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "wall.h"
#include "input.h"
#include "polygon.h"

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
D3DXVECTOR3 g_posWall;			//�ʒu
D3DXVECTOR3 g_rotWall;			//����
D3DXMATRIX g_mtxWorldWall;		//���[���h�}�g���b�N�X


//*****************************************************************************************************************
//	�|���S���̏���������
//*****************************************************************************************************************
HRESULT InitWall(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\wall00.jfif", &g_pTextureWall);

	g_posWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL)))
	{
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ� (XYZ)
	pVtx[0].pos = D3DXVECTOR3(g_posWall.x - F_SIZE_X,g_posWall.y + 150.0f, F_SIZE_X);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x + F_SIZE_X,g_posWall.y + 150.0f, F_SIZE_X);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x - F_SIZE_X,g_posWall.y, F_SIZE_X);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x + F_SIZE_X,g_posWall.y, F_SIZE_X);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���[���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return E_NOTIMPL;
}

//*****************************************************************************************************************
//	�|���S���̏I������
//*****************************************************************************************************************
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

//*****************************************************************************************************************
//	�|���S���̍X�V����
//*****************************************************************************************************************
void UpdateWall(void)
{
}

//*****************************************************************************************************************
//	�|���S���̕`�揈��
//*****************************************************************************************************************
void DrawWall(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;	

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldWall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotWall.y, g_rotWall.x, g_rotWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posWall.x, g_posWall.y, g_posWall.z);
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
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
