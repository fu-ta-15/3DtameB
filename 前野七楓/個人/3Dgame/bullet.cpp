//=================================================================================================================
//
// 弾の処理　〔bullet.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "bullet.h"	//インクルードファイル
#include "input.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define MAX_BULLET (256)

//=================================================================================================================
//	弾の構造体
//=================================================================================================================
typedef struct
{	
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	bool bUse;					//使用しているかどうか
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
}BULLET;


//=================================================================================================================
//	グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
BULLET g_aBullet[MAX_BULLET];					//弾の情報

//*****************************************************************************************************************
//	弾の初期化処理
//*****************************************************************************************************************
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bulled-light-yellow.png", &g_pTextureBullet);

	//グローバル変数の初期化（弾の情報の初期化)
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		//頂点座標の設定 (XYZ)
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, -50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, -50.0f, 0.0f);


		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	弾の終了処理
//*****************************************************************************************************************
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


//*****************************************************************************************************************
//	弾の更新処理
//*****************************************************************************************************************
void UpdateBullet(void)
{
	//変数宣言
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

		for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
		{
			//使用しているなら
			if (pBullet->bUse == true)
			{
				//位置の更新
				pBullet->pos += pBullet->move;
			}
		}
}

//*****************************************************************************************************************
//	弾の描画処理
//*****************************************************************************************************************
void DrawBullet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//ビューマトリックス取得用
	D3DXMATRIX mtxView;

	//計算用マトリックス
	D3DXMATRIX  mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &g_aBullet[nCntBullet].mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxWorld, NULL, &g_aBullet[nCntBullet].mtxView);

			//平行移動の部分は無視する
			g_aBullet[nCntBullet].mtxWorld._41 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._42 = 0.0f;
			g_aBullet[nCntBullet].mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);	//
		}
	}
}
//*****************************************************************************************************************
//	弾の設定
//*****************************************************************************************************************
void SetBullet(D3DXVECTOR3 pos,  D3DXVECTOR3 move)
{
	//変数宣言
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		//もし
		if (pBullet->bUse == false)
		{
			//引数をむすびつける
			pBullet->pos = pos;
			pBullet->move = move;
			pBullet->bUse = true;
			break;
		}
	}
}