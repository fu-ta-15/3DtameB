#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// �Փ˔���̏��� [collision.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "input.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define BOX_VERTICES (8)

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
VCollision g_aVCollision[MAX_VISIBLE_COLLISION];								// �����R���W�����̏��
D3DXVECTOR3 g_WeaponCol1;
D3DXVECTOR3 g_WeaponCol2;
D3DXVECTOR3 g_WeaponCol3;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitCollision(void)
{
#ifdef _DEBUG
	Player *pPlayer = GetPlayer();

	//������
	for (int nCntVCol = 0; nCntVCol < MAX_VISIBLE_COLLISION; nCntVCol++)
	{
		g_aVCollision[nCntVCol].bUse = false;
		g_aVCollision[nCntVCol].nIdx = 0;
		g_aVCollision[nCntVCol].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aVCollision[nCntVCol].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	D3DXCOLOR tred = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

	g_WeaponCol1 = D3DXVECTOR3(pPlayer->mtxWeaponCol[0]._41, pPlayer->mtxWeaponCol[0]._42, pPlayer->mtxWeaponCol[0]._43);
	g_WeaponCol2 = D3DXVECTOR3(pPlayer->mtxWeaponCol[1]._41, pPlayer->mtxWeaponCol[1]._42, pPlayer->mtxWeaponCol[1]._43);
	g_WeaponCol3 = D3DXVECTOR3(pPlayer->mtxWeaponCol[2]._41, pPlayer->mtxWeaponCol[2]._42, pPlayer->mtxWeaponCol[2]._43);
	SetSphere(g_WeaponCol1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), tred, PLAYER_ATTACK_RADIUS, 10, 0);
	SetSphere(g_WeaponCol2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), tred, PLAYER_ATTACK_RADIUS, 10, 1);
	SetSphere(g_WeaponCol3, D3DXVECTOR3(0, 0, 0), tred, PLAYER_ATTACK_RADIUS, 10, 2);

