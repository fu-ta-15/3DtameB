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
D3DXVECTOR3 g_posButton[CA_BUTTON_NUM];
D3DXMATRIX g_mtxWorldParent;
D3DXMATRIX g_mtxWorldChild;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	//初期化
	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
	{
		g_posButton[nCntBtn] = D3DXVECTOR3(nCntBtn * CA_BUTTON_SPACE + CA_BUTTON_POS_X, CA_BUTTON_POS_Y, 0.0f);
		g_button.pos[nCntBtn] = g_posButton[nCntBtn];
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command A00.png", &g_button.pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command B00.png", &g_button.pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command X00.png", &g_button.pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command Y00.png", &g_button.pTexture[3]);

	//頂点バッファの生成 ボタン
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * CA_BUTTON_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_button.pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexButton;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_button.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
	{
		//頂点座標 D3DXVECTOR3(X,Y, 0.0f);
		pVertexButton[0].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x, g_button.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIPで四角
		pVertexButton[1].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x, g_button.pos[nCntBtn].y, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_button.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_button.pos[nCntBtn].y, 0.0f);

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
	VERTEX_2D *pVertexButton;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_button.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
	{
		//頂点座標 D3DXVECTOR3(X,Y, 0.0f);
		pVertexButton[0].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x, g_button.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIPで四角
		pVertexButton[1].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x, g_button.pos[nCntBtn].y, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_button.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(g_button.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_button.pos[nCntBtn].y, 0.0f);
	}
	//頂点バッファをアンロックする
	g_button.pVtxBuff->Unlock();
}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void DrawCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_button.pVtxBuff, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_button.pTexture[nCntBtn]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBtn * 4, 2);
	}
}