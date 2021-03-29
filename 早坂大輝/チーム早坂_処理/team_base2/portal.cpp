//-----------------------------------------------------------------------------
//
// �|�[�^���̏��� [portal.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "portal.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffPortal = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePortal = NULL;											// �|���S���̃e�N�X�`���ւ̃|�C���^
Portal g_portal;																	// �|�[�^���̏��

//-----------------------------------------------------------------------------
// �|�[�^���̏���������
//-----------------------------------------------------------------------------
HRESULT InitPortal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|�[�^���̏�񏉊���
	g_portal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_portal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_portal.bActive = false;
	g_portal.bDraw = false;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//portal.png", &g_pTexturePortal);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT,					//�T�C�Y
		D3DUSAGE_WRITEONLY,									//
		FVF_VERTEX_3D,										//�t�H�[�}�b�g
		D3DPOOL_MANAGED,									//
		&g_pVtxBuffPortal,									//���_�o�b�t�@�ւ̃|�C���^
		NULL);

	VERTEX_3D *pVertex;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPortal->Lock(0, 0, (void**)&pVertex, 0);

	//���_���W�ݒ�
	pVertex[0].pos = D3DXVECTOR3(-PORTAL_WIDTH, 0.0f, 0.0f);
	pVertex[1].pos = D3DXVECTOR3(-PORTAL_WIDTH, PORTAL_HEIGHT, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(PORTAL_WIDTH, 0.0f, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(PORTAL_WIDTH, PORTAL_HEIGHT, 0.0f);

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
	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPortal->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Portal�I������
//-----------------------------------------------------------------------------
void UninitPortal(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePortal != NULL)
	{
		g_pTexturePortal->Release();
		g_pTexturePortal = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPortal != NULL)
	{
		g_pVtxBuffPortal->Release();
		g_pVtxBuffPortal = NULL;
	}
}

//-----------------------------------------------------------------------------
// Portal�X�V����
//-----------------------------------------------------------------------------
void UpdatePortal(void)
{
	//if portal is active
	if (g_portal.bActive == true)
	{
		Player *pPlayer = GetPlayer();

		//�|�[�^���ƃv���C���[�̏Փ˔���
		if (CollisionBoxBox(&pPlayer->pos, &g_portal.pos, PlAYER_WIDTH, PlAYER_WIDTH, PORTAL_WIDTH, 10.0f) == true)
		{
			//�X�e�[�W�J��
			Stage *pStage = GetStage();

			if (pStage->nStageNum < 2)
			{
				pStage->nStageNum++;
				SetFade(FADE_OUT, MODE_GAME);
			}
			else
			{
				pStage->nStageNum = 0;
				SetFade(FADE_OUT, MODE_RANKING);
			}

			//�|�[�^�����g�p�s��
			g_portal.bActive = false;
		}
	}
}

//-----------------------------------------------------------------------------
// Portal�`�揈��
//-----------------------------------------------------------------------------
void DrawPortal(void)
{
	if (g_portal.bDraw == true)
	{
		LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
		D3DXMATRIX mtxView;					// �r���[�}�g���b�N�X�擾
		D3DXMATRIX mtxTrans, mtxRot;		// �v�Z�p�}�g���b�N�X

		//�f�o�C�X�擾
		pDevice = GetDevice();

		//�J�����O�̐ݒ�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_portal.mtxWorld);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_portal.rot.y, g_portal.rot.x, g_portal.rot.z);
		D3DXMatrixMultiply(&g_portal.mtxWorld, &g_portal.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_portal.pos.x, g_portal.pos.y, g_portal.pos.z);
		D3DXMatrixMultiply(&g_portal.mtxWorld, &g_portal.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_portal.mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPortal, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePortal);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//�J�����O�̐ݒ��߂�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//-----------------------------------------------------------------------------
// �|�[�^���̃A�N�e�B�u��Ԃ�ύX
//-----------------------------------------------------------------------------
void ActivatePortal(bool bActive, bool bDraw)
{
	//�|�[�^�����g���邩�ǂ�����ύX
	if (bActive == true) g_portal.bActive = true;
	else g_portal.bActive = false;

	//�|�[�^����`�悷�邩�ǂ���
	if (bDraw == true) g_portal.bDraw = true;
	else g_portal.bDraw = false;
}