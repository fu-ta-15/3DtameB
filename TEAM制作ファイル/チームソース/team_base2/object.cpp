//-----------------------------------------------------------------------------
//
// �G�̏��� [object.cpp]
// Author: Suzuki Fuut
//
//-----------------------------------------------------------------------------
#include "object.h"
#include "collision.h"
#include <stdio.h>


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_OBJ				(30)
#define MAX_OBJ_TYPE		(OBJECT_TYPE_MAX)
#define MAX_STR				(128)
#define VECTOR_NUM			(3)			


//-----------------------------------------------------------------------------
// �I�u�W�F�N�g���̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	int nObjectNum;										// ���f���̐�	
	int nObjectIdx[MAX_OBJ_TYPE];						// ���f���̔ԍ�
	char cObjectFileName[MAX_OBJ_TYPE][MAX_STR];		// ���f���̃t�@�C����
	char cObjectTextureName[MAX_OBJ_TYPE][MAX_STR];		// �e�N�X�`���̃t�@�C����
	float fObjectPos[MAX_OBJ_TYPE][VECTOR_NUM];			// ���f���̈ʒu(�I�t�Z�b�g)
	float fObjectRot[MAX_OBJ_TYPE][VECTOR_NUM];			// ���f���̌���
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} ObjectInfo;

// �|�C���^
typedef struct
{
	int nObjectNum;				// ���f���̐�	
	int nObjectIdx;				// ���f���̔ԍ�
	char cObjectFileName;		// ���f���̃t�@�C����
	char cObjectTextureName;	// �e�N�X�`���̃t�@�C����
	float fObjectPos;			// ���f���̈ʒu(�I�t�Z�b�g)
	float fObjectRot;			// ���f���̌���
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} pObjectInfo;


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void LoadXFileObj(const char* cXFileName, int nCountModel);
void GetMinMaxVtx(int nIdx);

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Object g_Obj[MAX_OBJ];		// �I�u�W�F�N�g�̏��
ObjectInfo g_ObjInfo;

// �|�C���^
Object  * g_pObj;			// �I�u�W�F�N�g�̏��
pObjectInfo  * g_pObjInfo;


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void InitObject(int nStageNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		//�����ݒ�
		g_Obj[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�̏����ݒ�
		g_Obj[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����̏����ݒ�
		g_Obj[nCntObj].bUse = false;
		g_Obj[nCntObj].Type = OBJECT_TYPE_NULL;
		g_Obj[nCntObj].nIdx = NULL;
	}

	// �����ݒ�   // �|�C���^
	//g_pObj->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�̏����ݒ�
	//g_pObj->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����̏����ݒ�
	//g_pObj->bUse = false;
	//g_pObj->Type = OBJECT_TYPE_NULL;
	//g_pObj->nIdx = NULL;

	
	// �O���t�@�C������̐ݒ�
	SetTextObject(nStageNum);
}


//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitObject(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		//���b�V���j��
		if (g_Obj[nCntObj].pMesh != NULL)
		{
			g_Obj[nCntObj].pMesh->Release();
			g_Obj[nCntObj].pMesh = NULL;
		}

		//�}�e���A���j��
		if (g_Obj[nCntObj].pBuffMat != NULL)
		{
			g_Obj[nCntObj].pBuffMat->Release();
			g_Obj[nCntObj].pBuffMat = NULL;
		}
	}

	free(g_pObj);
}


//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateObject(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (g_Obj[nCntObj].bUse)
		{
			ColPlayerBoxThing(g_Obj[nCntObj].pos, g_Obj[nCntObj].vtxMax.x, g_Obj[nCntObj].vtxMax.z);
		}
	}
}


//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();					// �f�o�C�X�擾

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (g_Obj[nCntObj].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;						// �v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;								// ���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;									// �}�e���A���f�[�^�ւ̃|�C���^
			
			//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Obj[nCntObj].mtxWorld);

			//�v���C���[�̌������f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Obj[nCntObj].rot.y, g_Obj[nCntObj].rot.x, g_Obj[nCntObj].rot.z);
			D3DXMatrixMultiply(&g_Obj[nCntObj].mtxWorld, &g_Obj[nCntObj].mtxWorld, &mtxRot);

			//�v���C���[�̈ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_Obj[nCntObj].pos.x, g_Obj[nCntObj].pos.y, g_Obj[nCntObj].pos.z);
			D3DXMatrixMultiply(&g_Obj[nCntObj].mtxWorld, &g_Obj[nCntObj].mtxWorld, &mtxTrans);

			//�v���C���[�̃��[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Obj[nCntObj].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Obj[nCntObj].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Obj[nCntObj].nNumMat; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Obj[nCntObj].pTexture[nCntMat]);

				//���f���p�[�c�̕`��
				g_Obj[nCntObj].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}