#endif // !_DEBUG
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitCollision(void)
{
	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		//���b�V���j��
		if (g_aVCollision[nCntCollision].pMesh != NULL)
		{
			g_aVCollision[nCntCollision].pMesh->Release();
			g_aVCollision[nCntCollision].pMesh = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateCollision(void)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();
	
	DWORD currentTime = timeGetTime();	// ���݂̎���	

	//�G�ƃv���C���[�̍U������
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].bUse == true)
		{
			//��̈ʒu�ƓG�̈ʒu�Ŕ���
			D3DXVECTOR3 spherePos = D3DXVECTOR3(pPlayer->aModel[3].mtxWorld._41, pPlayer->aModel[3].mtxWorld._42, pPlayer->aModel[3].mtxWorld._43);	// ���̏ꏊ (�v���C���[�̉E��̈ʒu)
			
			//�G�ʒu
			D3DXVECTOR3 enemyPosFix = D3DXVECTOR3(pEnemy[nCntEnemy].pos.x, pEnemy[nCntEnemy].pos.y + pEnemy[nCntEnemy].fHeight, pEnemy[nCntEnemy].pos.z);

			//����
			pEnemy[nCntEnemy].bHit = CollisionBoxSphere(&enemyPosFix, &g_WeaponCol3, pEnemy[nCntEnemy].fWidth, pEnemy[nCntEnemy].fHeight, pEnemy[nCntEnemy].fDepth, PLAYER_ATTACK_RADIUS);
			pEnemy[nCntEnemy].bHit = CollisionBoxSphere(&enemyPosFix, &g_WeaponCol1, pEnemy[nCntEnemy].fWidth, pEnemy[nCntEnemy].fHeight, pEnemy[nCntEnemy].fDepth, PLAYER_ATTACK_RADIUS);
			pEnemy[nCntEnemy].bHit = CollisionBoxSphere(&enemyPosFix, &g_WeaponCol2, pEnemy[nCntEnemy].fWidth, pEnemy[nCntEnemy].fHeight, pEnemy[nCntEnemy].fDepth, PLAYER_ATTACK_RADIUS);

			//���肪true�̏ꍇ
			if (pEnemy[nCntEnemy].bHit == true)
			{
				//�v���C���[���U����Ԃ̏ꍇ
				if (pPlayer->motionType == MOTIONTYPE_ATTACK)
				{
					//�v���C���[�����G��Ԃ���Ȃ��ꍇ
					if (pEnemy[nCntEnemy].bInvincible != true)
					{
						//���ݎ��Ԏ擾
						pEnemy[nCntEnemy].dwTimeInv = timeGetTime();

						//�̗͌���
						pEnemy[nCntEnemy].nLife--;

						//�v���C���[����G�ւ̃x�N�g��
						D3DXVECTOR3 vecPtoE = pEnemy[nCntEnemy].pos - pPlayer->pos;
						vecPtoE = D3DXVECTOR3(vecPtoE.x, 10.0f, vecPtoE.z);
						D3DXVec3Normalize(&vecPtoE, &vecPtoE);

						//�m�b�N�o�b�N
						pEnemy[nCntEnemy].move += vecPtoE * ENEMY_KNOCKBACK;

						//���G���Ԃ�
						pEnemy[nCntEnemy].bInvincible = true;
					}
				}
			}
			//�U�����ꂽ�����玞�Ԍo�߂����疳�G����
			if (currentTime - pEnemy[nCntEnemy].dwTimeInv >= ENEMY_INVINCIBLE_TIME)
			{
				pEnemy[nCntEnemy].bInvincible = false;
			}

			//�v���C���[�ƓG�̈ړ������蔻��
			ColPlayerBoxThing(pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].fWidth, pEnemy[nCntEnemy].fDepth);
		}
	}

	//���R���W�����̈ړ�
	g_WeaponCol1 = D3DXVECTOR3(pPlayer->mtxWeaponCol[0]._41, pPlayer->mtxWeaponCol[0]._42, pPlayer->mtxWeaponCol[0]._43);
	g_WeaponCol2 = D3DXVECTOR3(pPlayer->mtxWeaponCol[1]._41, pPlayer->mtxWeaponCol[1]._42, pPlayer->mtxWeaponCol[1]._43);
	g_WeaponCol3 = D3DXVECTOR3(pPlayer->mtxWeaponCol[2]._41, pPlayer->mtxWeaponCol[2]._42, pPlayer->mtxWeaponCol[2]._43);

	MoveVCollision(&g_WeaponCol1, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	MoveVCollision(&g_WeaponCol2, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	MoveVCollision(&g_WeaponCol3, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawCollision(void)
{
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == true)
		{
			D3DXMATRIX mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;			// �}�e���A���ۑ�

			//���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aVCollision[nCntCollision].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aVCollision[nCntCollision].rot.y, g_aVCollision[nCntCollision].rot.x, g_aVCollision[nCntCollision].rot.z);
			D3DXMatrixMultiply(&g_aVCollision[nCntCollision].mtxWorld, &g_aVCollision[nCntCollision].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aVCollision[nCntCollision].pos.x, g_aVCollision[nCntCollision].pos.y, g_aVCollision[nCntCollision].pos.z);
			D3DXMatrixMultiply(&g_aVCollision[nCntCollision].mtxWorld, &g_aVCollision[nCntCollision].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aVCollision[nCntCollision].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&g_aVCollision[nCntCollision].mat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f���p�[�c�̕`��
			g_aVCollision[nCntCollision].pMesh->DrawSubset(0);

			//�}�e���A�������Ƃɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
#endif
}

//-----------------------------------------------------------------------------
// ���R���W�����̍\���̂��擾
//-----------------------------------------------------------------------------
VCollision *GetVCol(void)
{
	return &g_aVCollision[0];
}

//-----------------------------------------------------------------------------
// �����p�̃X�t�B�A��ݒu
//-----------------------------------------------------------------------------
void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nSlices, int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X

	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == false)
		{
			//�X�t�B�A�̃��b�V������
			D3DXCreateSphere(pDevice, fRadius, nSlices, nSlices, &g_aVCollision[nCntCollision].pMesh, NULL);

			//�ʒu�̐ݒ�
			g_aVCollision[nCntCollision].pos = pos;

			//�����̐ݒ�
			g_aVCollision[nCntCollision].rot = rot;

			//�F�̐ݒ�
			g_aVCollision[nCntCollision].mat.Diffuse = col;

			//�ԍ��t��
			g_aVCollision[nCntCollision].nIdx = nIdx;

			//�g�p���Ɉڍs
			g_aVCollision[nCntCollision].bUse = true;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// �����p�̃{�b�N�X��z�u
//-----------------------------------------------------------------------------
void SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, float fDepth, int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X

	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == false)
		{
			//�X�t�B�A�̃��b�V������
			D3DXCreateBox(pDevice, fWidth, fHeight * 2, fDepth, &g_aVCollision[nCntCollision].pMesh, NULL);

			//�ʒu�̐ݒ�
			g_aVCollision[nCntCollision].pos = pos;

			//�����̐ݒ�
			g_aVCollision[nCntCollision].rot = rot;

			//�F�̐ݒ�
			g_aVCollision[nCntCollision].mat.Diffuse = col;

			//�ԍ��t��
			g_aVCollision[nCntCollision].nIdx = nIdx;

			//�g�p���Ɉڍs
			g_aVCollision[nCntCollision].bUse = true;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// �����R���W�����̈ړ����f
//-----------------------------------------------------------------------------
void MoveVCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRot, int nIdx)
{
	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == true && g_aVCollision[nCntCollision].nIdx == nIdx)
		{
			g_aVCollision[nCntCollision].pos = *pPos;

			g_aVCollision[nCntCollision].rot = *pRot;
		}
	}
}

//-----------------------------------------------------------------------------
// ���Ɣ��̓����蔻�� (�c���l���Ȃ�)
//-----------------------------------------------------------------------------
bool CollisionBoxBox(D3DXVECTOR3 *pPosA, D3DXVECTOR3 *pPosB, float fWidthA, float fDepthA, float fWidthB, float fDepthB)
{
	//�E����
	if (pPosA->x - fWidthA < pPosB->x + fWidthB && pPosA->x - fWidthA > pPosB->x - fWidthB &&
		pPosA->z + fDepthA > pPosB->z - fDepthB && pPosA->z - fDepthA < pPosB->z + fDepthB)
	{
		return true;
	}
	//������
	if (pPosA->x + fWidthA > pPosB->x - fWidthB && pPosA->x + fWidthA < pPosB->x + fWidthB &&
		pPosA->z + fDepthA > pPosB->z - fDepthB && pPosA->z - fDepthA < pPosB->z + fDepthB)
	{
		return true;
	}
	//������
	if (pPosA->z - fDepthA < pPosB->z + fDepthB && pPosA->z - fDepthA > pPosB->z - fDepthB &&
		pPosA->x + fWidthA > pPosB->x - fWidthB && pPosA->x - fWidthA < pPosB->x + fWidthB)
	{
		return true;
	}
	//��O����
	if (pPosA->z + fDepthA > pPosB->z - fDepthB && pPosA->z + fDepthA < pPosB->z + fDepthB &&
		pPosA->x + fWidthA > pPosB->x - fWidthB && pPosA->x - fWidthA < pPosB->x + fWidthB)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// ���Ƌ��̓����蔻��
//-----------------------------------------------------------------------------
bool CollisionBoxSphere(D3DXVECTOR3 *pBoxPos, D3DXVECTOR3 *pSpherePos, float fBoxWidth, float fBoxHeight, float fBoxDepth, float fSphereRadius)
{
	D3DXVECTOR3 vtxPos[BOX_VERTICES];	// ���̒��_

	//�e���_�̈ʒu�ݒ�
	vtxPos[0] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z - (fBoxDepth / 2));	// �E��O��
	vtxPos[1] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z + (fBoxDepth / 2));	// �E����
	vtxPos[2] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z - (fBoxDepth / 2));	// ����O��
	vtxPos[3] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z + (fBoxDepth / 2));	// ������
	vtxPos[4] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y, pBoxPos->z - (fBoxDepth / 2));				// �E��O��
	vtxPos[5] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y, pBoxPos->z + (fBoxDepth / 2));				// �E����
	vtxPos[6] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y, pBoxPos->z - (fBoxDepth / 2));				// ����O��
	vtxPos[7] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y, pBoxPos->z + (fBoxDepth / 2));				// ������
	
	for (int nCntVtx = 0; nCntVtx < BOX_VERTICES; nCntVtx++)
	{
		//�e���_���狅�ւ̋��������a�ȓ��������炠�����Ă�
		if (sqrtf((vtxPos[nCntVtx].x - pSpherePos->x) * ((vtxPos[nCntVtx].x) - pSpherePos->x) + (vtxPos[nCntVtx].y - pSpherePos->y) * (vtxPos[nCntVtx].y - pSpherePos->y) + (vtxPos[nCntVtx].z - pSpherePos->z) * (vtxPos[nCntVtx].z - pSpherePos->z)) <= fSphereRadius)
		{
 			return true;
		}
	}

	//�����`�̈�ɓ����Ă�����
if (pSpherePos->x < pBoxPos->x + (fBoxWidth / 2) + fSphereRadius &&
	pSpherePos->x > pBoxPos->x - (fBoxWidth / 2) - fSphereRadius &&
	pSpherePos->z < pBoxPos->z + (fBoxDepth / 2) &&
	pSpherePos->z > pBoxPos->z - (fBoxDepth / 2) &&
	pSpherePos->y < pBoxPos->y + fBoxHeight &&
	pSpherePos->y > pBoxPos->y - fBoxHeight)
{
	return true;
}
if (pSpherePos->x < pBoxPos->x + (fBoxWidth / 2) &&
	pSpherePos->x > pBoxPos->x - (fBoxWidth / 2) &&
	pSpherePos->z < pBoxPos->z + (fBoxDepth / 2) + fSphereRadius &&
	pSpherePos->z > pBoxPos->z - (fBoxDepth / 2) - fSphereRadius &&
	pSpherePos->y < pBoxPos->y + fBoxHeight &&
	pSpherePos->y > pBoxPos->y - fBoxHeight)
{
	return true;
}
if (pSpherePos->x < pBoxPos->x + (fBoxWidth / 2) &&
	pSpherePos->x > pBoxPos->x - (fBoxWidth / 2) &&
	pSpherePos->z < pBoxPos->z + (fBoxDepth / 2) &&
	pSpherePos->z > pBoxPos->z - (fBoxDepth / 2) &&
	pSpherePos->y < pBoxPos->y + fBoxHeight + fSphereRadius &&
	pSpherePos->y > pBoxPos->y - fBoxHeight - fSphereRadius)
{
	return true;
}

return false;
}

/* �v���C���[�ƕ��̏Փ� */
void ColPlayerBoxThing(D3DXVECTOR3 posThing, float fWidthThing, float fDepthThing)
{
	Player *pPlayer = GetPlayer();
	// �����蔻�� 2d �����߂荞�ݖ߂�
	//��
	if (pPlayer->pos.x + PlAYER_WIDTH > posThing.x - fWidthThing &&
		pPlayer->pos.x - PlAYER_WIDTH < posThing.x + fWidthThing &&
		pPlayer->pos.z - PlAYER_WIDTH < posThing.z + fDepthThing)
	{
		if (pPlayer->posOld.z >= posThing.z + fDepthThing &&
			pPlayer->posOld.x + PlAYER_WIDTH >= posThing.x - fWidthThing &&
			pPlayer->posOld.x - PlAYER_WIDTH <= posThing.x + fWidthThing)
		{
			pPlayer->pos.z = posThing.z + fDepthThing + PlAYER_WIDTH;
		}
	}

	//��O
	if (pPlayer->pos.x + PlAYER_WIDTH > posThing.x - fWidthThing &&
		pPlayer->pos.x - PlAYER_WIDTH < posThing.x + fWidthThing &&
		pPlayer->pos.z + PlAYER_WIDTH > posThing.z - fDepthThing)
	{
		if (pPlayer->posOld.z <= posThing.z - fDepthThing &&
			pPlayer->posOld.x + PlAYER_WIDTH >= posThing.x - fWidthThing &&
			pPlayer->posOld.x - PlAYER_WIDTH <= posThing.x + fWidthThing)
		{
			pPlayer->pos.z = posThing.z - fDepthThing - PlAYER_WIDTH;
		}
	}

	//��
	if (pPlayer->pos.z - PlAYER_WIDTH < posThing.z + fDepthThing &&
		pPlayer->pos.z + PlAYER_WIDTH > posThing.z - fDepthThing &&
		pPlayer->pos.x + PlAYER_WIDTH > posThing.x - fWidthThing)
	{
		if (pPlayer->posOld.x <= posThing.x - fWidthThing &&
			pPlayer->posOld.z - PlAYER_WIDTH <= posThing.z + fDepthThing &&
			pPlayer->posOld.z + PlAYER_WIDTH >= posThing.z - fDepthThing)
		{
			pPlayer->pos.x = posThing.x - fWidthThing - PlAYER_WIDTH;
		}
	}

	//�E
	if (pPlayer->pos.z - PlAYER_WIDTH < posThing.z + fDepthThing &&
		pPlayer->pos.z + PlAYER_WIDTH > posThing.z - fDepthThing &&
		pPlayer->pos.x - PlAYER_WIDTH < posThing.x + fWidthThing)
	{
		if (pPlayer->posOld.x >= posThing.x + fWidthThing &&
			pPlayer->posOld.z - PlAYER_WIDTH <= posThing.z + fDepthThing &&
			pPlayer->posOld.z + PlAYER_WIDTH >= posThing.z - fDepthThing)
		{
			pPlayer->pos.x = posThing.x + fWidthThing + PlAYER_WIDTH;
		}
	}

}