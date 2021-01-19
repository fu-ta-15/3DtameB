//===================================================================
//
// �e�̏����@[bullet.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "bullet.h"
#include "billboard.h"

//===========================================================================================================
//�}�N����`
//===========================================================================================================
#define MAX_BULLET (512)					//�e�̍ő吔
#define BULLET_SIZE (5)					//�e�̑傫��

//=================================================================================================
//�O���[�o���ϐ�
//=================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;														//�e�̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;												//�o�b�t�@��
BULLET g_aBullet[MAX_BULLET];																	//�e�̏��	
D3DXMATRIX g_mtxWorldBullet;																	//���[���h�}�g���b�N�X

//=================================================================================================
//�v���g�^�C�v�錾
//=================================================================================================
void SetVertexBullet(int nIdy);

//=================================================================================================
//����������
//=================================================================================================
HRESULT InitBullet(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	//�e�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		SetVertexBullet(nCntBullet);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//=================================================================================================
//�I������
//=================================================================================================
void UninitBullet(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//=================================================================================================
//�X�V����
//=================================================================================================
void UpdateBullet(void)
{
	//�ϐ��錾
	BULLET *pBullet;

	VERTEX_3D *pVtx;

	pBullet = &g_aBullet[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		//�e�̍X�V
		if (pBullet->bUse == true)			//�e���g���Ă��邩
		{
			//�ʒu�̍X�V
			pBullet->pos += pBullet->move;

			//���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			//�G�t�F�N�g�̐ݒ�
			//SetEffect(pBullet->pos);

			/*ENEMY *pEnemy;
			pEnemy = GetENEMY();*/

			if (pBullet->type)
			{
				switch (pBullet->type)
				{
				case PLAYER_BULLET:
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					break;

				case ENEMY_BULLET:
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					break;
				}
			}

			//�����`�F�b�N
			pBullet->nLife--;

			if (pBullet->nLife <= 0)
			{
				pBullet->bUse = false;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=================================================================================================
//�`�揈��
//=================================================================================================
void DrawBullet(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;								//�r���[�}�g���b�N�X�擾�p				
	D3DXMATRIX mtxTrans;							//�v�Z�p�}�g���b�N�X
	BULLET *pBullet;

	pBullet = GetBullet();

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			//Z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				//Z�o�b�t�@�̍X�V

	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);				//�t�s������߂�

			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=================================================================================================
//�e�̒��_���W�̐ݒ�
//=================================================================================================
void SetVertexBullet(int nIdy)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdy * 4;

	//�e�̒��_���W
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x - BULLET_SIZE, g_aBullet[nIdy].pos.y + BULLET_SIZE, g_aBullet[nIdy].pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x + BULLET_SIZE, g_aBullet[nIdy].pos.y + BULLET_SIZE, g_aBullet[nIdy].pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x - BULLET_SIZE, g_aBullet[nIdy].pos.y - BULLET_SIZE, g_aBullet[nIdy].pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x + BULLET_SIZE, g_aBullet[nIdy].pos.y - BULLET_SIZE, g_aBullet[nIdy].pos.z);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=================================================================================================
//�e�̐ݒ�
//=================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	//�ϐ��錾
	BULLET *pBullet;
	VERTEX_3D *pVtx;

	pBullet = &g_aBullet[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//�ʒu�̐ݒ�
			pBullet->pos = pos;

			//�ړ��ʂ�ݒ�
			pBullet->move = move;

			//���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			//������ݒ�
			pBullet->nLife = nLife;

			pBullet->bUse = true;

			break;

		}
		//pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//===========================================================================================================
//�e�̎擾
//===========================================================================================================
BULLET *GetBullet(void)
{
	return *&g_aBullet;
}