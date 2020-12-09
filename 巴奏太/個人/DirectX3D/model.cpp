//-----------------------------------------------------------------------------
//
// モデルの処理 [model.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;													// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel;													// マテリアル(材質)へのポインタ
DWORD g_nNumMatModel = 0;														// マテリアルの数
Model g_Model;																	// モデルの情報
D3DXVECTOR3 g_posModel;															// 位置
D3DXVECTOR3 g_rotModel;															// 向き
D3DXMATRIX g_mtxWorldModel;														// ワールドマトリックス

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();														// デバイスの取得

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\chair_wood00.x",			// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,						// 固定
		pDevice,								// デバイス
		NULL,									// NULL固定
		&g_pBuffMatModel,						// マテリアル
		NULL,									// NULL固定
		&g_nNumMatModel,						// マテリアル数
		&g_pMeshModel);							// メッシュ

	//初期位置、向き
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 初期位置
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 初期向き
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	Camera *pCamera;
	pCamera = GetCamera();


	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Model.pos.x += sinf(pCamera->rot.y);
		g_Model.pos.z += cosf(pCamera->rot.y);
		g_Model.rot.y = pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.pos.x -= sinf(pCamera->rot.y);
		g_Model.pos.z -= cosf(pCamera->rot.y);
		g_Model.rot.y = pCamera->rot.y + D3DXToRadian(180.0f);
	}
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.pos.x -= sinf(pCamera->rot.y + D3DXToRadian(90));
		g_Model.pos.z -= cosf(pCamera->rot.y + D3DXToRadian(90));
		g_Model.rot.y = pCamera->rot.y + D3DXToRadian(-90.0f);
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.pos.x -= sinf(pCamera->rot.y + D3DXToRadian(-90));
		g_Model.pos.z -= cosf(pCamera->rot.y + D3DXToRadian(-90));
		g_Model.rot.y = pCamera->rot.y + D3DXToRadian(90.0f);
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
	D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
	pDevice = GetDevice();														// デバイスの取得

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Model.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

Model *GetModel(void)
{
	return &g_Model;
}

D3DXMATRIX *GetModelMTX(void)
{
	return &g_Model.mtxWorld;
}