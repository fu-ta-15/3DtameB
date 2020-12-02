//===========================================================================================================
//
// ポリゴンの設定 [polygon.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "model.h"
#include "input.h"
#include "camera.h"

//===========================================================================================================
//グローバル変数
//===========================================================================================================
LPD3DXMESH g_pMeshModel = NULL;					//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;			//マテリアルへのポインタ
DWORD g_nNumMatModel = 1;						//マテリアルの数
D3DXVECTOR3 g_posModel;							//位置
D3DXVECTOR3 g_rotModel;							//向き
D3DXMATRIX g_mtxWorldModel;						//ワールドマトリックス

//===========================================================================================================
//初期化
//===========================================================================================================
void InitModel(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\hata.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMatModel,NULL,&g_nNumMatModel,&g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================================================================================
//終了
//===========================================================================================================
void UninitModel(void)
{
	//頂点バッファの開放
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	//テクスチャの開放
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
}

//===========================================================================================================
//更新処理
//===========================================================================================================
void UpdateModel(void)
{
	g_rotModel.y = 0.5f;

	//モデルの移動
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_posModel.z += sinf (g_rotModel.y) * 1;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_posModel.z -= sinf (g_rotModel.y) * 1;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_posModel.x -= cosf (g_rotModel.y) * 1;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_posModel.x += cosf (g_rotModel.y) * 1;
	}
}

//===========================================================================================================
//描画処理
//===========================================================================================================
void DrawModel(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;				//計算用デバイス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixTranslation(&mtxRot, g_rotModel.x, g_rotModel.y, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

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

