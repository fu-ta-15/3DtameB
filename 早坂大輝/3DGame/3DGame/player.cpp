//=============================================================================
//
// �v���C���[�̏��� [model.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_MODEL	(1.0f)
#define MOVE_BULLET (5.0f)
#define HIT_WALL	(270.0f)
#define MAX_TEX		(10)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH g_pMeshModel = NULL;						//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;				//�}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatModel = 0;							//�}�e���A���̐�
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;			//���f���̍ŏ��A�ő�
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
Player g_player;									//���f�����

int g_nShootCount;									//���˃J�E���g

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
	g_player.boost = 10.0f;
	g_player.nNumModel = MAX_USE_MODEL;

	g_nShootCount = 0;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/robot000a.x",	//���{�b�g�{��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].nNumMat,
		&g_player.aModel[0].pMesh);
		
	D3DXLoadMeshFromX("data/MODEL/drone.x",		//�h���[��
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,
		NULL,
		&g_player.aModel[1].nNumMat,
		&g_player.aModel[1].pMesh);

	//�e�p�[�c�̊K�w�\���̐ݒ�
	g_player.aModel[0].nIdxModelParent = -1;	//�e�̃C���f�b�N�X��ݒ�
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIdxModelParent = 0;		//�e�̃C���f�b�N�X��ݒ�
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 60.0f, 5.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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


			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//�e�N�X�`��
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntMat].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/machine000.png", &g_apTextureModel[nCntMat]);
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

	//���˃J�E���g��i�߂�
	g_nShootCount++;

	//�ʒu�̍X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;

	//�ړ��ʂ̌���
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.2f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.2f;

	//�G�t�F�N�g
	//SetEffect(D3DXVECTOR3(g_model[0].pos.x, g_model[0].pos.y + 25.0f, g_model[0].pos.z),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 0.6f, 0.2f, 1.0f),
	//	1.0f,
	//	5.0f,
	//	0.1f);

	//�d��
	if (g_player.pos.y > 0.0f)
	{
		g_player.move.y -= 0.3f;
	}

	//�n�ʂ߂荞�ݖ߂�
	if (g_player.pos.y < 0.0f)
	{
		g_player.pos.y = 0.0f;
	}

	//�u�[�X�g�c�ʂ̒ǉ�
	if (g_player.pos.y == 0.0f)
	{
		if (g_player.boost < 100)
		{
			g_player.boost++;
		}
	}
	//�u�[�X�g(���V)
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		if (g_player.boost > 0)
		{
			g_player.move.y += 1;
			g_player.boost -= 2;
		}
	}

	// ���f���̈ړ�
	if (GetKeyboardPress(DIK_UP) == true)
	{
		if (GetKeyboardPress(DIK_LEFT) == true)
		{// �������
			g_player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * MOVE_MODEL;
			g_player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
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
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		if (GetKeyboardPress(DIK_LEFT) == true)
		{// ��������
			g_player.move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
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
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{// ������
		g_player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL;
		g_player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
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

	//�e�̔���
	if (GetKeyboardPress(DIK_G) == true)
	{
		if ((g_nShootCount % 15) == 0)
		{
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 45.0f, g_player.pos.z),
				D3DXVECTOR3(sinf(g_player.rot.y) * -11.0f, 0.0f, cosf(g_player.rot.y) * -10.0f),
				30.0f, 30.0f);
		}
	}

	// �e�̒Ǐ]
	SetPositionShadow(g_player.nShadow, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));

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

	//���Z�b�g
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
			mtxParent = g_player.aModel[0].mtxWorld;
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

//-----------------------------------------------------------------
// ���f���̈ʒu���̎擾
//-----------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;
}