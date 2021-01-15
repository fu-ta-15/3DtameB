//=================================================================================================================
//
// 壁の処理　〔wall.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "wall.h"
#include "input.h"
#include "polygon.h"

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
D3DXVECTOR3 g_posWall;			//位置
D3DXVECTOR3 g_rotWall;			//向き
D3DXMATRIX g_mtxWorldWall;		//ワールドマトリックス


//*****************************************************************************************************************
//	ポリゴンの初期化処理
//*****************************************************************************************************************
HRESULT InitWall(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\wall00.jfif", &g_pTextureWall);

	g_posWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定 (XYZ)
	pVtx[0].pos = D3DXVECTOR3(g_posWall.x - F_SIZE_X,g_posWall.y + 150.0f, F_SIZE_X);
	pVtx[1].pos = D3DXVECTOR3(g_posWall.x + F_SIZE_X,g_posWall.y + 150.0f, F_SIZE_X);
	pVtx[2].pos = D3DXVECTOR3(g_posWall.x - F_SIZE_X,g_posWall.y, F_SIZE_X);
	pVtx[3].pos = D3DXVECTOR3(g_posWall.x + F_SIZE_X,g_posWall.y, F_SIZE_X);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャー座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	return E_NOTIMPL;
}

//*****************************************************************************************************************
//	ポリゴンの終了処理
//*****************************************************************************************************************
void UninitWall(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//*****************************************************************************************************************
//	ポリゴンの更新処理
//*****************************************************************************************************************
void UpdateWall(void)
{
}

//*****************************************************************************************************************
//	ポリゴンの描画処理
//*****************************************************************************************************************
void DrawWall(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;	

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
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWall);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
