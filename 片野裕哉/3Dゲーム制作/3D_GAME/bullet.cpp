//=========================================================================================================================
//
// �e [bullet.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "bullet.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "player.h"

//
//
//
#define MAX_BULLET (256)		// �e�̍ő吔
#define BULLET_SIZE (2.0f)		// �e�̑傫��
#define BULLET_SPD (5.0f)		// �e�̈ړ���(���x)
#define BULLET_LIFE (100)		// �e�̎���

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// �e�N�X�`���ւ̃|�C���^
BULLET g_aBullet[MAX_BULLET];						// �e�̏��
int g_aLife[MAX_BULLET];

//
// ����������
//
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_aBullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].bUse = false;
		g_aLife[nCnt] = 0;
	}
	

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		// 
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x - BULLET_SIZE, g_aBullet[nCnt].pos.y - BULLET_SIZE, g_aBullet[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x - BULLET_SIZE, g_aBullet[nCnt].pos.y + BULLET_SIZE, g_aBullet[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x + BULLET_SIZE, g_aBullet[nCnt].pos.y - BULLET_SIZE, g_aBullet[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCnt].pos.x + BULLET_SIZE, g_aBullet[nCnt].pos.y + BULLET_SIZE, g_aBullet[nCnt].pos.z);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitBullet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}


//
// �X�V����
//
void UpdateBullet(void)
{
	Camera *pCamera = GetCamera();
	BULLET *pBullet = &g_aBullet[0];
	//MODEL *pModel = GetModel();
	PLAYER *pPlayer = GetPlayer();

	if (GetKeyboardPress(DIK_0) == true)
	{
		SetBullet(pPlayer->pos, D3DXVECTOR3(sinf(pPlayer->rot.y) * BULLET_SPD, 0.0f, cosf(pPlayer->rot.y) * BULLET_SPD));
	}

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			pBullet->pos.x -= pBullet->move.x;
			pBullet->pos.z -= pBullet->move.z;

			g_aLife[nCnt]++;
			if (g_aLife[nCnt] == BULLET_LIFE)
			{
				pBullet->bUse = false;
				g_aLife[nCnt] = 0;
			}
		}
	}
}


//
// �`�揈��
//
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	BULLET *pBullet = &g_aBullet[0];

	D3DXMATRIX mtxView;								// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxTrans;							// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pBullet->mtxWorld);

			// �r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView);	// �t�s������߂�
			pBullet->mtxWorld._41 = 0.0f;
			pBullet->mtxWorld._42 = 0.0f;
			pBullet->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);

			D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCnt * 4,						// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�
			
		}
	}

	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//
// �e�̐ݒ�
//
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	BULLET *pBullet = &g_aBullet[0];

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			pBullet->pos = pos;

			pBullet->move = move;

			pBullet->bUse = true;

			break;
		}
	}
}