//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̏��
//-----------------------------------------------------------------------------
Object * GetObj(void)
{
	return &g_Obj[0];
}


//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̐ݒu
//-----------------------------------------------------------------------------
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, OBJECT_TYPE type)
{

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (g_Obj[nCntObj].bUse == false)
		{

			//�ʒu���w��
			g_Obj[nCntObj].pos = pos;

			//�������w��
			g_Obj[nCntObj].rot = rot;

			//�ԍ��t��
			g_Obj[nCntObj].nIdx = nCntObj;

			//X�t�@�C���̓ǂݍ���
			LoadXFileObj(&g_ObjInfo.cObjectFileName[type][0], g_Obj[nCntObj].nIdx);

			//���_�̍ő�ŏ��l��T��
			GetMinMaxVtx(nCntObj);

			//�g�p���Ɉڍs
			g_Obj[nCntObj].bUse = true;
			break;
		}
	}
}



//-----------------------------------------------------------------------------
// �e�L�X�g�ł̃I�u�W�F�N�g�z�u
//-----------------------------------------------------------------------------
void SetTextObject(int nStageNum)
{
	char *aStr[128];

	if (nStageNum == 0) aStr[0] = "data\\TXT\\obj_wave1.txt";
	else if (nStageNum == 1) aStr[0] = "data\\TXT\\obj_wave2.txt";

	if (nStageNum != 2)
	{
		// �O���t�@�C���ւ̃|�C���^
		FILE *pFile = fopen(aStr[0], "r");	// �t�@�C���I�[�v��

		char *str;				// ������ǂݍ��ݗp
		int FileSize;			// �t�@�C���̃T�C�Y�ۑ��p
		bool ObjSet = false;	// �ݒu�J�n���}�p
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
					fscanf(pFile, "%s %s", str, &g_ObjInfo.cObjectFileName[nModelType][0]);
					// ���f���̃^�C�v��i�߂�
					nModelType++;
				}
				// ���f���̔z�u�J�n�̍��}
				if (strcmp(str, "MODEL_SET") == 0)
				{
					ObjSet = true;
				}

				while (ObjSet == true)
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
						SetObject(g_ObjInfo.pos, g_ObjInfo.rot, (OBJECT_TYPE)g_ObjInfo.nType);
					}
					if (strcmp(str, "END_MODEL_SET") == 0)
					{// �I�u�W�F�N�g�z�u�I��
						ObjSet = false;
					}
				}
			}
		}
		// �������̊J��
		free(str);
	}
}

void LoadXFileObj(const char * cXFileName, int nCountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			cXFileName,								// �ǂݍ��ރt�@�C����
			D3DXMESH_SYSTEMMEM,						// �Œ�
			pDevice,								// �f�o�C�X
			NULL,									// NULL�Œ�
			&g_Obj[nCountModel].pBuffMat,				// �}�e���A��
			NULL,									// NULL�Œ�
			&g_Obj[nCountModel].nNumMat,				// �}�e���A����
			&g_Obj[nCountModel].pMesh);					// ���b�V��

		//�}�e���A�����ւ̃|�C���^
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_Obj[nCountModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Obj[nCountModel].nNumMat; nCntMat++)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Obj[nCountModel].pTexture[nCntMat]);
		}
}

void GetMinMaxVtx(int nIdx)
{
	int nNumVtx;	// ���_��
	DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	//���_�����擾
	nNumVtx = g_Obj[nIdx].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_Obj[nIdx].pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	g_Obj[nIdx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W���

		//�ő�l�ŏ��l�𔲂��o��
		if (vtx.x < g_Obj[nIdx].vtxMin.x) g_Obj[nIdx].vtxMin.x = vtx.x;	// X�ŏ��l
		if (vtx.y > g_Obj[nIdx].vtxMax.y) g_Obj[nIdx].vtxMax.y = vtx.y;	// Y�ő�l
		if (vtx.y < g_Obj[nIdx].vtxMin.y) g_Obj[nIdx].vtxMin.y = vtx.y;	// Y�ŏ��l
		if (vtx.z > g_Obj[nIdx].vtxMax.z) g_Obj[nIdx].vtxMax.z = vtx.z;	// Z�ő�l
		if (vtx.z < g_Obj[nIdx].vtxMin.z) g_Obj[nIdx].vtxMin.z = vtx.z;	// Z�ŏ��l
		if (vtx.x > g_Obj[nIdx].vtxMax.x) g_Obj[nIdx].vtxMax.x = vtx.x;	// X�ő�l

		pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y�������|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_Obj[nIdx].pMesh->UnlockVertexBuffer();
}