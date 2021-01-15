//===================================================================
//
// 弾の処理　[bullet.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "bullet.h"
#include "billboard.h"

//===========================================================================================================
//マクロ定義
//===========================================================================================================
#define MAX_BULLET (512)					//弾の最大数
#define BULLET_SIZE (5)					//弾の大きさ

//=================================================================================================
//グローバル変数
//=================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;														//弾のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;												//バッファの
BULLET g_aBullet[MAX_BULLET];																	//弾の情報	
D3DXMATRIX g_mtxWorldBullet;																	//ワールドマトリックス

//=================================================================================================
//プロトタイプ宣言
//=================================================================================================
void SetVertexBullet(int nIdy);

//=================================================================================================
//初期化処理
//=================================================================================================
HRESULT InitBullet(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	//弾の設定
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		SetVertexBullet(nCntBullet);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//頂点テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//=================================================================================================
//終了処理
//=================================================================================================
void UninitBullet(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//=================================================================================================
//更新処理
//=================================================================================================
void UpdateBullet(void)
{
	//変数宣言
	BULLET *pBullet;

	VERTEX_3D *pVtx;

	pBullet = &g_aBullet[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		//弾の更新
		if (pBullet->bUse == true)			//弾が使われているか
		{
			//位置の更新
			pBullet->pos += pBullet->move;

			//頂点座標の設定
			SetVertexBullet(nCntBullet);

			//エフェクトの設定
			//SetEffect(pBullet->pos);

			/*ENEMY *pEnemy;
			pEnemy = GetENEMY();*/

			if (pBullet->type)
			{
				switch (pBullet->type)
				{
				case PLAYER_BULLET:
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					break;

				case ENEMY_BULLET:
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					break;
				}
			}

			//寿命チェック
			pBullet->nLife--;

			if (pBullet->nLife <= 0)
			{
				pBullet->bUse = false;
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=================================================================================================
//描画処理
//=================================================================================================
void DrawBullet(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ
	D3DXMATRIX mtxView;								//ビューマトリックス取得用				
	D3DXMATRIX mtxTrans;							//計算用マトリックス
	BULLET *pBullet;

	pBullet = GetBullet();

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			//Zテスト
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				//Zバッファの更新

	//ポリゴンの描画
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);				//逆行列を求める

			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=================================================================================================
//弾の頂点座標の設定
//=================================================================================================
void SetVertexBullet(int nIdy)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdy * 4;

	//弾の頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x - BULLET_SIZE, g_aBullet[nIdy].pos.y + BULLET_SIZE, g_aBullet[nIdy].pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x + BULLET_SIZE, g_aBullet[nIdy].pos.y + BULLET_SIZE, g_aBullet[nIdy].pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x - BULLET_SIZE, g_aBullet[nIdy].pos.y - BULLET_SIZE, g_aBullet[nIdy].pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdy].pos.x + BULLET_SIZE, g_aBullet[nIdy].pos.y - BULLET_SIZE, g_aBullet[nIdy].pos.z);

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=================================================================================================
//弾の設定
//=================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	//変数宣言
	BULLET *pBullet;
	VERTEX_3D *pVtx;

	pBullet = &g_aBullet[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//位置の設定
			pBullet->pos = pos;

			//移動量を設定
			pBullet->move = move;

			//頂点座標の設定
			SetVertexBullet(nCntBullet);

			//寿命を設定
			pBullet->nLife = nLife;

			pBullet->bUse = true;

			break;

		}
		//pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//===========================================================================================================
//弾の取得
//===========================================================================================================
BULLET *GetBullet(void)
{
	return *&g_aBullet;
}