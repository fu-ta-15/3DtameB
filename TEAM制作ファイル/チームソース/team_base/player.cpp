//=============================================================================
//
// �v���C���[�̏��� [model.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_MODEL	(1.0f)
#define MOVE_BULLET (5.0f)
#define HIT_WALL	(390.0f)
#define MAX_TEX		(10)

#define VTX_MINP	(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// �����_�ŏ��l
#define	VTX_MAXP	(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// �����_�ő�l

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH g_pMeshModel = NULL;						//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;				//�}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatModel = 0;							//�}�e���A���̐�
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxPlayer;			//���f���̍ŏ��A�ő�
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
Player g_player;									//���f�����

D3DXVECTOR3 aCollisionPos[2];						//�����蔻�胉�C��

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̍\���̂̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.boost = 200.0f;
	g_player.nNumModel = MAX_USE_MODEL;

	//�ϐ�������
	g_vtxMinPlayer = VTX_MINP;
	g_vtxMaxPlayer = VTX_MAXP;

	aCollisionPos[0] = D3DXVECTOR3(-200, 0, 200);
	aCollisionPos[1] = D3DXVECTOR3(200, 0, 200);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/healdrone.x",	//��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].nNumMat,
		&g_player.aModel[0].pMesh);

	//�e�p�[�c�̊K�w�\���̐ݒ�
	g_player.aModel[0].nIdxModelParent = -1;	//�e�̃C���f�b�N�X��ݒ�
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);	//�ʒu
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

													//�ϐ��錾
	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//���_�����擾
		nNumVtx = g_player.aModel[nCntModel].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//���_���̔����o��
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//�S�Ă̒��_���r�����f���̍ŏ��l�A�ő�l�𔲂��o��
			// �e���W�̍ő�l�̔�r
			if (g_vtxMaxPlayer.x < vtx.x)
			{
				g_vtxMaxPlayer.x = vtx.x;
			}
			if (g_vtxMaxPlayer.y < vtx.y)
			{
				g_vtxMaxPlayer.y = vtx.y;
			}
			if (g_vtxMaxPlayer.z < vtx.z)
			{
				g_vtxMaxPlayer.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (g_vtxMinPlayer.x > vtx.x)
			{
				g_vtxMinPlayer.x = vtx.x;
			}
			if (g_vtxMinPlayer.y > vtx.y)
			{
				g_vtxMinPlayer.y = vtx.y;
			}
			if (g_vtxMinPlayer.z > vtx.z)
			{
				g_vtxMinPlayer.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//�e�N�X�`��
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntMat].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
//				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
			}
		}

		//���_�o�b�t�@���A�����b�N
		g_player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_USE_MODEL; nCntModel++)
	{
		//���b�V���̔j��
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}
	}

	//�e�N�X�`���̊J��
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (g_apTextureModel[nCntMat] != NULL)
		{
			g_apTextureModel[nCntMat]->Release();
			g_apTextureModel[nCntMat] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	//�ʒu�̍X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;

	//�ړ��ʂ̌���
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.2f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.2f;


	//�d��
	if (g_player.pos.y > 0.0f)
	{
		g_player.move.y -= 0.5f;
	}

	//�n�ʂ߂荞�ݖ߂�
	if (g_player.pos.y < 0.0f)
	{
		g_player.pos.y = 0.0f;
	}


	// ���f���̈ړ�
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{// �������
			g_player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * MOVE_MODEL;
			g_player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �E�����
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * MOVE_MODEL;
			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// �����
			g_player.move.x += sinf(pCamera->rot.y) * MOVE_MODEL;
			g_player.move.z += cosf(pCamera->rot.y) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{// ��������
			g_player.move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �E������
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / -4;
		}
		else
		{// ������
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * MOVE_MODEL;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{// ������
		g_player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL;
		g_player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{// �E����
		g_player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL;
		g_player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / -2);
	}


	//���f���̌���
	if (GetKeyboardPress(DIK_LSHIFT) == true)	//���V�t�g��������
	{
		g_player.rotDest.y -= D3DX_PI / 18;

	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)	//�E�V�t�g��������
	{
		g_player.rotDest.y += D3DX_PI / 18;
	}

	// �ړI�̉�]�p�̏��
	if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}


	//�ǂ̐ݒ�
	if (g_player.pos.x < -HIT_WALL)
	{
		//���[
		g_player.pos.x = -HIT_WALL;
	}
	if (g_player.pos.x > HIT_WALL)
	{
		//�E�[
		g_player.pos.x = HIT_WALL;
	}
	if (g_player.pos.z > HIT_WALL)
	{
		//��
		g_player.pos.z = HIT_WALL;
	}
	if (g_player.pos.z < -HIT_WALL)
	{
		//��O
		g_player.pos.z = -HIT_WALL;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

												//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;	//�v���C���[�̃}�g���b�N�X��ݒ�
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
			&g_player.aModel[nCntModel].mtxWorld,
			&mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

			//���f���̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���f���̈ʒu���̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}