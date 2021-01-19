////===========================================================================================================
////
//// �|���S���̐ݒ� [polygon.cpp]
//// Author: fukuyama syuya
////
////===========================================================================================================
//#include "model.h"
//#include "input.h"
//#include "camera.h"
//#include "bullet.h"
//
////===========================================================================================================
//// �}�N����`
////===========================================================================================================
//#define MAX_TEX (1)										//�e�N�X�`���̍ő吔
//
////===========================================================================================================
//// �O���[�o���ϐ�
////===========================================================================================================
//LPD3DXMESH g_pMeshModel = NULL;							//���b�V���ւ̃|�C���^
//LPD3DXBUFFER g_pBuffMatModel = NULL;					//�}�e���A���ւ̃|�C���^
//DWORD g_nNumMatModel = 1;								//�}�e���A���̐�
//D3DXMATRIX g_mtxWorldModel;								//���[���h�}�g���b�N�X
//Model g_Model;											//���f���̏��
//D3DXVECTOR3 g_VtxMinModel, g_VtxMaxModel;				//���f���̍ŏ��l�E�ő�l
//LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};			//�e�N�X�`���ւ̃|�C���^
//
////===========================================================================================================
//// ������
////===========================================================================================================
//void InitModel(void)
//{
//	//�ϐ��錾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//		//X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX("data\\MODEL\\hata2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);
//
//	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^
//
//	//�}�e���A�����ɑ΂���|�C���^���擾
//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
//	{
//		if (pMat[nCntMat].pTextureFilename != NULL)
//		{
//			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
//		}
//	}
//
//	int nNumVtx;					//���_��
//
//	DWORD sizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y
//
//	BYTE *pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
//
//	//���_�����擾
//	nNumVtx = g_pMeshModel->GetNumVertices();
//
//	//���_�t�H�[�}�b�g�̃T�C�Y���擾
//	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());
//
//	//���_�o�b�t�@�̃��b�N
//	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//	{
//		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;				//���_���W�̑��
//
//
//
//		pVtxBuff += sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//	}
//
//	//���_�o�b�t�@�̃A�����b�N
//	g_pMeshModel->UnlockVertexBuffer();
//
//	//���f���̏�����
//	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////===========================================================================================================
//// �I��
////===========================================================================================================
//void UninitModel(void)
//{
//	//���_�o�b�t�@�̊J��
//	if (g_pBuffMatModel != NULL)
//	{
//		g_pBuffMatModel->Release();
//		g_pBuffMatModel = NULL;
//	}
//
//	//�e�N�X�`���̊J��
//	if (g_pMeshModel != NULL)
//	{
//		g_pMeshModel->Release();
//		g_pMeshModel = NULL;
//	}
//}
//
////===========================================================================================================
//// �X�V����
////===========================================================================================================
//void UpdateModel(void)
//{
//	Camera *pCamera;
//
//	pCamera = GetCamera();
//
//	//���f���̈ړ�
//	if (GetKeyboardPress(DIK_UP) == true)
//	{
//		g_Model.pos.x += sinf(pCamera->rot.y) * 1;
//		g_Model.pos.z += cosf (pCamera->rot.y) * 1;
//
//		g_Model.rotDest.y = D3DX_PI + pCamera->rot.y;
//	}
//
//	if (GetKeyboardPress(DIK_DOWN) == true)
//	{
//		g_Model.pos.z -= cosf (pCamera->rot.y) * 1;
//		g_Model.pos.x -= sinf (pCamera->rot.y) * 1;
//
//		g_Model.rotDest.y = 0.0f + pCamera->rot.y;
//	}
//
//	if (GetKeyboardPress(DIK_LEFT) == true)
//	{
//		g_Model.pos.x -= cosf (pCamera->rot.y) * 1;
//		g_Model.pos.z += sinf (pCamera->rot.y) * 1;
//
//		g_Model.rotDest.y = D3DX_PI / 2 + pCamera->rot.y;
//	}
//
//	if (GetKeyboardPress(DIK_RIGHT) == true)
//	{
//		g_Model.pos.x += cosf (pCamera->rot.y) * 1;
//		g_Model.pos.z -= sinf (pCamera->rot.y) * 1;
//
//		g_Model.rotDest.y = -D3DX_PI / 2 + pCamera->rot.y;
//	}
//
//	g_Model.rot.y = g_Model.rotDest.y;
//
//	//���f���̌���
//	
//
//	//�e�𔭎�
//	if (GetKeyboardPress(DIK_SPACE) == true)
//	{
//		SetBullet(g_Model.pos, D3DXVECTOR3(10.0f, 0.0f, 0.0f), 50, PLAYER_BULLET);
//	}
//}
//
////===========================================================================================================
//// �`�揈��
////===========================================================================================================
//void DrawModel(void)
//{
//	//�ϐ��錾
//	LPDIRECT3DDEVICE9 pDevice;
//	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�f�o�C�X
//	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
//	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�̃|�C���^
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&g_mtxWorldModel);
//
//	//�����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
//
//	//�ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);
//
//	//���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);
//
//	//���݂̃}�e���A�����擾
//	pDevice->GetMaterial(&matDef);
//
//	//�}�e���A���f�[�^�ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//	
//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
//	{
//		//�}�e���A���̐ݒ�
//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//		//�e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);
//
//		//���f���p�[�c�̕`��
//		g_pMeshModel->DrawSubset(nCntMat);
//	}
//
//	//�ۑ����Ă����}�e���A����߂�
//	pDevice->SetMaterial(&matDef);
//}
////===========================================================================================================
//// ���f���̎擾
////===========================================================================================================
//Model *GetModel(void)
//{
//	return &g_Model;
//}