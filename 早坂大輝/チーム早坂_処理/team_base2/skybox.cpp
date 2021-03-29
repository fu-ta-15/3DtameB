//-----------------------------------------------------------------------------
//
// スカイボックスの処理 [skybox.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "skybox.h"
#include "input.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define SKYBOX_FACES (6)	// スカイボックスの面の数 (6面)
#define SPLIT_U (4.0f)		// テクスチャの分割数
#define SPLIT_V (3.0f)		//

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9  g_pVtxBuffSky = NULL;									// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;										// ポリゴンのテクスチャへのポインタ
Skybox g_skybox[SKYBOX_FACES];													// スカイボックスの情報

//-----------------------------------------------------------------------------
// Skybox初期化処理
//-----------------------------------------------------------------------------
HRESULT InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); // device

	//初期化設定
	g_skybox[0].pos = D3DXVECTOR3(0.0f, 0.0f, SKYBOX_FACE_DISTANCE);
	g_skybox[1].pos = D3DXVECTOR3(0.0f, 0.0f, -SKYBOX_FACE_DISTANCE);
	g_skybox[2].pos = D3DXVECTOR3(SKYBOX_FACE_DISTANCE, 0.0f, 0.0f);
	g_skybox[3].pos = D3DXVECTOR3(-SKYBOX_FACE_DISTANCE, 0.0f, 0.0f);
	g_skybox[4].pos = D3DXVECTOR3(0.0f, SKYBOX_FACE_DISTANCE, 0.0f);
	g_skybox[5].pos = D3DXVECTOR3(0.0f, -SKYBOX_FACE_DISTANCE, 0.0f);
	
	g_skybox[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_skybox[1].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_skybox[2].rot = D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f);
	g_skybox[3].rot = D3DXVECTOR3(0.0f, -D3DX_PI / 2.0f, 0.0f);
	g_skybox[4].rot = D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f);
	g_skybox[5].rot = D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f);

	for (int nCntFace = 0; nCntFace < SKYBOX_FACES; nCntFace++)
	{
		g_skybox[nCntFace].bDraw = true;
	}

	//テクスチャ読み込み
	//D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//skybox.png", &g_pTextureSky);
	D3DXCreateTextureFromFileEx(pDevice, "data\\TEXTURE\\skybox1.png", 2048, 1536, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL, &g_pTextureSky);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT * SKYBOX_FACES,	//サイズ
		D3DUSAGE_WRITEONLY,									//
		FVF_VERTEX_3D,										//フォーマット
		D3DPOOL_MANAGED,									//
		&g_pVtxBuffSky,									//頂点バッファへのポインタ
		NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_3D *pVertex;
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVertex, 0);

	//6面分
	for (int nCntFace = 0; nCntFace < SKYBOX_FACES; nCntFace++, pVertex += 4)
	{
		//頂点座標設定
		pVertex[0].pos = D3DXVECTOR3(-SKYBOX_FACE_WIDTH / 2, -SKYBOX_FACE_HEIGHT / 2, 0.0f);
		pVertex[1].pos = D3DXVECTOR3(-SKYBOX_FACE_WIDTH / 2, SKYBOX_FACE_HEIGHT / 2, 0.0f);
		pVertex[2].pos = D3DXVECTOR3(SKYBOX_FACE_WIDTH / 2, -SKYBOX_FACE_HEIGHT / 2, 0.0f);
		pVertex[3].pos = D3DXVECTOR3(SKYBOX_FACE_WIDTH / 2, SKYBOX_FACE_HEIGHT / 2, 0.0f);

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
		switch (nCntFace)
		{
		case 0:	// 正面
			pVertex[0].tex = D3DXVECTOR2(1.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(1.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(2.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(2.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 1:	// 後ろ
			pVertex[0].tex = D3DXVECTOR2(3.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(3.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(4.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(4.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 2:	// 右
			pVertex[0].tex = D3DXVECTOR2(2.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(2.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(3.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(3.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 3:	// 左
			pVertex[0].tex = D3DXVECTOR2(0.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(0.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(1.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(1.0f / SPLIT_U, 1.0f / SPLIT_V);
			break;
		case 4:	// 上
			pVertex[0].tex = D3DXVECTOR2(1.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(1.0f / SPLIT_U, 0.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(2.0f / SPLIT_U, 1.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(2.0f / SPLIT_U, 0.0f / SPLIT_V);
			break;
		case 5:	// 下
			pVertex[0].tex = D3DXVECTOR2(1.0f / SPLIT_U, 3.0f / SPLIT_V);
			pVertex[1].tex = D3DXVECTOR2(1.0f / SPLIT_U, 2.0f / SPLIT_V);
			pVertex[2].tex = D3DXVECTOR2(2.0f / SPLIT_U, 3.0f / SPLIT_V);
			pVertex[3].tex = D3DXVECTOR2(2.0f / SPLIT_U, 2.0f / SPLIT_V);
			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSky->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Skybox終了処理
//-----------------------------------------------------------------------------
void UninitSky(void)
{
	//テクスチャの破棄
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}
}

//-----------------------------------------------------------------------------
// Skybox更新処理
//-----------------------------------------------------------------------------
void UpdateSky(void)
{
	if (GetKeyboardPress(DIK_F) == true)
	{
		g_skybox[0].rot.x += 0.05f;
	}
}

//-----------------------------------------------------------------------------
// Skybox描画処理
//-----------------------------------------------------------------------------
void DrawSky(void)
{
	for (int nCntFace = 0; nCntFace < SKYBOX_FACES; nCntFace++)
	{
		if (g_skybox[nCntFace].bDraw == true)
		{
			LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
			D3DXMATRIX mtxView;					// ビューマトリックス取得
			D3DXMATRIX mtxTrans, mtxRot;		// 計算用マトリックス

			//デバイス取得
			pDevice = GetDevice();

			//ライティングの影響を受けなくする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//サンプラーステートの設定
			pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);	
			pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);	
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_skybox[nCntFace].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_skybox[nCntFace].rot.y, g_skybox[nCntFace].rot.x, g_skybox[nCntFace].rot.z);
			D3DXMatrixMultiply(&g_skybox[nCntFace].mtxWorld, &g_skybox[nCntFace].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_skybox[nCntFace].pos.x, g_skybox[nCntFace].pos.y, g_skybox[nCntFace].pos.z);
			D3DXMatrixMultiply(&g_skybox[nCntFace].mtxWorld, &g_skybox[nCntFace].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_skybox[nCntFace].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSky, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSky);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFace * 4, 2);

			//RS戻す
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			//サンプラーステートの設定
			pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小時　補間
			pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大時　補間
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値　繰り返し
			pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V値　繰り返し
		}
	}
}