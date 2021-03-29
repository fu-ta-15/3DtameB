#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// �{�X�̏��� [boss.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "boss.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "portal.h"
#include "meshfield.h"
#include "collision.h"

#include <stdio.h>

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void LoadXFileBoss(const char* cXFileName, Model *model);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Boss g_Boss;									// �{�X�̏��

CharacterPartsInfo g_partsBoss;	// boss read info
Model g_modelBoss[BOSS_MODEL_PARTS];				// boss model

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//�e�L�X�g����ǂݍ���
	ReadCharacterInfo(&g_partsBoss, "data//TXT//motion_Boss.txt");

	//�ǂݍ��񂾏����g����X�t�@�C���ǂݍ���
	for (int nCntModel = 0; nCntModel < g_partsBoss.nModelNum; nCntModel++) LoadXFileBoss(&g_partsBoss.cModelFileName[nCntModel][0], &g_modelBoss[nCntModel]);

	//�e�p�[�c�̊K�w�\���ݒ�
	for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
	{// Robot000
		g_modelBoss[nCntModel].nNumModel = g_partsBoss.nModelNum;
		g_modelBoss[nCntModel].nIdxModelParent = g_partsBoss.nModelParent[nCntModel];
		g_modelBoss[nCntModel].pos = D3DXVECTOR3(g_partsBoss.fModelPos[nCntModel][0], g_partsBoss.fModelPos[nCntModel][1], g_partsBoss.fModelPos[nCntModel][2]);
		g_modelBoss[nCntModel].rot = D3DXVECTOR3(g_partsBoss.fModelRot[nCntModel][0], g_partsBoss.fModelRot[nCntModel][1], g_partsBoss.fModelRot[nCntModel][2]);
	}

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//�����ݒ�
		g_Boss.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�̏����ݒ�
		g_Boss.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����̏����ݒ�
		g_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ��l�̏����ݒ�
		g_Boss.bUse = false;
		g_Boss.bInvincible = false;
		g_Boss.nLife = ENEMY_HP_MAX;
		g_Boss.nLifeMax = ENEMY_HP_MAX;
		g_Boss.bHit = false;
		g_Boss.bAttack = false;
		g_Boss.dwTimeAtk = NULL;
		g_Boss.dwTimeInv = NULL;
	}
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitBoss(void)
{
	for (int nCnt = 0; nCnt < BOSS_MODEL_PARTS; nCnt++)
	{
		if (g_modelBoss[nCnt].pMeshModel != NULL)
		{//	MESH RELEASE
			g_modelBoss[nCnt].pMeshModel->Release();
			g_modelBoss[nCnt].pMeshModel = NULL;
		}
		if (g_modelBoss[nCnt].pBuffMatModel != NULL)
		{//	BUFFMAT RELEASE
			g_modelBoss[nCnt].pBuffMatModel->Release();
			g_modelBoss[nCnt].pBuffMatModel = NULL;
		}
		for (int nCntTEX = 0; nCntTEX < 10; nCntTEX++)
		{//	TEXTURE RELEASE
			if (g_modelBoss[nCnt].pTexture[nCntTEX] != NULL)
			{
				g_modelBoss[nCnt].pTexture[nCntTEX]->Release();
				g_modelBoss[nCnt].pTexture[nCntTEX] = NULL;
			}
		}
	}

	for (int nCnt = 0; nCnt < g_Boss.aModel[0].nNumModel; nCnt++)
	{
		if (g_Boss.aModel[nCnt].pMeshModel != NULL)
		{//	MESH RELEASE
			g_Boss.aModel[nCnt].pMeshModel->Release();
			g_Boss.aModel[nCnt].pMeshModel = NULL;
		}
		if (g_Boss.aModel[nCnt].pBuffMatModel != NULL)
		{//	BUFFMAT RELEASE
			g_Boss.aModel[nCnt].pBuffMatModel->Release();
			g_Boss.aModel[nCnt].pBuffMatModel = NULL;
		}
		for (int nCntTEX = 0; nCntTEX < 10; nCntTEX++)
		{//	TEXTURE RELEASE
			if (g_Boss.aModel[nCnt].pTexture[nCntTEX] != NULL)
			{
				g_Boss.aModel[nCnt].pTexture[nCntTEX]->Release();
				g_Boss.aModel[nCnt].pTexture[nCntTEX] = NULL;
			}
		}
	}
}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateBoss(void)
{
	StartMotion(SELECTMOTION_BOSS, MOTIONTYPE_BOSS_NEUTRAL, NULL);	// �Ƃ肠�����j���[�g���������Ƃ�

	//�{�X�ƃv���C���[�̈ړ������蔻��
	ColPlayerBoxThing(g_Boss.pos, g_Boss.fWidth, g_Boss.fDepth);
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// �f�o�C�X�擾

	//���{�b�g�^�C�v�̓G�`��
		if (g_Boss.bUse == true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();									// �f�o�C�X�擾
			D3DXMATRIX mtxRot, mtxTrans;												// �v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;														// ���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;															// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL *pMatAlt;														// �ウ�̃}�e���A��

			//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Boss.mtxWorld);

			//�v���C���[�̌������f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Boss.rot.y, g_Boss.rot.x, g_Boss.rot.z);
			D3DXMatrixMultiply(&g_Boss.mtxWorld, &g_Boss.mtxWorld, &mtxRot);

			//�v���C���[�̈ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_Boss.pos.x, g_Boss.pos.y, g_Boss.pos.z);
			D3DXMatrixMultiply(&g_Boss.mtxWorld, &g_Boss.mtxWorld, &mtxTrans);

			//�v���C���[�̃��[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Boss.mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_Boss.aModel[0].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

				//�e�p�[�c�̃��[���h�}�g���b�N�X������
				D3DXMatrixIdentity(&g_Boss.aModel[nCntModel].mtxWorld);

				//�e�p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Boss.aModel[nCntModel].rot.y, g_Boss.aModel[nCntModel].rot.x, g_Boss.aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModel].mtxWorld, &g_Boss.aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�e�p�[�c�̈ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_Boss.aModel[nCntModel].pos.x, g_Boss.aModel[nCntModel].pos.y, g_Boss.aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModel].mtxWorld, &g_Boss.aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
				if (g_Boss.aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_Boss.aModel[g_Boss.aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_Boss.mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
				}

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModel].mtxWorld, &g_Boss.aModel[nCntModel].mtxWorld, &mtxParent);

				//�e�p�[�c�̃��[���h�}�g���b�N�X�ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Boss.aModel[nCntModel].mtxWorld);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Boss.aModel[nCntModel].pBuffMatModel->GetBufferPointer();
				pMatAlt = (D3DXMATERIAL*)g_Boss.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

				//���G��Ԃ����ă��f���̐F��ς���
				if (g_Boss.bInvincible == true)
				{//���G���
					pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_Boss.aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//�}�e���A���ݒ�
						pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_Boss.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
				else if (g_Boss.bInvincible == false)
				{//�ʏ���
					pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_Boss.aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//�}�e���A���ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_Boss.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
}

//-----------------------------------------------------------------------------
// �{�X���̎擾
//-----------------------------------------------------------------------------
Boss *GetBoss(void)
{
	return &g_Boss;
}

//-----------------------------------------------------------------------------
// boss��z�u����
//-----------------------------------------------------------------------------
void SetBoss(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	if (g_Boss.bUse == false)
	{
		//�ʒu���w��
		g_Boss.pos = pos;

		//��ޕt��
		g_Boss.type = type;

		switch (type)
		{
		case ENEMYTYPE_BOSS:
			//�p�[�c����n��
			for (int nCntRobot = 0; nCntRobot < ENEMY_ROBOT_MODELPARTS; nCntRobot++) g_Boss.aModel[nCntRobot] = g_modelBoss[nCntRobot];
			for (int nCnt = 0; nCnt < ENEMY_ROBOT_MODELPARTS; nCnt++)
			{
				g_Boss.DefKey[nCnt] = KeyPosRot(g_modelBoss[nCnt].pos.x, g_modelBoss[nCnt].pos.y, g_modelBoss[nCnt].pos.z, 0, 0, 0);
				g_Boss.aModel[nCnt].nNumModel = g_modelBoss[nCnt].nNumModel;
			}
			g_Boss.fWidth = BOSS_COL_WIDTH;
			g_Boss.fDepth = BOSS_COL_WIDTH;
			g_Boss.fHeight = BOSS_COL_HEIGHT;
			//�����L�[

			break;
		}

		//�g�p���Ɉڍs
		g_Boss.bUse = true;
	}
}


/* X�t�@�C�����烂�f����ǂݍ��ފ֐�*/
void LoadXFileBoss(const char* cXFileName, Model *model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	//X�t�@�C���̓ǂݍ���
	HRESULT hr = D3DXLoadMeshFromX(
		cXFileName,										// �ǂݍ��ރt�@�C����
		D3DXMESH_SYSTEMMEM,								// �Œ�
		pDevice,										// �f�o�C�X
		NULL,											// NULL�Œ�
		&model->pBuffMatModel,							// �}�e���A��
		NULL,											// NULL�Œ�
		&model->nNumMatModel,							// �}�e���A����
		&model->pMeshModel);							// ���b�V��

	//�}�e���A�����ւ̃|�C���^
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)model->pBuffMatModel->GetBufferPointer();

	//�e�N�X�`�����擾
	//for (int nCntMat = 0; nCntMat < (int)model->nNumMatModel; nCntMat++)
	//{
	//	D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &model->pTexture[nCntMat]);
	//}
}