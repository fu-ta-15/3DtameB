#include "StageModel.h"
#include "Input.h"
#include "Shadow.h"

LPD3DXMESH g_pMeshModel[STAGEMODEL_NUM] = {};
LPD3DXBUFFER g_pBuffMatModel[STAGEMODEL_NUM] = {};
DWORD g_nNumMatModel = 0;
D3DXMATRIX g_mtxWorldModel;
MODEL *pModel;

void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pModel = (MODEL*)malloc(STAGEMODEL_NUM * sizeof(MODEL));
	
	D3DXLoadMeshFromX("data/MODEL/airplane000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel[0], NULL, &g_nNumMatModel, &g_pMeshModel[0]);
	
	pModel[0].pos = D3DXVECTOR3(0.f, 10.f, 0.f);
	pModel[0].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	pModel[0].ID = 0;
	pModel[0].fMoveSpeed = 0.f;
}

void UninitModel(void)
{
	for (int nCnt = 0; nCnt < STAGEMODEL_NUM; nCnt++)
	{
		if (g_pMeshModel[nCnt] != NULL)
			g_pMeshModel[nCnt] = NULL;
		if (g_pBuffMatModel[nCnt] != NULL)
			g_pBuffMatModel[nCnt] = NULL;
	}
}

void UpdateModel(void)
{
	//CAMERA *pCamera;
	//pCamera = GetCamera();
	////pModel[0].rot.y = PI;
	//if (GetkeyboardPress(DIK_UP) == true)
	//{
	//	if (GetkeyboardPress(DIK_RIGHT) == true)
	//	{
	//		pModel[0].rot.y = -PI * 3 / 4 - pCamera[0].fRot.x;
	//		if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//	}
	//	else if (GetkeyboardPress(DIK_LEFT) == true)
	//	{
	//		pModel[0].rot.y = PI * 3 / 4 - pCamera[0].fRot.x;
	//		if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//	}
	//	else
	//	{
	//		pModel[0].rot.y = PI - pCamera[0].fRot.x;
	//		//pModel[0].rot.y += PI * 0.1;
	//		if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//	}
	//}
	//else if (GetkeyboardPress(DIK_DOWN) == true)
	//{
	//	if (GetkeyboardPress(DIK_LEFT) == true)
	//	{
	//		pModel[0].rot.y = PI / 4 - pCamera[0].fRot.x;
	//		if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//	}
	//	else if (GetkeyboardPress(DIK_RIGHT) == true)
	//	{
	//		pModel[0].rot.y = -PI / 4 - pCamera[0].fRot.x;
	//		if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//	}
	//	else
	//	{
	//		pModel[0].rot.y = -pCamera[0].fRot.x;
	//		if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//	}
	//}
	//else if (GetkeyboardPress(DIK_LEFT) == true)
	//{
	//	pModel[0].rot.y = PI / 2 - pCamera[0].fRot.x;
	//	if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//}
	//else if (GetkeyboardPress(DIK_RIGHT) == true)
	//{
	//	pModel[0].rot.y = - PI / 2 - pCamera[0].fRot.x;
	//	if (pModel[0].fMoveSpeed < 3) pModel[0].fMoveSpeed++;
	//}
	//else if(pModel[0].fMoveSpeed > 0) pModel[0].fMoveSpeed --;

	//pModel[0].pos.x += -sinf(pModel[0].rot.y) * pModel[0].fMoveSpeed;
	//pModel[0].pos.z += -cosf(pModel[0].rot.y) * pModel[0].fMoveSpeed;
	//pCamera->posV.x += -sinf(pModel[0].rot.y) * pModel[0].fMoveSpeed;
	//pCamera->posV.z += -cosf(pModel[0].rot.y) * pModel[0].fMoveSpeed;

	//pCamera->posR = pModel[0].pos;
	//SetShadow(pModel[0].pos, D3DXVECTOR2(5.f, 5.f), pModel[0].ID);
}

void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;
	for (int nCnt = 0; nCnt < STAGEMODEL_NUM; nCnt++)
	{
		D3DXMatrixIdentity(&g_mtxWorldModel);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pModel[0].rot.y, pModel[0].rot.x, pModel[0].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pModel[0].pos.x, pModel[0].pos.y, pModel[0].pos.z); //¢ŠEmatrix‘S‘Ì@ˆÚ“®‚µ‚½‚¢‹——£‚Æ‚¢‚¤matrix‚Ì‡ŽZ
		D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans); //¢ŠEmatrix‚ÌˆÚ“®
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel); //set the world into Map
		pDevice->GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt]->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice->SetTexture(0, NULL);
			g_pMeshModel[nCnt]->DrawSubset(nCntMat);
		}
		pDevice->SetMaterial(&matDef);
	}
}