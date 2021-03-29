//-----------------------------------------------------------------------------
//
// ポータルの処理 [portal.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "portal.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffPortal = NULL;									// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePortal = NULL;											// ポリゴンのテクスチャへのポインタ
Portal g_portal;																	// ポータルの情報

//-----------------------------------------------------------------------------
// ポータルの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitPortal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ポータルの情報初期化
	g_portal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_portal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_portal.bActive = false;
	g_portal.bDraw = false;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//portal.png", &g_pTexturePortal);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT,					//サイズ
		D3DUSAGE_WRITEONLY,									//
		FVF_VERTEX_3D,										//フォーマット
		D3DPOOL_MANAGED,									//
		&g_pVtxBuffPortal,									//頂点バッファへのポインタ
		NULL);

	VERTEX_3D *pVertex;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPortal->Lock(0, 0, (void**)&pVertex, 0);

	//頂点座標設定
	pVertex[0].pos = D3DXVECTOR3(-PORTAL_WIDTH, 0.0f, 0.0f);
	pVertex[1].pos = D3DXVECTOR3(-PORTAL_WIDTH, PORTAL_HEIGHT, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(PORTAL_WIDTH, 0.0f, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(PORTAL_WIDTH, PORTAL_HEIGHT, 0.0f);

	//法線ベクトルの設定
	pVertex[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertex[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertex[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVertex[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVertex[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPortal->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Portal終了処理
//-----------------------------------------------------------------------------
void UninitPortal(void)
{
	//テクスチャの破棄
	if (g_pTexturePortal != NULL)
	{
		g_pTexturePortal->Release();
		g_pTexturePortal = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPortal != NULL)
	{
		g_pVtxBuffPortal->Release();
		g_pVtxBuffPortal = NULL;
	}
}

//-----------------------------------------------------------------------------
// Portal更新処理
//-----------------------------------------------------------------------------
void UpdatePortal(void)
{
	//if portal is active
	if (g_portal.bActive == true)
	{
		Player *pPlayer = GetPlayer();

		//ポータルとプレイヤーの衝突判定
		if (CollisionBoxBox(&pPlayer->pos, &g_portal.pos, PlAYER_WIDTH, PlAYER_WIDTH, PORTAL_WIDTH, 10.0f) == true)
		{
			//ステージ遷移
			Stage *pStage = GetStage();

			if (pStage->nStageNum < 2)
			{
				pStage->nStageNum++;
				SetFade(FADE_OUT, MODE_GAME);
			}
			else
			{
				pStage->nStageNum = 0;
				SetFade(FADE_OUT, MODE_RANKING);
			}

			//ポータルを使用不可に
			g_portal.bActive = false;
		}
	}
}

//-----------------------------------------------------------------------------
// Portal描画処理
//-----------------------------------------------------------------------------
void DrawPortal(void)
{
	if (g_portal.bDraw == true)
	{
		LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
		D3DXMATRIX mtxView;					// ビューマトリックス取得
		D3DXMATRIX mtxTrans, mtxRot;		// 計算用マトリックス

		//デバイス取得
		pDevice = GetDevice();

		//カリングの設定
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_portal.mtxWorld);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_portal.rot.y, g_portal.rot.x, g_portal.rot.z);
		D3DXMatrixMultiply(&g_portal.mtxWorld, &g_portal.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_portal.pos.x, g_portal.pos.y, g_portal.pos.z);
		D3DXMatrixMultiply(&g_portal.mtxWorld, &g_portal.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_portal.mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPortal, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePortal);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//カリングの設定を戻す
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//-----------------------------------------------------------------------------
// ポータルのアクティブ状態を変更
//-----------------------------------------------------------------------------
void ActivatePortal(bool bActive, bool bDraw)
{
	//ポータルが使えるかどうかを変更
	if (bActive == true) g_portal.bActive = true;
	else g_portal.bActive = false;

	//ポータルを描画するかどうか
	if (bDraw == true) g_portal.bDraw = true;
	else g_portal.bDraw = false;
}