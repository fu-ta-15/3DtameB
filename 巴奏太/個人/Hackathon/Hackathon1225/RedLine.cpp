////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 判定ラインの処理 [RedLine.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/25
//
////////////////////////////////////////////////////////////////////////////////
#include "RedLine.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRedLine = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureRedLine = NULL;		//テクスチャのポインタ
D3DXVECTOR3 posRedLine;								//位置
D3DXVECTOR3 rotRedLine;								//向き
D3DXMATRIX	mtxworldRedLine;						//ワールドマトリックス

////////////////////////////////////////////////////////////////////////////////
//壁の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitRedLine(void)
{
	//変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bga.png", &g_pTextureRedLine);

	posRedLine = D3DXVECTOR3(0.0f, 60.0f, 200.0f);
	rotRedLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffRedLine, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRedLine->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-500, -300, 0);
	pVtx[1].pos = D3DXVECTOR3(-500, 300, 0);
	pVtx[2].pos = D3DXVECTOR3(500, -300, 0);
	pVtx[3].pos = D3DXVECTOR3(500, 300, 0);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);

	//頂点バッファをアンロックする
	g_pVtxBuffRedLine->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//壁の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitRedLine(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffRedLine != NULL)
	{
		g_pVtxBuffRedLine->Release();	//開放
		g_pVtxBuffRedLine = NULL;		//初期化
	}
	if (g_pTextureRedLine != NULL)
	{
		g_pTextureRedLine->Release();	//開放
		g_pTextureRedLine = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//壁の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateRedLine(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//壁の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawRedLine(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	// ◆アルファブレンディングを行なう
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// ◆アルファブレンディングステートを設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxworldRedLine);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotRedLine.y, rotRedLine.x, rotRedLine.z);
	D3DXMatrixMultiply(&mtxworldRedLine, &mtxworldRedLine, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, posRedLine.x, posRedLine.y, posRedLine.z);
	D3DXMatrixMultiply(&mtxworldRedLine, &mtxworldRedLine, &mtxTrans);

	//ワールドマトリックス
	pDevice->SetTransform(D3DTS_WORLD, &mtxworldRedLine);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRedLine, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}