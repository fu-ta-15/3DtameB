//=============================================================================
//
// モデルの処理 [model.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"

//=============================================================================
// グローバル変数
//=============================================================================
LPD3DXMESH g_pMeshModel = NULL;			//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアル(材質情報)へのポインタ
DWORD g_nNumMatModel = 0;				//マテリアルの数
D3DXVECTOR3 g_posModel;					//位置
D3DXVECTOR3 g_rotModel;					//向き
D3DXVECTOR3 g_moveModel;				//移動量
D3DXMATRIX g_mtxWorldModel;				//ワールドマトリックス
int nCntBoost;

//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/sieldcell000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置の初期設定
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きの初期設定
	nCntBoost = 0.0f;
}

//=============================================================================
// 終了処理
//=============================================================================
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

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	//ブースト残量
	if (nCntBoost < 100)
	{
		nCntBoost++;
	}

	//位置の更新
	g_posModel.x += g_moveModel.x;
	g_posModel.y += g_moveModel.y;
	g_posModel.z += g_moveModel.z;

	//移動量の減衰
	g_moveModel.x += (0.0f - g_moveModel.x) * 0.2f;
	g_moveModel.y += (0.0f - g_moveModel.y) * 0.2f;
	g_moveModel.z += (0.0f - g_moveModel.z) * 0.2f;

	//重力
	if (g_posModel.y > 0.0f)
	{
		g_moveModel.y -= 0.5;
	}
	if (g_posModel.y < 0.0f)
	{
		g_posModel.y = 0.0f;
	}

	//浮遊
	if (GetKeyboardPress(DIK_J) == true)
	{
		if (nCntBoost > 0)
		{
			g_moveModel.y += 1;
			nCntBoost -= 3;
		}
	}

	//モデルの移動
	if (GetKeyboardPress(DIK_UP) == true)		//↑を押した
	{
		//前移動
		g_posModel.x += sinf(pCamera->rot.y) * 2.0f;
		g_posModel.x += sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z += cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z += cosf(pCamera->rot.y) * 2.0f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)		//↓を押した
	{
		//後移動
		g_posModel.x -= sinf(pCamera->rot.y) * 2.0f;
		g_posModel.x -= sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= cosf(pCamera->rot.y) * 2.0f;
	}
	if (GetKeyboardPress(DIK_RIGHT) == true)	//→を押した
	{
		//右移動
		g_posModel.x += cosf(pCamera->rot.y) * 2.0f;
		g_posModel.x += cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z -= sinf(pCamera->rot.y) * 2.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)		//←を押した
	{
		//左移動
		g_posModel.x -= cosf(pCamera->rot.y) * 2.0f;
		g_posModel.x -= cosf(pCamera->rot.y) * 2.0f;
		g_posModel.z += sinf(pCamera->rot.y) * 2.0f;
		g_posModel.z += sinf(pCamera->rot.y) * 2.0f;
	}


	//モデルの向き
	if (GetKeyboardPress(DIK_LSHIFT) == true)	//左シフトを押した
	{
		//左回転
		g_rotModel.y -= 0.05f;
	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)	//右シフトを押した
	{
		//右回転
		g_rotModel.y += 0.05f;
	}

	//リセット
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
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

		//モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}