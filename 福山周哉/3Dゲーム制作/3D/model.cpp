////===========================================================================================================
////
//// ポリゴンの設定 [polygon.cpp]
//// Author: fukuyama syuya
////
////===========================================================================================================
//#include "model.h"
//#include "input.h"
//#include "camera.h"
//#include "bullet.h"
//
////===========================================================================================================
//// マクロ定義
////===========================================================================================================
//#define MAX_TEX (1)										//テクスチャの最大数
//
////===========================================================================================================
//// グローバル変数
////===========================================================================================================
//LPD3DXMESH g_pMeshModel = NULL;							//メッシュへのポインタ
//LPD3DXBUFFER g_pBuffMatModel = NULL;					//マテリアルへのポインタ
//DWORD g_nNumMatModel = 1;								//マテリアルの数
//D3DXMATRIX g_mtxWorldModel;								//ワールドマトリックス
//Model g_Model;											//モデルの情報
//D3DXVECTOR3 g_VtxMinModel, g_VtxMaxModel;				//モデルの最小値・最大値
//LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};			//テクスチャへのポインタ
//
////===========================================================================================================
//// 初期化
////===========================================================================================================
//void InitModel(void)
//{
//	//変数宣言
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//		//Xファイルの読み込み
//	D3DXLoadMeshFromX("data\\MODEL\\hata2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);
//
//	D3DXMATERIAL *pMat;				//マテリアルへのポインタ
//
//	//マテリアル情報に対するポインタを取得
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
//	int nNumVtx;					//頂点数
//
//	DWORD sizeFVF;					//頂点フォーマットのサイズ
//
//	BYTE *pVtxBuff;					//頂点バッファへのポインタ
//
//	//頂点数を取得
//	nNumVtx = g_pMeshModel->GetNumVertices();
//
//	//頂点フォーマットのサイズを取得
//	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());
//
//	//頂点バッファのロック
//	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//	{
//		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;				//頂点座標の代入
//
//
//
//		pVtxBuff += sizeFVF;									//頂点フォーマットのサイズ分ポインタを進める
//	}
//
//	//頂点バッファのアンロック
//	g_pMeshModel->UnlockVertexBuffer();
//
//	//モデルの初期化
//	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////===========================================================================================================
//// 終了
////===========================================================================================================
//void UninitModel(void)
//{
//	//頂点バッファの開放
//	if (g_pBuffMatModel != NULL)
//	{
//		g_pBuffMatModel->Release();
//		g_pBuffMatModel = NULL;
//	}
//
//	//テクスチャの開放
//	if (g_pMeshModel != NULL)
//	{
//		g_pMeshModel->Release();
//		g_pMeshModel = NULL;
//	}
//}
//
////===========================================================================================================
//// 更新処理
////===========================================================================================================
//void UpdateModel(void)
//{
//	Camera *pCamera;
//
//	pCamera = GetCamera();
//
//	//モデルの移動
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
//	//モデルの向き
//	
//
//	//弾を発射
//	if (GetKeyboardPress(DIK_SPACE) == true)
//	{
//		SetBullet(g_Model.pos, D3DXVECTOR3(10.0f, 0.0f, 0.0f), 50, PLAYER_BULLET);
//	}
//}
//
////===========================================================================================================
//// 描画処理
////===========================================================================================================
//void DrawModel(void)
//{
//	//変数宣言
//	LPDIRECT3DDEVICE9 pDevice;
//	D3DXMATRIX mtxRot, mtxTrans;				//計算用デバイス
//	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
//	D3DXMATERIAL *pMat;							//マテリアルデータのポインタ
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//ワールドマトリックスの初期化
//	D3DXMatrixIdentity(&g_mtxWorldModel);
//
//	//向きを反映
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
//
//	//位置を反映
//	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);
//
//	//ワールドマトリックスの設定
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);
//
//	//現在のマテリアルを取得
//	pDevice->GetMaterial(&matDef);
//
//	//マテリアルデータへのポインタを取得
//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//	
//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
//	{
//		//マテリアルの設定
//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//		//テクスチャの設定
//		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);
//
//		//モデルパーツの描画
//		g_pMeshModel->DrawSubset(nCntMat);
//	}
//
//	//保存していたマテリアルを戻す
//	pDevice->SetMaterial(&matDef);
//}
////===========================================================================================================
//// モデルの取得
////===========================================================================================================
//Model *GetModel(void)
//{
//	return &g_Model;
//}