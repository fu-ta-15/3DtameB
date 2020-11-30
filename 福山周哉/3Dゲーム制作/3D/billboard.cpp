//===========================================================================================================
//
// ビルボードの設定 [wall.cpp]
// Author: fukuyama syuya
//
//===========================================================================================================
#include "billboard.h"

//===========================================================================================================
//マクロ定義
//===========================================================================================================
#define MAX_SIZE (50.0f)				//ビルボードのサイズ

//===========================================================================================================
//グローバル変数
//===========================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBillboard = NULL;
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;					//テクスチャ
D3DXVECTOR3 g_posBillboard;										//位置
D3DXMATRIX g_mtxWorldBillboard;									//ワールドマトリックス

//===========================================================================================================
// 初期化処理
//===========================================================================================================
HRESULT InitBillboard(void)					//デバイスのポインタ
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cube.png", &g_pTextureBillboard);

	//ポリゴンの初期化
	g_posBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBufferBillboard, NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBufferBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posBillboard.x + 20, g_posBillboard.y + 45, g_posBillboard.z);
	pVtx[1].pos = D3DXVECTOR3(g_posBillboard.x + 20, g_posBillboard.y, g_posBillboard.z);
	pVtx[2].pos = D3DXVECTOR3(g_posBillboard.x - 20, g_posBillboard.y + 45, g_posBillboard.z);
	pVtx[3].pos = D3DXVECTOR3(g_posBillboard.x - 20, g_posBillboard.y, g_posBillboard.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	g_pVtxBufferBillboard->Unlock();

	return S_OK;
}

//===========================================================================================================
//終了処理
//===========================================================================================================
void UninitBillboard(void)
{
	//頂点バッファの開放
	if (g_pVtxBufferBillboard != NULL)
	{
		g_pVtxBufferBillboard->Release();
		g_pVtxBufferBillboard = NULL;
	}

	//テクスチャの開放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//===========================================================================================================
//更新処理
//===========================================================================================================
void UpdateBillboard(void)
{
}

//===========================================================================================================
//描画処理
//===========================================================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ
	D3DXMATRIX mtxView;								//ビューマトリックス取得用				
	D3DXMATRIX mtxTrans;							//計算用マトリックス

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//ビューマトリックス取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);				//逆行列を求める

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufferBillboard, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,						//描画を開始する頂点インデックス
		2);						//描画するプリミティブ数

}