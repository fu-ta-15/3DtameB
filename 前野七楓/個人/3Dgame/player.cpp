//=================================================================================================================
//
// �v���C���[�̏����@�kplayer.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "polygon.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"

//=================================================================================================================
//	���f���\����
//=================================================================================================================
typedef struct
{
	LPD3DXMESH g_pMesh = NULL;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER g_pBuffMat = NULL;			//�}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD g_nNumMat = 0;					//�}�e���A���̐�
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	//int nNumMo
}Model;

//=================================================================================================================
//	�v���C���[�̍\����
//=================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}Player;

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexturePlayer[1] = {};		//�e�N�X�`���ւ̃|�C���^
Player g_Player;									//���f���̏��
Model g_Model;										//���f���̏��
D3DXVECTOR3 g_VtxMinPlayer;							//���f���̍ŏ��l
D3DXVECTOR3 g_VtxMaxPlayer;							//���f���̍ő�l

//*****************************************************************************************************************
//	���f���̏���������
//*****************************************************************************************************************
void InitModel(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("date\\MODEL\\torii00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_pBuffMatPlayer, NULL,
		&g_nNumMatPlayer, &g_pMeshPlayer);

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^
	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());


	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
		}
	}


	//���_�o�b�t�@���b�N
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY,(void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++);
	{
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//���ׂĂ̒��_���r���ă��f���̍ő�ŏ��𔲂��o��

		pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���̃|�C���^
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshPlayer->UnlockVertexBuffer();
}

//*****************************************************************************************************************
//	���f���̏I������
//*****************************************************************************************************************
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//*****************************************************************************************************************
//	�|���S���̍X�V����
//*****************************************************************************************************************
void UpdateModel(void)
{
	//���f���𓮂���
	ControlModel();

	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(D3DXVECTOR3(g_Player.pos.x + 0.0f, g_Player.pos.y + 0.0f, g_Player.pos.y + 0.0f),
			D3DXVECTOR3(sinf(g_Player.rot.y) * 2.0f, 0.0f, cosf(g_Player.rot.y)* 2.0f));
	}
}

//*****************************************************************************************************************
//	�|���S���̕`�揈��
//*****************************************************************************************************************
void DrawModel(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//*****************************************************************************************************************
//	�ݒ菈��
//*****************************************************************************************************************
void ControlModel(void)
{	
	Camera *pCamera; 
	pCamera = GetCamera();

	//���t�g�L�[�������ꂽ�Ƃ�
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.pos.x = g_Player.pos.x - cosf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z + sinf(pCamera->rot.y) * SPEED;

		g_Player.rot.y = (pCamera->rot.y) - D3DX_PI / 2.0f;
		
	}

	//���C�g�L�[�������ꂽ��
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.pos.x = g_Player.pos.x + cosf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z - sinf(pCamera->rot.y) * SPEED;
		g_Player.rot.y = (pCamera->rot.y) + D3DX_PI / 2.0f;

	}

	//�_�E���L�[�������ꂽ��
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Player.pos.x = g_Player.pos.x - sinf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z - cosf(pCamera->rot.y) * SPEED;

		g_Player.rot.y = (pCamera->rot.y) - D3DX_PI;
	}

	//�A�b�v�L�[�������ꂽ��	
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Player.pos.x = g_Player.pos.x + sinf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z + cosf(pCamera->rot.y) * SPEED;

		g_Player.rot.y = (pCamera->rot.y);
	}

}
//*****************************************************************************************************************
//	�v���C���[�̏��
//*****************************************************************************************************************
Model *GetModel(void)
{
	return &g_Model;
}
