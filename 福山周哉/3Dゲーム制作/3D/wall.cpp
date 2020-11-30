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
#define MAX_SIZE (50.0f)				//壁のサイズ

//===========================================================================================================
//グローバル変数
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferWall = NULL;
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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferWall, NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBufferWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y + 50, g_posWall.z + 50);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y + 50, g_posWall.z + 50);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x - MAX_SIZE, g_posWall.y, g_posWall.z + 50);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x + MAX_SIZE, g_posWall.y, g_posWall.z + 50);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBufferWall->Unlock();

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

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,						//描画を開始する頂点インデックス
		2);						//描画するプリミティブ数

}