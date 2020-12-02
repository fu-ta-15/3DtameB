//===========================================================================================================
//
// ポリゴンの設定 [polygon.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "polygon.h"

//===========================================================================================================
//マクロ定義
//===========================================================================================================
#define MAX_POLYGON (1)					//ポリゴンの最大数
#define MAX_SIZE (50.0f)				//ポリゴンのサイズ

//===========================================================================================================
//グローバル変数
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferPolygon = NULL;
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;					//テクスチャ
D3DXVECTOR3 g_posPolygon;										//位置
D3DXVECTOR3 g_rotPolygon;										//向き
D3DXMATRIX g_mtxWorldPolygon;									//ワールドマトリックス

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT InitPolygon(void)					//デバイスのポインタ
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field001.jpg", &g_pTexturePolygon);

	//ポリゴンの初期化
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferPolygon, NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBufferPolygon->Lock(0,0,(void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - MAX_SIZE, g_posPolygon.y, g_posPolygon.z + MAX_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + MAX_SIZE, g_posPolygon.y, g_posPolygon.z + MAX_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - MAX_SIZE, g_posPolygon.y, g_posPolygon.z - MAX_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + MAX_SIZE, g_posPolygon.y, g_posPolygon.z - MAX_SIZE);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,  0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBufferPolygon->Unlock();

	return S_OK;
}

//===========================================================================================================
//終了処理
//===========================================================================================================
void UninitPolygon(void)
{
	//頂点バッファの開放
	if (g_pVtxBufferPolygon != NULL)
	{
		g_pVtxBufferPolygon->Release();
		g_pVtxBufferPolygon = NULL;
	}

	//テクスチャの開放
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//===========================================================================================================
//更新処理
//===========================================================================================================
void UpdatePolygon(void)
{
}

//===========================================================================================================
//描画処理
//===========================================================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスポインタ
	D3DXMATRIX mtxRot,mtxTrans;					//計算用マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufferPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,						//描画を開始する頂点インデックス
		2);						//描画するプリミティブ数

}