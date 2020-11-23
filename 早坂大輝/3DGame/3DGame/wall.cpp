//=============================================================================
//
// 壁の処理 [wall.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "wall.h"
#include "input.h"					

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_WALL (4)							//壁最大数

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9	g_pTextureWall = NULL;		//テクスチャへのポインタ
D3DXVECTOR3 g_posWall;							//位置
D3DXVECTOR3 g_rotWall;							//向き
D3DXMATRIX g_mtxWorldWall;						//ワールドマトリックス
Wall g_aWall[MAX_WALL];							//壁の情報

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_3D *pVtx;			//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wall002.jpg", &g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定(Z型)
		SetVertexWall(nCntWall);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//テクスチャ座標
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Z型
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//４つの頂点を進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
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

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	int nCntVertex = 0;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldWall);

		//ライティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
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
		if (g_aWall[nCntWall].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVertex, 2);
		}
		//４つ進める
		nCntVertex += 4;

		//ライティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//=============================================================================
// 
//=============================================================================
void SetVertexWall(int nCntWall)
{
	VERTEX_3D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntWall * 4;

	pVtx[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - 180.0f, g_aWall[nCntWall].pos.y + 90.0f, g_aWall[nCntWall].pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + 180.0f, g_aWall[nCntWall].pos.y + 90.0f, g_aWall[nCntWall].pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - 180.0f, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + 180.0f, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//=============================================================================
//
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{

		if (g_aWall[nCntWall].bUse == false)
		{
			//向きの設定
			g_aWall[nCntWall].rot = rot;

			//位置を設定
			g_aWall[nCntWall].pos = pos;

			//頂点座標の設定
			SetVertexWall(nCntWall);

			//敵の使用の設定
			g_aWall[nCntWall].bUse = true;

			break;
		}
		//４つの頂点を進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}