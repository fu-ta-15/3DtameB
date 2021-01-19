//-----------------------------------------------------------------------------
//
// タイトルの処理 [title.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// マクロ
//-----------------------------------------------------------------------------
#define TITLE_OBJ_AMOUNT (1)													//タイトルのオブジェクト数

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffTitle = NULL;								//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_OBJ_AMOUNT] = { NULL };				//ポリゴンのテクスチャへのポインタ
TITLE g_aTitle[TITLE_OBJ_AMOUNT];												//TITLE構造体の情報

//-----------------------------------------------------------------------------
// タイトルの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVertex;

	//TITLEの初期化
	g_aTitle[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title_bg.jpg", &g_pTextureTitle[0]);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * TITLE_OBJ_AMOUNT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVertex, 0);

	for (int nCntT = 0; nCntT < TITLE_OBJ_AMOUNT; nCntT++)
	{
		switch (nCntT)
		{
		case 0:
			//頂点座標 D3DXVECTOR3(X,Y, 0.0f);
			pVertex[0].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x, g_aTitle[nCntT].pos.y +SCREEN_HEIGHT, 0.0f);
			pVertex[1].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x, g_aTitle[nCntT].pos.y, 0.0f);
			pVertex[2].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x + SCREEN_WIDTH, g_aTitle[nCntT].pos.y + SCREEN_HEIGHT, 0.0f);
			pVertex[3].pos = D3DXVECTOR3(g_aTitle[nCntT].pos.x + SCREEN_WIDTH, g_aTitle[nCntT].pos.y, 0.0f);
			break;

		default:
			break;
		}

		//rhwの設定
		pVertex[0].rhw = 1.0f;	//1.0f固定
		pVertex[1].rhw = 1.0f;
		pVertex[2].rhw = 1.0f;
		pVertex[3].rhw = 1.0f;

		switch (nCntT)
		{
		case 0:
			//頂点カラーの設定
			pVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //D3DCOLOR_RGBA(赤, 緑, 青, 透明度);
			pVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;

		default:
			break;
		}

		//頂点情報の設定
		pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVertex += 4; //頂点ずらし
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//フェードイン
	SetFade(FADE_IN, MODE_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------
// タイトルの終了処理
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTex = 0; nCntTex < TITLE_OBJ_AMOUNT; nCntTex++)
	{
		//テクスチャの開放
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}

}

//-----------------------------------------------------------------------------
// タイトルの更新処理
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//-----------------------------------------------------------------------------
// タイトルの描画処理
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntTex = 0; nCntTex < TITLE_OBJ_AMOUNT; nCntTex++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTex]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}
}