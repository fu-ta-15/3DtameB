//===========================================================================================================
//
// 壁の設定 [wall.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "wall.h"

//===========================================================================================================
//マクロ定義
//===========================================================================================================
#define MAX_WALL (1)					//壁の最大数
#define MAX_SIZE (100.0f)				//壁のサイズ

//===========================================================================================================
//グローバル変数
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferWall = NULL;			//ポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;				//インデックスのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;					//テクスチャ
D3DXVECTOR3 g_posWall;										//位置
D3DXVECTOR3 g_rotWall;										//向き
D3DXMATRIX g_mtxWorldWall;									//ワールドマトリックス

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT InitWall(void)					//デバイスのポインタ
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field002.jpg", &g_pTextureWall);

	//ポリゴンの初期化
	g_rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferWall, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffWall, NULL);

	WORD * pIdx;				//インデックス情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBufferWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[4].pos = D3DXVECTOR3(g_posWall.x, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[5].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[6].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y, g_posWall.z + MAX_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posWall.x, g_posWall.y, g_posWall.z + MAX_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y, g_posWall.z + MAX_SIZE);

	/*pVtx[0].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z - MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE * 2, g_posWall.z + MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z - MAX_SIZE);
	pVtx[4].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z);
	pVtx[5].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + MAX_SIZE, g_posWall.z + MAX_SIZE);
	pVtx[6].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y - MAX_SIZE, g_posWall.z - MAX_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y - MAX_SIZE, g_posWall.z);
	pVtx[8].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y - MAX_SIZE, g_posWall.z + MAX_SIZE);*/

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	//頂点バッファをアンロック
	g_pVtxBufferWall->Unlock();

	//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

	//番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファのアンロック
	g_pIdxBuffWall->Unlock();

	return S_OK;
}

//===========================================================================================================
//終了処理
//===========================================================================================================
void UninitWall(void)
{
	//頂点バッファの開放
	if (g_pVtxBufferWall  != NULL)
	{
		g_pVtxBufferWall->Release();
		g_pVtxBufferWall = NULL;
	}

	//テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//インデックスの開放
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//===========================================================================================================
//更新処理
//===========================================================================================================
void UpdateWall(void)
{
}

//===========================================================================================================
//描画処理
//===========================================================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスポインタ
	D3DXMATRIX mtxRot, mtxTrans;					//計算用マトリックス

													//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldWall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotWall.y, g_rotWall.x, g_rotWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posWall.x, g_posWall.y, g_posWall.z);
	D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufferWall, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffWall);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 
													   0, 
													   9,			//頂点数
													   0, 
													  14);			//描画するプリミティブ数
}