////=========================================================================================================================
////
//// ���f�� [model.cpp]
//// Author:Katano Hiroya
////
////=========================================================================================================================
//#include "model.h"
//#include "input.h"
//#include "camera.h"
//#include "bullet.h"
//
////
//// �}�N����`
////
//#define MAX_MODEL (2)		// ���f���̐�
//#define MODEL_SPD (2.0f)	// ���f���̈ړ���
//#define SPD_DECAY (0.4f)	// �ړ��ʂ̌����W��
//
////
//// �O���[�o���ϐ�
////
////LPD3DXMESH g_pMeshModel = NULL;					// ���b�V��(���_���)�ւ̃|�C���^
////LPD3DXBUFFER g_pBuffMatModel = NULL;			// �}�e���A��(�ގ����)�ւ̃|�C���^
////DWORD g_nNumMatModel = NULL;					// �}�e���A���̐�
//MODEL g_aModel[MAX_MODEL];						// ���f���̏��
////D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;		// ���f���̍ŏ��l�E�ő�l
//LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// �e�N�X�`���ւ̃|�C���^
//
////
//// ����������
////
//void InitModel(void)
//{
//	// �f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		// X�t�@�C���̓ǂݍ���
//		D3DXLoadMeshFromX(
//			"data\\MODEL\\airplane000.x",
//			D3DXMESH_SYSTEMMEM,
//			pDevice,
//			NULL,
//			&g_aModel[nCntModel].pBuffMatModel,
//			NULL,
//			&g_aModel[nCntModel].nNumMatModel,
//			&g_aModel[nCntModel].pMeshModel);
//
//		int nNumvtx = 0;			// ���_��
//		DWORD sizeFVF = NULL;		// ���_�t�H�[�}�b�g�̃T�C�Y
//		BYTE *pVtxBuff = NULL;		// ���_�o�b�t�@�̃|�C���^
//
//		D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^
//
//		g_aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
//		g_aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);
//
//		// ���_�����擾
//		nNumvtx = g_aModel[nCntModel].pMeshModel->GetNumVertices();
//
//		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
//		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntModel].pMeshModel->GetFVF());
//
//		// ���_�o�b�t�@�����b�N
//		g_aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
//		{
//			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��
//
//			// ���S�Ă̒��_�����r���ă��f���̍ŏ��l�E�ő�l�𔲂��o��
//			if (g_aModel[nCntModel].vtxMinModel.x > vtx.x)
//			{
//				g_aModel[nCntModel].vtxMinModel.x = vtx.x;
//			}
//
//			if (g_aModel[nCntModel].vtxMinModel.y > vtx.y)
//			{
//				g_aModel[nCntModel].vtxMinModel.y = vtx.y;
//			}
//
//			if (g_aModel[nCntModel].vtxMinModel.z > vtx.z)
//			{
//				g_aModel[nCntModel].vtxMinModel.z = vtx.z;
//			}
//
//			if (g_aModel[nCntModel].vtxMaxModel.x < vtx.x)
//			{
//				g_aModel[nCntModel].vtxMaxModel.x = vtx.x;
//			}
//
//			if (g_aModel[nCntModel].vtxMaxModel.y < vtx.y)
//			{
//				g_aModel[nCntModel].vtxMaxModel.y = vtx.y;
//			}
//
//			if (g_aModel[nCntModel].vtxMaxModel.z < vtx.z)
//			{
//				g_aModel[nCntModel].vtxMaxModel.z = vtx.z;
//			}
//			// ���S�Ă̒��_�����r���ă��f���̍ŏ��l�E�ő�l�𔲂��o��
//
//			pVtxBuff += sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//		}
//
//		g_aModel[nCntModel].pMeshModel->UnlockVertexBuffer();
//
//		// �}�e���A�����ɑ΂���|�C���^���擾
//		pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
//		{
//			if (pMat[nCntMat].pTextureFilename != NULL)
//			{// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
//				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
//			}// �����̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
//		}
//
//		g_aModel[nCntModel].pos = D3DXVECTOR3(nCntModel * 10.0f, 0.0f, 0.0f);
//		g_aModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aModel[nCntModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//}
//
//
////
//// �I������
////
//void UninitModel(void)
//{
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		// ���b�V���̔j��
//		if (g_aModel[nCntModel].pMeshModel != NULL)
//		{
//			g_aModel[nCntModel].pMeshModel->Release();
//			g_aModel[nCntModel].pMeshModel = NULL;
//		}
//
//		// �}�e���A���̔j��
//		if (g_aModel[nCntModel].pBuffMatModel != NULL)
//		{
//			g_aModel[nCntModel].pBuffMatModel->Release();
//			g_aModel[nCntModel].pBuffMatModel = NULL;
//		}
//	}
//}
//
//
////
//// �X�V����
////
//void UpdateModel(void)
//{
//	Camera *pCamera = GetCamera();
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (GetKeyboardTrigger(DIK_RETURN) == true)
//		{
//			g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
//			g_aModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_aModel[nCntModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		}
//
//		if (GetKeyboardPress(DIK_UP) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (-D3DX_PI + pCamera->rot.y);
//
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//			g_aModel[nCntModel].move.x += sinf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z += cosf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_DOWN) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (pCamera->rot.y);
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//
//			g_aModel[nCntModel].move.x -= sinf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z -= cosf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_LEFT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (D3DX_PI / 2 + pCamera->rot.y);
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//
//			g_aModel[nCntModel].move.x -= cosf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z += sinf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_RIGHT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y = (-D3DX_PI / 2 + pCamera->rot.y);
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//
//			g_aModel[nCntModel].move.x += cosf(pCamera->rot.y) * MODEL_SPD;
//			g_aModel[nCntModel].move.z -= sinf(pCamera->rot.y) * MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_LSHIFT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y -= 0.2f;
//			if (g_aModel[nCntModel].rotDest.y < -D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//			}
//		}
//
//		if (GetKeyboardPress(DIK_RSHIFT) == true)
//		{
//			g_aModel[nCntModel].rotDest.y += 0.2f;
//			if (g_aModel[nCntModel].rotDest.y > D3DX_PI)
//			{
//				g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//			}
//		}
//
//		if (GetKeyboardPress(DIK_I) == true)
//		{
//			g_aModel[nCntModel].move.y += MODEL_SPD;
//		}
//
//		if (GetKeyboardPress(DIK_K) == true)
//		{
//			g_aModel[nCntModel].move.y -= MODEL_SPD;
//		}
//
//
//
//
//		if ((g_aModel[nCntModel].rotDest.y - g_aModel[nCntModel].rot.y) > D3DX_PI)
//		{
//			g_aModel[nCntModel].rotDest.y -= D3DX_PI * 2.0f;
//		}
//		else if ((g_aModel[nCntModel].rotDest.y - g_aModel[nCntModel].rot.y) < -D3DX_PI)
//		{
//			g_aModel[nCntModel].rotDest.y += D3DX_PI * 2.0f;
//		}
//
//		g_aModel[nCntModel].rot.y += (g_aModel[nCntModel].rotDest.y - g_aModel[nCntModel].rot.y) * 0.1f;
//
//		if (g_aModel[nCntModel].rot.y > D3DX_PI)
//		{
//			g_aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
//		}
//		else if (g_aModel[nCntModel].rot.y < -D3DX_PI)
//		{
//			g_aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
//		}
//
//		g_aModel[nCntModel].move.x += (0.0f - g_aModel[nCntModel].move.x) * SPD_DECAY;
//		g_aModel[nCntModel].move.z += (0.0f - g_aModel[nCntModel].move.z) * SPD_DECAY;
//		g_aModel[nCntModel].move.y += (0.0f - g_aModel[nCntModel].move.y) * SPD_DECAY;
//
//		g_aModel[nCntModel].pos.x += g_aModel[nCntModel].move.x;
//		g_aModel[nCntModel].pos.z += g_aModel[nCntModel].move.z;
//		g_aModel[nCntModel].pos.y += g_aModel[nCntModel].move.y;
//	}
//}
//
//
////
//// �`�揈��
////
//void DrawModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�ւ̃|�C���^
//	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
//	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
//	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		// ���[���h�}�g���b�N�X�̏�����
//		D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
//
//		// �����𔽉f
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
//
//		D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);
//
//		// �ʒu�𔽉f
//		D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
//
//		D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
//
//		// ���[���h�}�g���b�N�X�̐ݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
//
//		// ���݂̃}�e���A�����擾
//		pDevice->GetMaterial(&matDef);
//
//		// �}�e���A���f�[�^�ւ̃|�C���^���擾
//		pMat = (D3DXMATERIAL *)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
//		{
//			// �}�e���A���̐ݒ�
//			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//			// �e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);
//
//			// ���f��(�p�[�c)�̕`��
//			g_aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
//		}
//
//	}
//	// �ۑ����Ă����}�e���A����߂�
//	pDevice->SetMaterial(&matDef);
//}
//
//
////
//// ���f���̎擾
////
//MODEL *GetModel(void)
//{
//	return &g_aModel[0];
//}
