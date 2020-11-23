//=========================================================================================================================
//
// モデル [model.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "model.h"
#include "input.h"
#include "camera.h"

//
// マクロ定義
//
#define MODEL_SPD (2.0f)	// モデルの移動量
#define SPD_DECAY (0.4f)	// 移動量の減衰係数

//
// グローバル変数
//
LPD3DXMESH g_pMeshModel = NULL;				// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;		// マテリアル(材質情報)へのポインタ
DWORD g_nNumMatModel = NULL;				// マテリアルの数
MODEL g_Model;								// モデルの情報

//
// 初期化処理
//
void InitModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\car000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//
// 終了処理
//
void UninitModel(void)
{
	// メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

}


//
// 更新処理
//
void UpdateModel(void)
{
	Camera pCamera = *GetCamera();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model.rotObjective = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetKeyboardPress(DIK_UP) == true)
	{
		//if (pCamera.rot.y > 0.0f)
		//{
			g_Model.rot.y = (-D3DX_PI + pCamera.rot.y);

			//if (g_Model.rotObjective.y + g_Model.rot.y <= 0.0f)
			//{
			//	g_Model.rot.y += (g_Model.rotObjective.y - g_Model.rot.y) * 0.2f;
			//}
			//else if (g_Model.rotObjective.y + g_Model.rot.y > 0.0f)
			//{
			//	g_Model.rot.y += (g_Model.rotObjective.y + g_Model.rot.y) * 0.2f;
			//}
		//}
		//if (pCamera.rot.y <= 0.0f)
		//{
		//	g_Model.rotObjective.y = (D3DX_PI + pCamera.rot.y);

		//	if (g_Model.rotObjective.y + g_Model.rot.y <= 0.0f)
		//	{
		//		g_Model.rot.y += (g_Model.rotObjective.y + g_Model.rot.y) * 0.2f;
		//	}
		//	else if (g_Model.rotObjective.y + g_Model.rot.y > 0.0f)
		//	{
		//		g_Model.rot.y += (g_Model.rotObjective.y - g_Model.rot.y) * 0.2f;
		//	}
		//}

		if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y += D3DX_PI * 2.0f;
		}
		g_Model.move.x += sinf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z += cosf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.rot.y = (pCamera.rot.y);

		g_Model.move.x -= sinf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z -= cosf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.rot.y = (D3DX_PI / 2 - pCamera.rot.y);

		g_Model.move.x -= cosf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z += sinf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.rot.y = (-D3DX_PI / 2 - pCamera.rot.y);

		g_Model.move.x += cosf(pCamera.rot.y) * MODEL_SPD;
		g_Model.move.z -= sinf(pCamera.rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Model.rot.y -= 0.2f;
		if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Model.rot.y += 0.2f;
		if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y -= D3DX_PI * 2.0f;
		}
	}

	g_Model.move.x += (0.0f - g_Model.move.x) * SPD_DECAY;
	g_Model.move.z += (0.0f - g_Model.move.z) * SPD_DECAY;

	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.z += g_Model.move.z;
}


//
// 描画処理
//
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Model.mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);

	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);

	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL *)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}


//
// モデルの取得
//
MODEL *GetModel(void)
{
	return &g_Model;
}
