//=========================================================================================================================
//
// HPゲージ [hpgauge.cpp]
// Author:Hiroya Katano
//
//=========================================================================================================================
#include "hpgauge.h"
#include "player.h"

//=========================================================================================================================
// グローバル変数
//=========================================================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHPGauge = NULL;		// 頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureGaugeBG = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGauge = NULL;
LPDIRECT3DTEXTURE9 g_pTextureGaugeFlame = NULL;

//=========================================================================================================================
// HPGaugeの初期化処理
//=========================================================================================================================
HRESULT InitHPGauge(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HPGaugeBG.png", &g_pTextureGaugeBG);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HPGauge.png", &g_pTextureGauge);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HPGaugeFrame.png", &g_pTextureGaugeFlame);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TYPE_HPGAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHPGauge,
		NULL)))
	{
		return E_FAIL;
	}



	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHPGauge = 0; nCntHPGauge < MAX_TYPE_HPGAUGE; nCntHPGauge++)
	{
		// 頂点座標の設定
		switch (nCntHPGauge)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_BG_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_BG_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_BG_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_BG_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_BG_Y / 2, 0.0f);
			break;
		case 1:
			pVtx[0].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
			break;
		case 2:
			pVtx[0].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_FRAME_Y / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_FRAME_Y / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_FRAME_Y / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_FRAME_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_FRAME_Y / 2, 0.0f);
			break;
		}

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = DEFAULT_COLOR;
		pVtx[1].col = DEFAULT_COLOR;
		pVtx[2].col = DEFAULT_COLOR;
		pVtx[3].col = DEFAULT_COLOR;

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffHPGauge->Unlock();

	return S_OK;
}

//=========================================================================================================================
// HPGaugeの終了処理
//=========================================================================================================================
void UninitHPGauge(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffHPGauge != NULL)
	{
		g_pVtxBuffHPGauge->Release();
		g_pVtxBuffHPGauge = NULL;
	}

	// テクスチャの開放
	if (g_pTextureGaugeBG != NULL)
	{
		g_pTextureGaugeBG->Release();
		g_pTextureGaugeBG = NULL;
	}

	if (g_pTextureGauge != NULL)
	{
		g_pTextureGauge->Release();
		g_pTextureGauge = NULL;
	}

	if (g_pTextureGaugeFlame != NULL)
	{
		g_pTextureGaugeFlame->Release();
		g_pTextureGaugeFlame = NULL;
	}
}

//=========================================================================================================================
// HPGaugeの更新処理
//=========================================================================================================================
void UpdateHPGauge(void)
{
	ManageGauge();
}

//=========================================================================================================================
// HPGaugeの描画処理
//=========================================================================================================================
void DrawHPGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHPGauge, 0, sizeof(VERTEX_2D));

	// 頂点フォ―マットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TYPE_HPGAUGE; nCnt++)
	{
		// テクスチャの設定
		switch (nCnt)
		{
		case 0:
			pDevice->SetTexture(0, g_pTextureGaugeBG);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTextureGauge);
			break;
		case 2:
			pDevice->SetTexture(0, g_pTextureGaugeFlame);
			break;
		}

		// HPGaugeの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			// プリミティブの種類
			nCnt * 4,								// 描画を開始する頂点インデックス
			2);								// 描画するプリミティブの数
	}
}


//=========================================================================================================================
// 特殊ゲージの管理
//=========================================================================================================================
void ManageGauge(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	Player *pPlayer = GetPlayer();


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->nLife == PLAYER_HEALTH)
	{
		pVtx[4].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X + GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
	}
	else if (pPlayer->nLife >= 0 || pPlayer->nLife < PLAYER_HEALTH)
	{
		pVtx[4].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2, HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2 + GAUGE_X * (pPlayer->nLife / (PLAYER_HEALTH*1.0f)), HPGAUGE_BASE_POINT_Y + GAUGE_Y / 2, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(HPGAUGE_BASE_POINT_X - GAUGE_X / 2 + GAUGE_X * (pPlayer->nLife / (PLAYER_HEALTH*1.0f)), HPGAUGE_BASE_POINT_Y - GAUGE_Y / 2, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffHPGauge->Unlock();
}
