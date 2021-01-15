//=================================================================================================================
//
// ���b�V���t�B�[���h�̏����@�kpolygon.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "meshfield.h"
#include "input.h"

//=================================================================================================================
// �O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//�C���f�b�N�X�o�b�t�@
D3DXVECTOR3 g_posMeshfield;			//�ʒu
D3DXVECTOR3 g_rotMeshfield;			//����
D3DXMATRIX g_mtxWorldMeshfield;		//���[���h�}�g���b�N�X


//*****************************************************************************************************************
//	���b�V���t�B�[���h�̏���������
//*****************************************************************************************************************
HRESULT InitMeshfield(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\floor01.jpg", &g_pTextureMeshfield);

	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL)))
	{
		return E_FAIL;
	}
	 
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//�C���f�b�N�X���ւ̃|�C���^
	WORD *pId;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//�C���f�b�N�X�o�b�t�@�����b�N���ԍ����f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pId, 0);

	//�ԍ��f�[�^�̐ݒ�
	pId[0] = 3;
	pId[1] = 0;
	pId[2] = 4;
	pId[3] = 1;
	pId[4] = 5;
	pId[5] = 2;
	pId[6] = 2;
	pId[7] = 6;
	pId[8] = 6;
	pId[9] = 3;
	pId[10] = 7;
	pId[11] = 4;
	pId[12] = 8;
	pId[13] = 5;


	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshField->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W�̐ݒ� (XYZ)
	pVtx[0].pos = D3DXVECTOR3(g_posMeshfield.x - 200.0f, 0.0f, g_posMeshfield.z + 200.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z + 200.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshfield.x + 200.0f, 0.0f, g_posMeshfield.z + 200.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshfield.x - 200.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f,  0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshfield.x + 200.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshfield.x - 200.0f, 0.0f, g_posMeshfield.z - 200.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z - 200.0f);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshfield.x + 200.0f, 0.0f, g_posMeshfield.z - 200.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���[���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	���b�V���t�B�[���h�̏I������
//*****************************************************************************************************************
void UninitMeshfield(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
}

//*****************************************************************************************************************
//	���b�V���t�B�[���h�̍X�V����
//*****************************************************************************************************************
void UpdateMeshfield(void)
{
}

//*****************************************************************************************************************
//	���b�V���t�B�[���h�̕`�揈��
//*****************************************************************************************************************
void DrawMeshfield(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		9,
		0,
		12);
}
