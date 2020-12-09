//-----------------------------------------------------------------------------
//
// �ǂ̏��� [wall.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "wall.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffWall = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;									// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;										// �|���S���̃e�N�X�`���ւ̃|�C���^
Wall g_aWall[WALL_MAX];															// �ǂ̏��
D3DXVECTOR3 g_posWall;															// �ʒu
D3DXVECTOR3 g_rotWall;															// ����
D3DXMATRIX g_mtxWorldWall;														// ���[���h�}�g���b�N�X

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg" , &g_pTextureWall);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * WALL_MAX,		//�T�C�Y
								D3DUSAGE_WRITEONLY,									//
								FVF_VERTEX_3D,										//�t�H�[�}�b�g
								D3DPOOL_MANAGED,									//
								&g_pVtxBuffWall,									//���_�o�b�t�@�ւ̃|�C���^
								NULL);

	VERTEX_3D *pVertex;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		//���_���W�ݒ� (��������E��O�ɏ���)
		pVertex[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
		pVertex[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
		pVertex[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
		pVertex[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
		pVertex[4].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
		pVertex[5].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
		pVertex[6].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		pVertex[7].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		pVertex[8].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

		//pVertex[0].pos = D3DXVECTOR3(g_posWall.x - WALL_WIDTH * 2, g_posWall.y, g_posWall.z);
		//pVertex[1].pos = D3DXVECTOR3(g_posWall.x - WALL_WIDTH * 2, g_posWall.y + WALL_HEIGHT, g_posWall.z);
		//pVertex[2].pos = D3DXVECTOR3(g_posWall.x + WALL_WIDTH * 2, g_posWall.y, g_posWall.z);
		//pVertex[3].pos = D3DXVECTOR3(g_posWall.x + WALL_WIDTH * 2, g_posWall.y + WALL_HEIGHT, g_posWall.z);

		for (int nCnt = 0; nCnt < 9; nCnt++)
		{
			//�@���̐ݒ�
			pVertex[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//���_�J���[�̐ݒ�
			pVertex[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�e�N�X�`�����W�̐ݒ�
		pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertex[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVertex[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVertex[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVertex[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVertex[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVertex[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertex[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVertex[8].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffWall,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

	//�ԍ��f�[�^�ݒ� (��M�����ɂȂ鏇��)
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffWall->Unlock();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f), NULL, NULL);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateWall(void)
{

}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�擾
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				14,
				0,
				12);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	VERTEX_3D *pVertex;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			//�ʒu�̐ݒ�
			g_aWall[nCntWall].pos = pos;

			//��]�̐ݒ�
			g_aWall[nCntWall].rot = rot;

			//���ݒ�
			g_aWall[nCntWall].fWidth = fWidth;

			//�����ݒ�
			g_aWall[nCntWall].fHeight = fHeight;

			////���_���ݒ�
			//pVertex[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
			//pVertex[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
			//pVertex[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
			//pVertex[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
			//pVertex[4].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
			//pVertex[5].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
			//pVertex[6].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			//pVertex[7].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			//pVertex[8].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

			//�g�p���ɕύX
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}