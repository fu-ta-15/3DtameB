////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ���e�I���C�g�̏��� [meteorite.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/25
//
////////////////////////////////////////////////////////////////////////////////
#include "meteorite.h"
#include "Input.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_MODEL (8)

////////////////////////////////////////////////////////////////////////////////
//���f���̍\����
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	LPD3DXMESH pMesh;			//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBufferMat;	//�}�e���A���ւ̃|�C���^
	DWORD nNumMat;				//�}�e���A���̐�
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X
} MODEL;

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̍\����
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	MODEL aModel[MAX_MODEL];	//���f��(�p�[�c)
	int nNumModel;				//���f��(�p�[�c)��
} METEORITE;

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
METEORITE g_Meteorite;	//覐�

						////////////////////////////////////////////////////////////////////////////////
						//����������
						////////////////////////////////////////////////////////////////////////////////
void InitMeteorite(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/Model/inseki0.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[0].pBufferMat, NULL, &g_Meteorite.aModel[0].nNumMat, &g_Meteorite.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[1].pBufferMat, NULL, &g_Meteorite.aModel[1].nNumMat, &g_Meteorite.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[2].pBufferMat, NULL, &g_Meteorite.aModel[2].nNumMat, &g_Meteorite.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki3.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[3].pBufferMat, NULL, &g_Meteorite.aModel[3].nNumMat, &g_Meteorite.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki4.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[4].pBufferMat, NULL, &g_Meteorite.aModel[4].nNumMat, &g_Meteorite.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki5.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[5].pBufferMat, NULL, &g_Meteorite.aModel[5].nNumMat, &g_Meteorite.aModel[5].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki6.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[6].pBufferMat, NULL, &g_Meteorite.aModel[6].nNumMat, &g_Meteorite.aModel[6].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki7.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[7].pBufferMat, NULL, &g_Meteorite.aModel[7].nNumMat, &g_Meteorite.aModel[7].pMesh);

	g_Meteorite.nNumModel = MAX_MODEL;

	//�e�p�[�c�̊K�w�\���ݒ�
	g_Meteorite.aModel[0].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[1].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[2].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[3].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[4].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[5].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[6].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[6].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[7].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[8].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.aModel[9].nIdxModelParent = -1;						//�e���f���̃C���f�b�N�X��ݒ�
	g_Meteorite.aModel[9].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Meteorite.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Meteorite.pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);				//�v���C���[�̈ʒu�̏����ݒ�
	g_Meteorite.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�v���C���[�̌����̏����ݒ�

}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitMeteorite(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Meteorite.aModel[nCntModel].pMesh != NULL)
		{
			g_Meteorite.aModel[nCntModel].pMesh->Release();	//�j��
			g_Meteorite.aModel[nCntModel].pMesh = NULL;		//������
		}

		if (g_Meteorite.aModel[nCntModel].pBufferMat != NULL)
		{
			g_Meteorite.aModel[nCntModel].pBufferMat->Release();	//�j��
			g_Meteorite.aModel[nCntModel].pBufferMat = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateMeteorite(void)
{
	static bool bBakusan = false;

	if (GetkeyboardTrigger(DIK_RETURN) == true)
	{
		bBakusan = true;
	}

	if (bBakusan == true)
	{
		g_Meteorite.aModel[0].pos.x -= 10;
		g_Meteorite.aModel[0].pos.y += 10;
		g_Meteorite.aModel[0].pos.z += 10;
		g_Meteorite.aModel[1].pos.x += 10;
		g_Meteorite.aModel[1].pos.y += 10;
		g_Meteorite.aModel[1].pos.z += 10;
		g_Meteorite.aModel[2].pos.x += 10;
		g_Meteorite.aModel[2].pos.y -= 10;
		g_Meteorite.aModel[2].pos.z -= 10;
		g_Meteorite.aModel[3].pos.x -= 10;
		g_Meteorite.aModel[3].pos.y += 10;
		g_Meteorite.aModel[3].pos.z -= 10;
		g_Meteorite.aModel[4].pos.x -= 10;
		g_Meteorite.aModel[4].pos.y -= 10;
		g_Meteorite.aModel[4].pos.z += 10;
		g_Meteorite.aModel[5].pos.x += 10;
		g_Meteorite.aModel[5].pos.y -= 10;
		g_Meteorite.aModel[5].pos.z += 10;
		g_Meteorite.aModel[6].pos.x -= 10;
		g_Meteorite.aModel[6].pos.y -= 10;
		g_Meteorite.aModel[6].pos.z -= 10;
		g_Meteorite.aModel[7].pos.x += 10;
		g_Meteorite.aModel[7].pos.y += 10;
		g_Meteorite.aModel[7].pos.z -= 10;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawMeteorite(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

												//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Meteorite.mtxWorld);

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meteorite.rot.y, g_Meteorite.rot.x, g_Meteorite.rot.z);
	D3DXMatrixMultiply(&g_Meteorite.mtxWorld, &g_Meteorite.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Meteorite.pos.x, g_Meteorite.pos.y, g_Meteorite.pos.z);
	D3DXMatrixMultiply(&g_Meteorite.mtxWorld, &g_Meteorite.mtxWorld, &mtxTrans);

	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Meteorite.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Meteorite.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

												//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Meteorite.aModel[nCntModel].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meteorite.aModel[nCntModel].rot.y, g_Meteorite.aModel[nCntModel].rot.x, g_Meteorite.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Meteorite.aModel[nCntModel].mtxWorld, &g_Meteorite.aModel[nCntModel].mtxWorld, &mtxRot);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Meteorite.aModel[nCntModel].pos.x, g_Meteorite.aModel[nCntModel].pos.y, g_Meteorite.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Meteorite.aModel[nCntModel].mtxWorld, &g_Meteorite.aModel[nCntModel].mtxWorld, &mtxTrans);

		//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_Meteorite.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Meteorite.aModel[g_Meteorite.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Meteorite.mtxWorld;	//�v���C���[�̃}�g���b�N�X��ݒ�
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Meteorite.aModel[nCntModel].mtxWorld, &g_Meteorite.aModel[nCntModel].mtxWorld, &mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Meteorite.aModel[nCntModel].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL *)g_Meteorite.aModel[nCntModel].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Meteorite.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f��(�p�[�c)�̕`��
			g_Meteorite.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}