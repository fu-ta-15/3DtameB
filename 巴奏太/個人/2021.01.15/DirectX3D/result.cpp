//-----------------------------------------------------------------------------
//
// リザルトの処理 [result.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "result.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define RESULT_OBJ_AMOUNT (1)													//オブジェクト数

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffResult = NULL;								//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureResult[RESULT_OBJ_AMOUNT] = { NULL };				//リザルトのテクスチャへのポインタ
RESULT g_aResult[RESULT_OBJ_AMOUNT];												//リザルト構造体の配列情報

//-----------------------------------------------------------------------------
// リザルトの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVertex;

	//デバイスの取得
	pDevice = GetDevice();

	//リザルト構造体の初期化
	g_aResult[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result_bg.jpg", &g_apTextureResult[0]);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * RESULT_OBJ_AMOUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntR = 0; nCntR < RESULT_OBJ_AMOUNT; nCntR++)
	{
		switch (nCntR)
		{
		case 0:
			//頂点座標 D3DXVECTOR3(X,Y, 0.0f);
			pVertex[0].pos = D3DXVECTOR3(g_aResult[nCntR].pos.x, g_aResult[nCntR].pos.y + SCREEN_HEIGHT, 0.0f);
			pVertex[1].pos = D3DXVECTOR3(g_aResult[nCntR].pos.x, g_aResult[nCntR].pos.y, 0.0f);
			pVertex[2].pos = D3DXVECTOR3(g_aResult[nCntR].pos.x + SCREEN_WIDTH, g_aResult[nCntR].pos.y + SCREEN_HEIGHT, 0.0f);
			pVertex[3].pos = D3DXVECTOR3(g_aResult[nCntR].pos.x + SCREEN_WIDTH, g_aResult[nCntR].pos.y, 0.0f);
			break;

		default:
			break;
		}

		//rhwの設定
		pVertex[0].rhw = 1.0f;	//1.0f固定
		pVertex[1].rhw = 1.0f;
		pVertex[2].rhw = 1.0f;
		pVertex[3].rhw = 1.0f;

		//頂点カラーの設定
		switch (nCntR)
		{
		case 0:
			pVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //D3DCOLOR_RGBA(赤, 緑, 青, 透明度);
			pVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;

		default:
			break;
		}


		//頂点情報の設定
		pVertex[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVertex[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVertex[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVertex[3].tex = D3DXVECTOR2(1.0, 0.0);

		pVertex += 4; //頂点ポインタをずらす
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// リザルトの終了処理
//-----------------------------------------------------------------------------
void UninitResult(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	for (int nCntR = 0; nCntR < (RESULT_OBJ_AMOUNT); nCntR++)
	{
		//テクスチャの開放
		if (g_apTextureResult[nCntR] != NULL)
		{
			g_apTextureResult[nCntR]->Release();
			g_apTextureResult[nCntR] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// リザルトの更新処理
//-----------------------------------------------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_BACKSPACE) == true || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_TITLE);
	}
}

//-----------------------------------------------------------------------------
// タイトルの描画処理
//-----------------------------------------------------------------------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntR = 0; nCntR < RESULT_OBJ_AMOUNT; nCntR++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureResult[nCntR]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntR * 4, 2);
	}
}