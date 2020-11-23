//=============================================================================
//
// 影の処理 [shadow.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "shadow.h"
#include "input.h"

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9	g_pTextureShadow = NULL;		//テクスチャへのポインタ
D3DXVECTOR3 g_posShadow;							//位置
D3DXVECTOR3 g_rotShadow;							//向き
D3DXMATRIX g_mtxWorldShadow;						//ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_3D *pVtx;			//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(Z型)
	pVtx[0].pos = D3DXVECTOR3(g_posShadow.x - 20.0f, g_posShadow.y, g_posShadow.z + 15.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posShadow.x + 20.0f, g_posShadow.y, g_posShadow.z + 15.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posShadow.x - 20.0f, g_posShadow.y, g_posShadow.z - 15.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posShadow.x + 20.0f, g_posShadow.y, g_posShadow.z - 15.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//テクスチャ座標
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Z型
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	//テクスチャの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);
	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);
	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}