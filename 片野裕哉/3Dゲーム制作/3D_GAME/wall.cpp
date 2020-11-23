//=========================================================================================================================
//
// 壁(ウォール) [wall.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "wall.h"

//
// マクロ定義
//
#define MAX_WALL (256)			// 壁の最大数
#define WALL_SIZE (200)			// 壁の大きさ

//
// 構造体の定義
//
typedef struct
{
	D3DXVECTOR3 pos;			// 壁の中心座標
	D3DXVECTOR3 rot;			// 壁の向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	bool bUse;					// 使用しているかどうか
}Wall;

//
// グローバル変数
//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;			// テクスチャへのポインタ
Wall g_aWall[MAX_WALL];								// 壁の情報

//
// 初期化処理
//
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Wall *pWall = &g_aWall[0];						// 壁の構造体のポインタ

	// デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++, pWall++)
	{
		pWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWall->bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\field000.jpg", &g_pTextureWall);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		// 頂点座標の設定
		SetVertexWall(nCnt);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	for (int SetCntWall = 0; SetCntWall < 1; SetCntWall++)
	{
		SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	return S_OK;
}


//
// 終了処理
//
void UninitWall(void)
{
	// テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

}


//
// 更新処理
//
void UpdateWall(void)
{

}


//
// 描画処理
//
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	Wall *pWall = &g_aWall[0];						// 壁の構造体のポインタ
	D3DXMATRIX mtxRot, mtxTrans;					// 計算用マトリックス


	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++, pWall++)
	{
		if (pWall->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pWall->mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			// ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				4 * nCnt,						// 描画を開始する頂点インデックス
				2);								// 描画するプリミティブの数
		}
	}
}


//
// 壁の配置
//
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 構造体のポインタ変数
	Wall *pWall = &g_aWall[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{
			// 位置の設定
			pWall->pos = pos;

			// 角度の設定
			pWall->rot = rot;

			// 使用状態をtrueにする
			pWall->bUse = true;

			break;
		}
	}
}


//-----------------------------------------------------------------
// 壁の頂点座標の設定
//-----------------------------------------------------------------
void SetVertexWall(int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_3D *pVtx;
	Wall *pWall = &g_aWall[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nIdx * 4;
	pWall += nIdx;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	pVtx[1].pos = D3DXVECTOR3(pWall->pos.x - WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);
	pVtx[2].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y, pWall->pos.z);
	pVtx[3].pos = D3DXVECTOR3(pWall->pos.x + WALL_SIZE / 2.0f, pWall->pos.y + WALL_SIZE, pWall->pos.z);

	// 頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}