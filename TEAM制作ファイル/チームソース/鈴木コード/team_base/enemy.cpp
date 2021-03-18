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
#define MAX_OBJ				(30)
#define MAX_ENEMY_TYPE		(ENEMYTYPE_MAX)
#define MAX_STR				(128)
#define VECTOR_NUM			(3)			


//-----------------------------------------------------------------------------
// �I�u�W�F�N�g���̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	int nEnemyNum;										// ���f���̐�	
	int nEnemyIdx[MAX_ENEMY_TYPE];						// ���f���̔ԍ�
	char cEnemyFileName[MAX_ENEMY_TYPE][MAX_STR];		// ���f���̃t�@�C����
	char cEnemyTextureName[MAX_ENEMY_TYPE][MAX_STR];		// �e�N�X�`���̃t�@�C����
	float fEnemyPos[MAX_ENEMY_TYPE][VECTOR_NUM];			// ���f���̈ʒu(�I�t�Z�b�g)
	float fEnemyRot[MAX_ENEMY_TYPE][VECTOR_NUM];			// ���f���̌���
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} EnemyInfo;


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void LoadXFileEnemy(const char* cXFileName, Model *model);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Enemy g_aEnemy[ENEMY_AMOUNT_MAX];				// �G�̏��
int g_nEnemyAlive = 0;							// �G�̐�����

CharacterPartsInfo g_partsRobot;				// �ǂݍ��񂾃p�[�c���(���{�b�g)
KEY g_defKeyRobot[ENEMY_ROBOT_MODELPARTS];		// 

Model g_modelRobot[ENEMY_ROBOT_MODELPARTS];		// ���{�b�g�̃��f�����

bool g_bEliminated;								// �S�ł�����
DWORD g_dwTimeTransition;						// ��ʑJ�ڎ��Ԍv�Z

EnemyInfo g_ObjInfo;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//�e�L�X�g����ǂݍ���
	ReadCharacterInfo(&g_partsRobot, "data//TXT//motion_kogata.txt");


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
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitEnemy(void)
{
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
Model *GetEnemyModelParts(ENEMYTYPE type)
{
	switch (type)
	{
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

void SetTextEnemy(void)
{
	// �O���t�@�C���ւ̃|�C���^
	FILE *pFile = fopen("data\\TXT\\enemy.txt", "r");	// �t�@�C���I�[�v��

	char *str;				// ������ǂݍ��ݗp
	int FileSize;			// �t�@�C���̃T�C�Y�ۑ��p
	bool EnemySet = false;	// �ݒu�J�n���}�p
	int nModelType = 1;		// ���f���̃^�C�v�𑶗p

	// �t�@�C���̒��̍Ō�܂ł̒������擾
	fseek(pFile, 0, SEEK_END);
	FileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// �������̊m��
	str = (char*)malloc(sizeof(char) * FileSize);

	// �������̏�����
	memset(str, NULL, sizeof(char) * FileSize);

	// �I�[�v�������̂��m�F
	if (pFile == NULL)
	{// �J���Ȃ�������
		printf("�t�@�C�����J���܂���ł����B");
	}
	else
	{// �J������
	 // �ǂݍ��ݏI���̕������ǂݍ��ނ܂�
		while (strcmp(str, "END_SCRIPT") != 0)
		{
			// �e�L�X�g�t�@�C���̓ǂݍ���
			fscanf(pFile, "%s", str);

			if (strcmp(str, "MODEL_NAME") == 0)
			{// ���f�������^�C�v���Ƃɕۑ�
			 // �e�L�X�g�t�@�C���̓ǂݍ���
				fscanf(pFile, "%s %s", str, &g_ObjInfo.cEnemyFileName[nModelType][0]);
				// ���f���̃^�C�v��i�߂�
				nModelType++;
			}
			// ���f���̔z�u�J�n�̍��}
			if (strcmp(str, "MODEL_SET") == 0)
			{
				EnemySet = true;
			}

			while (EnemySet == true)
			{
				// �e�L�X�g�t�@�C���̓ǂݍ���
				fscanf(pFile, "%s", str);
				// ���f�������^�C�v���Ƃɕۑ�
				if (strcmp(str, "TYPE") == 0) fscanf(pFile, "%s %d", str, &g_ObjInfo.nType);

				// �����ƈʒu���擾
				if (strcmp(str, "POS") == 0)
				{
					// "��"��ǂݍ���
					fscanf(pFile, "%s", str);
					// ���l��ǂݍ���
					fscanf(pFile, "%f %f %f", &g_ObjInfo.pos.x, &g_ObjInfo.pos.y, &g_ObjInfo.pos.z);
				}
				if (strcmp(str, "ROT") == 0)
				{
					// "��"��ǂݍ���
					fscanf(pFile, "%s", str);
					// ���l��ǂݍ���
					fscanf(pFile, "%f %f %f", &g_ObjInfo.rot.x, &g_ObjInfo.rot.y, &g_ObjInfo.rot.z);

				}
				if (strcmp(str, "SET") == 0)
				{// �I�u�W�F�N�g�̐ݒu
					//SetObject(g_ObjInfo.pos, g_ObjInfo.rot, (OBJECT_TYPE)g_ObjInfo.nType);
				}
				if (strcmp(str, "END_MODEL_SET") == 0)
				{// �I�u�W�F�N�g�z�u�I��
					EnemySet = false;
				}
			}
		}
	}
	// �������̊J��
	free(str);
}


/* X�t�@�C�����烂�f����ǂݍ��ފ֐�*/
void LoadXFileEnemy(const char* cXFileName, Model *model)
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
	for (int nCntMat = 0; nCntMat < (int)model->nNumMatModel; nCntMat++)
	{
		D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &model->pTexture[nCntMat]);
	}
}