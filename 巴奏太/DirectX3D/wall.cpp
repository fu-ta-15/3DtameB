//-----------------------------------------------------------------------------
//
// 壁の処理 [wall.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "wall.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffWall = NULL;									// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall = NULL;									// インデックスバッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;										// ポリゴンのテクスチャへのポインタ
Wall g_aWall[WALL_MAX];															// 壁の情報
D3DXVECTOR3 g_posWall;															// 位置
D3DXVECTOR3 g_rotWall;															// 向き
D3DXMATRIX g_mtxWorldWall;														// ワールドマトリックス

//-----------------------------------------------------------------------------
// ポリゴンの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg" , &g_pTextureWall);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * WALL_MAX,		//サイズ
								D3DUSAGE_WRITEONLY,									//
								FVF_VERTEX_3D,										//フォーマット
								D3DPOOL_MANAGED,									//
								&g_pVtxBuffWall,									//頂点バッファへのポインタ
								NULL);

	VERTEX_3D *pVertex;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		//頂点座標設定 (左奥から右手前に順番)
		pVertex[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
		pVertex[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
		pVertex[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
		pVertex[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
		pVertex[4].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
		pVertex[5].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
		pVertex[6].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		pVertex[7].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		pVertex[8].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

		//pVertex[0].pos = D3DXVECTOR3(g_posWall.x - WALL_WIDTH * 2, g_posWall.y, g_posWall.z);
		//pVertex[1].pos = D3DXVECTOR3(g_posWall.x - WALL_WIDTH * 2, g_posWall.y + WALL_HEIGHT, g_posWall.z);
		//pVertex[2].pos = D3DXVECTOR3(g_posWall.x + WALL_WIDTH * 2, g_posWall.y, g_posWall.z);
		//pVertex[3].pos = D3DXVECTOR3(g_posWall.x + WALL_WIDTH * 2, g_posWall.y + WALL_HEIGHT, g_posWall.z);

		for (int nCnt = 0; nCnt < 9; nCnt++)
		{
			//法線の設定
			pVertex[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			pVertex[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//テクスチャ座標の設定
		pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertex[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVertex[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVertex[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVertex[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVertex[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVertex[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertex[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVertex[8].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffWall,
		NULL);

	WORD *pIdx;	// インデックス情報へのポインタ

	//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

	//番号データ設定 (一筆書きになる順番)
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

	//インデックスバッファをアンロック
	g_pIdxBuffWall->Unlock();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DXToRadian(-90.0f), 0.0f), NULL, NULL);

	return S_OK;
}

//-----------------------------------------------------------------------------
// ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffWall != NULL)
	{
		g_pIdxBuffWall->Release();
		g_pIdxBuffWall = NULL;
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdateWall(void)
{

}

//-----------------------------------------------------------------------------
// ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス

	//デバイス取得
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				14,
				0,
				12);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	VERTEX_3D *pVertex;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			//位置の設定
			g_aWall[nCntWall].pos = pos;

			//回転の設定
			g_aWall[nCntWall].rot = rot;

			//幅設定
			g_aWall[nCntWall].fWidth = fWidth;

			//高さ設定
			g_aWall[nCntWall].fHeight = fHeight;

			////頂点情報設定
			//pVertex[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
			//pVertex[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
			//pVertex[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + WALL_HEIGHT, g_aWall[nCntWall].pos.z);
			//pVertex[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
			//pVertex[4].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
			//pVertex[5].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y + (WALL_HEIGHT / 2), g_aWall[nCntWall].pos.z);
			//pVertex[6].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			//pVertex[7].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			//pVertex[8].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

			//使用中に変更
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}