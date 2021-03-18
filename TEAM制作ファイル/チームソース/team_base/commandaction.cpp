//-----------------------------------------------------------------------------
//
// コマンドアクションの処理 [commandaction.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "commandaction.h"
#include "input.h"

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitCommand(void);
void UninitCommand(void);
void UpdateCommand(void);
void DrawCommand(void);

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
CAButton g_button;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	//初期化
	g_button.pos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_button.pos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_button.pos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_button.pos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandA00.png", &g_button.pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandB00.png", &g_button.pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandX00.png", &g_button.pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\commandY00.png", &g_button.pTexture[3]);

	//頂点バッファの生成 ボタン
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * CA_BUTTON_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_button.pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexButton;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_button.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntButton = 0; nCntButton < CA_BUTTON_NUM; nCntButton++, pVertexButton += 4)
	{
		//頂点座標 D3DXVECTOR3(X,Y, 0.0f);
		pVertexButton[0].pos = D3DXVECTOR3(0.0f, CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIPで四角
		pVertexButton[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(CA_BUTTON_WIDTH, CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(CA_BUTTON_WIDTH, 0.0f, 0.0f);

		//rhwの設定
		for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].rhw = 1.0f;

		//頂点カラーの設定
		for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点情報の設定
		pVertexButton[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertexButton[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertexButton[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVertexButton[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//頂点バッファをアンロックする
	g_button.pVtxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitCommand(void)
{

}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdateCommand(void)
{

}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void DrawCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	for (int nCntButton = 0; nCntButton < CA_BUTTON_NUM; nCntButton++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_button.pVtxBuff, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_button.pTexture[nCntButton]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntButton * 4, 2);
	}
}