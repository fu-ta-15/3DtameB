//=========================================================================================================================
//
// �p�[�e�B�N�� [Particle.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "Particle.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "player.h"

//
//
//
#define MAX_PARTICLE (2048)			// �p�[�e�B�N���̍ő吔
#define PARTICLE_SIZE (2.0f)		// �p�[�e�B�N���̑傫��
#define PARTICLE_SPD (5.0f)			// �p�[�e�B�N���̈ړ���(���x)
#define PARTICLE_LIFE (100)			// �p�[�e�B�N���̎���

//
// �O���[�o���ϐ�
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;			// �e�N�X�`���ւ̃|�C���^
PARTICLE g_aParticle[MAX_PARTICLE];						// �p�[�e�B�N���̏��

//
// ����������
//
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureParticle);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].bUse = false;
		g_aParticle[nCnt].nLife = 0;
	}


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		// 
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x - PARTICLE_SIZE, g_aParticle[nCnt].pos.y - PARTICLE_SIZE, g_aParticle[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x - PARTICLE_SIZE, g_aParticle[nCnt].pos.y + PARTICLE_SIZE, g_aParticle[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x + PARTICLE_SIZE, g_aParticle[nCnt].pos.y - PARTICLE_SIZE, g_aParticle[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x + PARTICLE_SIZE, g_aParticle[nCnt].pos.y + PARTICLE_SIZE, g_aParticle[nCnt].pos.z);

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
	g_pVtxBuffParticle->Unlock();

	return S_OK;
}


//
// �I������
//
void UninitParticle(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

}


//
// �X�V����
//
void UpdateParticle(void)
{
	Camera *pCamera = GetCamera();
	PARTICLE *pParticle = &g_aParticle[0];
	//MODEL *pModel = GetModel();
	PLAYER *pPlayer = GetPlayer();

	if (GetKeyboardPress(DIK_9) == true)
	{
		SetParticle(pPlayer->pos, D3DXVECTOR3(sinf(pPlayer->rot.y) * PARTICLE_SPD, 0.0f, cosf(pPlayer->rot.y) * PARTICLE_SPD));
	}

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			pParticle->pos.x -= pParticle->move.x;
			pParticle->pos.z -= pParticle->move.z;

			g_aParticle[nCnt].nLife++;
			if (g_aParticle[nCnt].nLife >= PARTICLE_LIFE)
			{
				pParticle->bUse = false;
				g_aParticle[nCnt].nLife = 0;
			}
		}
	}
}


//
// �`�揈��
//
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	PARTICLE *pParticle = &g_aParticle[0];

	D3DXMATRIX mtxView;								// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxTrans;							// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�o�b�t�@��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++, pParticle++)
	{
		if (pParticle->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pParticle->mtxWorld);

			// �r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pParticle->mtxWorld, NULL, &mtxView);	// �t�s������߂�
			pParticle->mtxWorld._41 = 0.0f;
			pParticle->mtxWorld._42 = 0.0f;
			pParticle->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pParticle->pos.x, pParticle->pos.y, pParticle->pos.z);

			D3DXMatrixMultiply(&pParticle->mtxWorld, &pParticle->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pParticle->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);

			

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCnt * 4,						// �`����J�n���钸�_�C���f�b�N�X
				2);								// �`�悷��v���~�e�B�u�̐�

		}
	}

	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// �W���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//
// �p�[�e�B�N���̐ݒ�
//
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	PARTICLE *pParticle = &g_aParticle[0];

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++, pParticle++)
	{
		if (pParticle->bUse == false)
		{
			pParticle->pos = pos;

			pParticle->move = move;

			pParticle->bUse = true;

			break;
		}
	}
}
