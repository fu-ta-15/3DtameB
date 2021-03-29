//-----------------------------------------------------------------------------
//
// �{�X�̍U������ [boss_attack.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "boss_attack.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "input.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void UpdateFloor(void);
void AttackDetail(void);
bool CheckFloor(D3DXVECTOR3 checkPos, int nIdx);
void InitializeFloor(int nIdx);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBossATK = NULL;			// �|���S���̃e�N�X�`���ւ̃|�C���^																// �|�[�^���̏��
AttackFloor g_bossAttack[BOSS_ATTACK_MAX];				// �{�X�̍U�����̏��

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitBossATK(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//circle.png", &g_pTextureBossATK);

	//���_�o�b�t�@����
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		VERTEX_3D *pVertex;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT * BOSS_ATTACK_OBJ,					//�T�C�Y
			D3DUSAGE_WRITEONLY,									//
			FVF_VERTEX_3D,										//�t�H�[�}�b�g
			D3DPOOL_MANAGED,									//
			&g_bossAttack[nCntBATK].pVtx,						//���_�o�b�t�@�ւ̃|�C���^
			NULL);

		//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		g_bossAttack[nCntBATK].pVtx->Lock(0, 0, (void**)&pVertex, 0);

		for (int nCntFloor = 0; nCntFloor < BOSS_ATTACK_OBJ; nCntFloor++, pVertex += 4)
		{
			//�����̏�����
			InitializeFloor(nCntBATK);

			//���_���W�ݒ�
			pVertex[0].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS, 0.0f, -BOSS_ATTACK_RADIUS);
			pVertex[1].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS, 0.0f, BOSS_ATTACK_RADIUS);
			pVertex[2].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS, 0.0f, -BOSS_ATTACK_RADIUS);
			pVertex[3].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS, 0.0f, BOSS_ATTACK_RADIUS);

			//�@���x�N�g���̐ݒ�
			for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//���_�J���[�̐ݒ�
			if (nCntFloor == 0)
			{
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);
			}

			//�e�N�X�`�����W�̐ݒ�
			pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		//���_�o�b�t�@���A�����b�N����
		g_bossAttack[nCntBATK].pVtx->Unlock();
	}

	//BeginBossAttack(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitBossATK(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBossATK != NULL)
	{
		g_pTextureBossATK->Release();
		g_pTextureBossATK = NULL;
	}

	//���_�o�b�t�@�̔j��
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (g_bossAttack[nCntBATK].pVtx != NULL)
		{
			g_bossAttack[nCntBATK].pVtx->Release();
			g_bossAttack[nCntBATK].pVtx = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateBossATK(void)
{
	Player *pPlayer = GetPlayer();

	UpdateFloor();	// ���̏�ԍX�V

	if (GetKeyboardTrigger(DIK_V)) BeginBossAttack(pPlayer->pos);	// �e�X�g�p V�Ń{�X�̍U���v���C���[�ɗ���
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawBossATK(void)
{
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (g_bossAttack[nCntBATK].bDraw == true)
		{
			LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
			D3DXMATRIX mtxView;					// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxTrans, mtxRot;		// �v�Z�p�}�g���b�N�X

			//�f�o�C�X�擾
			pDevice = GetDevice();

			//���Z�����̐ݒ�
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X�i�`�挳�j�̍������@�̐ݒ�
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	//�f�X�e�B�l�[�V�����i�`���j�̍������@�̐ݒ�

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_bossAttack[nCntBATK].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_bossAttack[nCntBATK].rot.y, g_bossAttack[nCntBATK].rot.x, g_bossAttack[nCntBATK].rot.z);
			D3DXMatrixMultiply(&g_bossAttack[nCntBATK].mtxWorld, &g_bossAttack[nCntBATK].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_bossAttack[nCntBATK].pos.x, g_bossAttack[nCntBATK].pos.y, g_bossAttack[nCntBATK].pos.z);
			D3DXMatrixMultiply(&g_bossAttack[nCntBATK].mtxWorld, &g_bossAttack[nCntBATK].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_bossAttack[nCntBATK].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_bossAttack[nCntBATK].pVtx, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCntFloor = 0; nCntFloor < BOSS_ATTACK_OBJ; nCntFloor++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBossATK);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFloor * 4, 2);
			}

			//�ʏ퍇���ɖ߂�
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}
}

//-----------------------------------------------------------------------------
// �U�������̊J�n
//-----------------------------------------------------------------------------
void BeginBossAttack(D3DXVECTOR3 pos)
{
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (!g_bossAttack[nCntBATK].bDraw)
		{//	�`�悵�Ă��Ȃ���
			g_bossAttack[nCntBATK].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);		// pos set
			g_bossAttack[nCntBATK].bDraw = true;								// start draw

			break;
		}
	}
}

/* �U�����e */
void AttackDetail(void)
{
	Player *pPlayer = GetPlayer();

	pPlayer->move.y += 5.0f;	// ��ɔ�΂�
}

/* ���̏�ԍX�V */
void UpdateFloor(void)
{
	Player *pPlayer = GetPlayer();
	VERTEX_3D *pVertex;

	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (g_bossAttack[nCntBATK].bDraw)
		{//	�`�撆�̕�
			//0%~100%�܂ŏ��X�ɉ��Z�A100%�ōU���t���O��L����
			if (g_bossAttack[nCntBATK].bDraw && g_bossAttack[nCntBATK].fFloorRatio <= 1.0f) g_bossAttack[nCntBATK].fFloorRatio += 0.01f;
			if (g_bossAttack[nCntBATK].fFloorRatio >= 1.0f)
			{
				g_bossAttack[nCntBATK].bAttackFlag = true;
				if (CheckFloor(pPlayer->pos, nCntBATK)) AttackDetail();	// �Ώۂ��͈͓����m�F�A�����Ă��ꍇ�U������
				InitializeFloor(nCntBATK);	// ���̏�����
			}

			//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
			g_bossAttack[nCntBATK].pVtx->Lock(0, 0, (void**)&pVertex, 0);

			pVertex += 4;	// 2���ڂɍs��

			pVertex[0].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, -BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);
			pVertex[1].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);
			pVertex[2].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, -BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);
			pVertex[3].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);

			g_bossAttack[nCntBATK].pVtx->Unlock();
		}
	}
}

/* �ԏ��͈͓̔��ɑΏۂ��������`�F�b�N */
bool CheckFloor(D3DXVECTOR3 checkPos, int nIdx)
{
	//�Ώۂ̈ʒu�Ə��̒��S�̋��� XZ��
	float fDistance = sqrtf((g_bossAttack[nIdx].pos.x - checkPos.x) * ((g_bossAttack[nIdx].pos.x) - checkPos.x) + (g_bossAttack[nIdx].pos.z - checkPos.z) * (g_bossAttack[nIdx].pos.z - checkPos.z));

	if (fDistance <= BOSS_ATTACK_RADIUS)
	{//	�����Ă�
		return true;
	}
	else
	{//	�����ĂȂ�
		return false;
	}
}

/* ���̏������������� */
void InitializeFloor(int nIdx)
{
	g_bossAttack[nIdx].bAttackFlag = false;
	g_bossAttack[nIdx].bDraw = false;
	g_bossAttack[nIdx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_bossAttack[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_bossAttack[nIdx].fFloorRatio = 0.0f;
}