#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// �G�̏��� [enemy.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "portal.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void MoveEnemy(float fMoveAngleDegree, float fMoveSpeed);
void LoadXFileEnemy(const char* cXFileName, PlayerModel *model);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Enemy g_aEnemy[ENEMY_AMOUNT_MAX];	// �G�̏��
int g_nEnemyAlive = 0;				// �G�̐�����

CharacterPartsInfo g_partsRobot;	// �ǂݍ��񂾃p�[�c���(���{�b�g)
KEY g_defKeyRobot[ENEMY_ROBOT_MODELPARTS];					//

PlayerModel g_modelSnake;			// �ւ̃��f�����
PlayerModel g_modelRobot[ENEMY_ROBOT_MODELPARTS];			// ���{�b�g�̃��f�����

bool g_bEliminated;					// �S�ł�����
DWORD g_dwTimeTransition;			// ��ʑJ�ڎ��Ԍv�Z

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//X�t�@�C���̓ǂݍ���
	LoadXFileEnemy("data\\MODEL\\snake.x", &g_modelSnake);

	//�e�L�X�g����ǂݍ���
	ReadCharacterInfo(&g_partsRobot, "model_robot.txt");

	//�ǂݍ��񂾏����g����X�t�@�C���ǂݍ���
	for (int nCntModel = 0; nCntModel < g_partsRobot.nModelNum; nCntModel++)
	{
		LoadXFileEnemy(&g_partsRobot.cModelFileName[nCntModel][0], &g_modelRobot[nCntModel]);
	}

	//�e�p�[�c�̊K�w�\���ݒ�
	for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
	{
		g_modelRobot[nCntModel].nNumModel = g_partsRobot.nModelNum;
		g_modelRobot[nCntModel].nIdxModelParent = g_partsRobot.nModelParent[nCntModel];
		g_modelRobot[nCntModel].pos = D3DXVECTOR3(g_partsRobot.fModelPos[nCntModel][0], g_partsRobot.fModelPos[nCntModel][1], g_partsRobot.fModelPos[nCntModel][2]);
		g_modelRobot[nCntModel].rot = D3DXVECTOR3(g_partsRobot.fModelRot[nCntModel][0], g_partsRobot.fModelRot[nCntModel][1], g_partsRobot.fModelRot[nCntModel][2]);
	}

	//�����L�[
	for (int nCnt = 0; nCnt < ENEMY_ROBOT_MODELPARTS; nCnt++)
	{
		g_defKeyRobot[nCnt] = KeyPosRot(g_modelRobot[nCnt].pos.x, g_modelRobot[nCnt].pos.y, g_modelRobot[nCnt].pos.z, 0, 0, 0);
	}

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//�����ݒ�
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�̏����ݒ�
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����̏����ݒ�
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].bInvincible = false;
		g_aEnemy[nCntEnemy].nLife = ENEMY_HP_MAX;
		g_aEnemy[nCntEnemy].nLifeMax = ENEMY_HP_MAX;
		g_aEnemy[nCntEnemy].bHit = false;
		g_aEnemy[nCntEnemy].bAttack = false;
		g_aEnemy[nCntEnemy].dwTimeAtk = NULL;
		g_aEnemy[nCntEnemy].dwTimeInv = NULL;
		g_aEnemy[nCntEnemy].nIdx = NULL;
	}
	g_nEnemyAlive = 0;
	g_dwTimeTransition = NULL;
	g_bEliminated = false;

	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 250.0f), ENEMYTYPE_ROBOT);
	SetEnemy(D3DXVECTOR3(50.0f, 0.0f, 250.0f), ENEMYTYPE_SNAKE);
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitEnemy(void)
{
	//�ւ̃}�e���A���J��
	if (g_modelSnake.pBuffMatModel != NULL)
	{
		g_modelSnake.pBuffMatModel->Release();
		g_modelSnake.pBuffMatModel = NULL;
	}
	//�ւ̃��b�V���J��
	if (g_modelSnake.pMeshModel != NULL)
	{
		g_modelSnake.pMeshModel->Release();
		g_modelSnake.pMeshModel = NULL;
	}
	//�ւ̃e�N�X�`���J��
	for (int nCntTex = 0; nCntTex < 10; nCntTex++)
	{
		if (g_modelSnake.pTexture[nCntTex] != NULL)
		{
			g_modelSnake.pTexture[nCntTex]->Release();
			g_modelSnake.pTexture[nCntTex] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateEnemy(void)
{
	DWORD dwCurrentTime = timeGetTime();	// ���ݎ���

	//�g�p���̓G��T��
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			Player *pPlayer = GetPlayer();	// �v���C���[�̎擾

			//�ړ��ʒǉ�
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			//�ړ��ʌ���
			g_aEnemy[nCntEnemy].move.x = g_aEnemy[nCntEnemy].move.x * 0.2f;
			g_aEnemy[nCntEnemy].move.z = g_aEnemy[nCntEnemy].move.z * 0.2f;

			//�d��
			g_aEnemy[nCntEnemy].move.y -= ENEMY_FALLSPEED;

			if (g_aEnemy[nCntEnemy].pos.y < 0) g_aEnemy[nCntEnemy].pos.y = 0;

			//�̗͂Ȃ��Ȃ�����
			if (g_aEnemy[nCntEnemy].nLife <= 0)
			{
				//�g�p�󋵂�؂�ւ���
				g_aEnemy[nCntEnemy].bUse = false;

				//�����������Z
				g_nEnemyAlive--;
			}

			//���[�V�����Ǘ�
			if (g_aEnemy[nCntEnemy].move.x != 0.0f || g_aEnemy[nCntEnemy].move.z != 0.0f)
			{
				StartMotion(SELECTMOTION_ENEMY, MOTIONTYPE_WALK, nCntEnemy);
			}
			else
			{
				StartMotion(SELECTMOTION_ENEMY, MOTIONTYPE_NEUTRAL, nCntEnemy);
			}

			//�v���C���[�Ƃ̋���
			float fDistanceToPlayer = sqrtf((pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x) * ((pPlayer->pos.x) - g_aEnemy[nCntEnemy].pos.x) + (pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z) * (pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z));

			//���������m�͈͈ȓ���������
			if (fDistanceToPlayer <= ENEMY_DETECT_RADIUS)
			{
				//�v���C���[�Ɍ������P�ʃx�N�g��
				D3DXVECTOR3 vecToPlayer = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
				D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

				//�ړ������Z
				g_aEnemy[nCntEnemy].move += vecToPlayer * ENEMY_MOVESPEED;

				//�v���C���[�ւ̃��W�A���p
				float fRadianToPlayer = atan2f(g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x, g_aEnemy[nCntEnemy].pos.z - pPlayer->pos.z);
				g_aEnemy[nCntEnemy].rot.y = fRadianToPlayer;
			}

			//�������U���͈͓���������
			if (fDistanceToPlayer <= ENEMY_ATTACK_RADIUS)
			{
				//���łɍU�����Ă��Ȃ��ꍇ
				if (g_aEnemy[nCntEnemy].bAttack != true)
				{
					//�v���C���[�̖��G���Ԃ���Ȃ��ꍇ
					if (pPlayer->bInvincible != true)
					{
						//���ݎ��Ԏ擾�i���G���Ԍv�Z�j
						g_aEnemy[nCntEnemy].dwTimeAtk = timeGetTime();

						//���ݎ��Ԏ擾�i�U��CT�v�Z�j
						pPlayer->dwTime = timeGetTime();

						//�̗͌���
						pPlayer->nLife--;

						//�G���玩���Ɍ������x�N�g��
						D3DXVECTOR3 vecEnemyToPlayer = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
						D3DXVec3Normalize(&vecEnemyToPlayer, &vecEnemyToPlayer);

						//�m�b�N�o�b�N
						pPlayer->move += vecEnemyToPlayer * ENEMY_KNOCKBACK;
						pPlayer->move.y += 1.0f;

						//���G�ɂȂ�
						pPlayer->bInvincible = true;

						//�G���U���N�[���^�C���ɓ���
						g_aEnemy[nCntEnemy].bAttack = true;
					}
				}
			}

			//���Ԍo�߂ōU��CT����
			if (dwCurrentTime - g_aEnemy[nCntEnemy].dwTimeAtk >= ENEMY_ATTACK_COOLTIME)
			{
				//CT����
				g_aEnemy[nCntEnemy].bAttack = false;
			}
			
			//�G���S�ł�����
			if (g_nEnemyAlive <= 0)
			{
				//�|�[�^�����N��
				ActivatePortal(true, true);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// �f�o�C�X�擾

	//�փ^�C�v�̓G�`��
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].type == ENEMYTYPE_SNAKE)
		{
			D3DXMATRIX mtxRot, mtxTrans;												// �v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;														// ���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;															// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL *pMatAlt;														// �ウ�̃}�e���A��

			//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//�v���C���[�̌������f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//�v���C���[�̈ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//�v���C���[�̃��[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_modelSnake.pBuffMatModel->GetBufferPointer();
			pMatAlt = (D3DXMATERIAL*)g_modelSnake.pBuffMatModel->GetBufferPointer();

			//���G��Ԃ����ă��f���̐F��ς���
			if (g_aEnemy[nCntEnemy].bInvincible == true)
			{//���G���
				pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				for (int nCntMat = 0; nCntMat < (int)g_modelSnake.nNumMatModel; nCntMat++)
				{
					//�}�e���A���ݒ�
					pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_modelSnake.pTexture[nCntMat]);

					//���f���p�[�c�̕`��
					g_modelSnake.pMeshModel->DrawSubset(nCntMat);
				}
			}
			else if (g_aEnemy[nCntEnemy].bInvincible == false)
			{//�ʏ���
				pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
				for (int nCntMat = 0; nCntMat < (int)g_modelSnake.nNumMatModel; nCntMat++)
				{
					//�}�e���A���ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_modelSnake.pTexture[nCntMat]);

					//���f���p�[�c�̕`��
					g_modelSnake.pMeshModel->DrawSubset(nCntMat);
				}
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

	//���{�b�g�^�C�v�̓G�`��
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].type == ENEMYTYPE_ROBOT)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();									// �f�o�C�X�擾
			D3DXMATRIX mtxRot, mtxTrans;												// �v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;														// ���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;															// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL *pMatAlt;														// �ウ�̃}�e���A��

			//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//�v���C���[�̌������f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//�v���C���[�̈ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//�v���C���[�̃��[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

				//�e�p�[�c�̃��[���h�}�g���b�N�X������
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//�e�p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�e�p�[�c�̈ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
				}

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//�e�p�[�c�̃��[���h�}�g���b�N�X�ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMatModel->GetBufferPointer();
				pMatAlt = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMatModel->GetBufferPointer();

				//���G��Ԃ����ă��f���̐F��ς���
				if (g_aEnemy[nCntEnemy].bInvincible == true)
				{//���G���
					pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//�}�e���A���ݒ�
						pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_aEnemy[nCntEnemy].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
				else if (g_aEnemy[nCntEnemy].bInvincible == false)
				{//�ʏ���
					pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//�}�e���A���ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_aEnemy[nCntEnemy].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
			}


			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------------------
// �v���C���[�̏����擾
//-----------------------------------------------------------------------------
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//-----------------------------------------------------------------------------
// �p�[�c�����擾
//-----------------------------------------------------------------------------
PlayerModel *GetEnemyModelParts(ENEMYTYPE type)
{
	switch (type)
	{
	case ENEMYTYPE_SNAKE:
		return &g_modelSnake;
		break;

	case ENEMYTYPE_ROBOT:
		return &g_modelRobot[0];
		break;

	default:
		return NULL;
		break;
	}
}

//-----------------------------------------------------------------------------
// �G��z�u����
//-----------------------------------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�ʒu���w��
			g_aEnemy[nCntEnemy].pos = pos;

			//�ԍ��t��
			g_aEnemy[nCntEnemy].nIdx = nCntEnemy;

			//��ޕt��
			g_aEnemy[nCntEnemy].type = type;

			//�p�[�c����n��
			switch (type)
			{
			case ENEMYTYPE_SNAKE:
				break;

			case ENEMYTYPE_ROBOT:
				for (int nCntRobot = 0; nCntRobot < ENEMY_ROBOT_MODELPARTS; nCntRobot++)
				{
					g_aEnemy[nCntEnemy].aModel[nCntRobot] = g_modelRobot[nCntRobot];
				}
				break;

			default:
				break;
			}

			//�������ɉ��Z
			g_nEnemyAlive++;

			//�g�p���Ɉڍs
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}
}

/* ���f�����ړ�������֐� */
void MoveEnemy(float fMoveAngleDegree, float fMoveSpeed)
{
	/*Camera *pCamera = GetCamera();	// �J�����̏��擾

	g_enemy.pos.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_enemy.pos.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_enemy.rotDest.y = pCamera->rot.y + D3DXToRadian(fMoveAngleDegree) + D3DX_PI;*/
}

/* X�t�@�C�����烂�f����ǂݍ��ފ֐�*/
void LoadXFileEnemy(const char* cXFileName, PlayerModel *model)
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

	if (hr != S_OK)
	{
		Sleep(10);
	}
	//�}�e���A�����ւ̃|�C���^
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)model->pBuffMatModel->GetBufferPointer();

	//�e�N�X�`�����擾
	for (int nCntMat = 0; nCntMat < (int)model->nNumMatModel; nCntMat++)
	{
		D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &model->pTexture[nCntMat]);
	}
}