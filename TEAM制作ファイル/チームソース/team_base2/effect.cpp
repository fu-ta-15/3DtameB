//##################################################################################################################################################################//
//
// エフェクト処理 [effect.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "effect.h"
#include <time.h>
#include "portal.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define EFFECT_SIZEW					(6.0f)						// 弾のサイズ
#define EFFECT_SIZEH					(8.0f)						// 弾のサイズ
#define COLOR_RED						(255)						// 赤色
#define COLOR_BULUE						(255)						// 青色
#define COLOR_GREEN						(255)						// 緑色
#define COLOR_ALPHA						(255)						// アルファ値
#define PVTEX_MAX						(4)							// pVtx
#define MAX_EFFECT						(3000)						// 弾の最大数


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
}Portal_Effect;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureEffect = NULL;		// テクスチャの情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファの情報
Effect g_aEffect[MAX_EFFECT];						// エフェクトの情報
Portal_Effect g_PE[MAX_EFFECT];



//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ
	Effect *pEffect = &g_aEffect[0];
	Portal *pPortal = &GetPortal();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Particle04_clear_hard.png", &g_apTextureEffect);

	if (g_apTextureEffect == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\bullet000.png");
	}

	// 弾の初期化設定
	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		pEffect->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->posdest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);
		pEffect->type = EFFECT_TYPE_NOT;
		pEffect->EffectSizeW = EFFECT_SIZEW;
		pEffect->EffectSizeH = EFFECT_SIZEH;
		pEffect->fAngle = 0.0f;
		pEffect->fRadius = 0.0f;
		pEffect->nFrame = 0;
		pEffect->nCnt = 0;
		pEffect->nIdx = 0;
		pEffect->nLife = 0;
		pEffect->bUse = false;

		g_PE[nCntBullet].pos = pPortal->pos;
		g_PE[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pEffect = &g_aEffect[0];

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		// 各頂点座標
		pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - pEffect->EffectSizeW, pEffect->pos.y + pEffect->EffectSizeH, pEffect->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x + pEffect->EffectSizeW, pEffect->pos.y + pEffect->EffectSizeH, pEffect->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x - pEffect->EffectSizeW, pEffect->pos.y - pEffect->EffectSizeH, pEffect->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + pEffect->EffectSizeW, pEffect->pos.y - pEffect->EffectSizeH, pEffect->pos.z);

		pVtx[0].nor = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);

		// 頂点カラーの設定・赤・緑・青
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		// テクスチャの頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// プラス4進める
		pVtx += PVTEX_MAX;
	}

	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitEffect(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
	if (g_apTextureEffect != NULL)
	{
		g_apTextureEffect->Release();
		g_apTextureEffect = NULL;
	}
}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateEffect(void)
{
	// 構造体の情報取得
	Effect *pEffect;
	pEffect = &g_aEffect[0];

	//エフェクトの最大値まで回す
	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		switch (pEffect->type)
		{// そのエフェクトは何のタイプですか

		case EFFECT_TYPE_NORMAL://ノーマル
			EffectOn();
			break;

		case EFFECT_TYPE_PORTAL://ポータル用
			EffectPortalOn();
			break;

		default:
			break;
		}
	}

}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawEffect(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxTrans, mtxRot;		// 計算用マトリックス
	// ビューマトリックス取得用
	D3DXMATRIX mtxView;
	// 構造体の情報取得
	Effect *pEffect;
	pEffect = &g_aEffect[0];
	Portal *pPortal = &GetPortal();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//カリングの設定

	// ライトをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_PE[nCntBullet].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PE[nCntBullet].rot.y, g_PE[nCntBullet].rot.x, g_PE[nCntBullet].rot.z);
			D3DXMatrixMultiply(&g_PE[nCntBullet].mtxWorld, &g_PE[nCntBullet].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_PE[nCntBullet].pos.x, g_PE[nCntBullet].pos.y, g_PE[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_PE[nCntBullet].mtxWorld, &g_PE[nCntBullet].mtxWorld, &mtxTrans);

			// 計算用マトリックス
			D3DXMATRIX mtxTrans, mtxRot;		// 計算用マトリックス

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pEffect->rot.y, pEffect->rot.x, pEffect->rot.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxTrans);

			//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &g_PE[nCntBullet].mtxWorld);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEffect);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);

		}
	}
	//ライトをオフにする														
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//通常合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

void EffectOn(void)
{
	// 構造体のポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	Effect *pEffect;
	pEffect = &g_aEffect[0];

	// 頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			// 過去の位置を保存
			pEffect->oldpos = pEffect->pos;

			// 位置の更新
			pEffect->move.y -= 1.3f;
			pEffect->pos.z += pEffect->move.z;
			pEffect->pos.x += pEffect->move.x;
			pEffect->pos.y += pEffect->move.y;

			// 移動量の減衰
			pEffect->move.z += (0.0f - pEffect->move.z) * 0.4f;
			pEffect->move.x += (0.0f - pEffect->move.x) * 0.4f;
			pEffect->move.y += (0.0f - pEffect->move.y) * 0.013f;

			if (pEffect->oldpos.y - EFFECT_SIZEW < 0)
			{// 前回の位置が床より下に行ったら

			 // 移動の設定
				float fAngle = (float)((rand() % 628) - 628) / 100.f;

				pEffect->move.z = cosf(fAngle + D3DX_PI) * 8.0f;
				pEffect->move.x = sinf(fAngle - D3DX_PI) * 8.0f;

				pEffect->pos.y = 0 + EFFECT_SIZEW;
				pEffect->move.y += 20.0f;
			}

			// ライフの減少
			pEffect->nLife -= 1;

			// 寿命チェック
			if (pEffect->nLife == 0)
			{
				// 0になったらフォルスに変える
				pEffect->bUse = false;
			}
		}
		// 4頂点ずつずれる
		pVtx += PVTEX_MAX;
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}

//=====================================================================================================================================================================//
// エフェクトの設定処理
//=====================================================================================================================================================================//
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float movex, float movez, float movey, int nIdx, int nLife)
{
	//ポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	Effect *pEffect;
	pEffect = &g_aEffect[0];


	//頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//弾の設定
	for (int nCntBullet = 0; nCntBullet < nIdx; nCntBullet++, pEffect++)
	{
			if (pEffect->bUse == false)
			{//使用されていない弾


			 // 位置の設定
				pEffect->pos.x = pos.x;
				pEffect->pos.z = pos.z;
				pEffect->pos.y = pos.y;

				// 移動の設定
				float fAngle = (float)((rand() % 628) - 628) / 100.f;

				// 情報代入
				pEffect->move.z = cosf(fAngle + D3DX_PI) * 3.0f;
				pEffect->move.x = sinf(fAngle - D3DX_PI) * 3.0f;
				pEffect->move.y = movey ;

				// 色情報を設定
				pEffect->color.r = col.r;
				pEffect->color.b = col.b;
				pEffect->color.g = col.g;
				pEffect->color.a = col.a;

				// 色情報を代入
				pVtx[0].col = pEffect->color;
				pVtx[1].col = pEffect->color;
				pVtx[2].col = pEffect->color;
				pVtx[3].col = pEffect->color;

				// 寿命の設定
				pEffect->nLife = nLife;

				// 弾を発射
				pEffect->bUse = true;

				break;
			}
		pVtx += PVTEX_MAX;	// 頂点情報を4進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}

// ポータルのエフェクト更新
void EffectPortalOn(void)
{
	// 構造体のポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	Effect *pEffect;
	pEffect = &g_aEffect[0];
	Portal *pPortal = &GetPortal();

	// 頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);



	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{

			g_PE[nCntBullet].rot.z += 0.0002f;

			// 回転の修正 (3.14超えたら±逆に)
			if (g_PE[nCntBullet].rot.y > D3DX_PI)
			{
				g_PE[nCntBullet].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_PE[nCntBullet].rot.y < -D3DX_PI)
			{
				g_PE[nCntBullet].rot.y += D3DX_PI * 2.0f;
			}

			pEffect->nCnt++;

			// 位置の更新
			pEffect->posdest.y = (0.0f - pEffect->pos.y) * 0.0001f;
			pEffect->posdest.x = (pPortal->pos.x - pEffect->pos.x) * 0.0001f;

			pEffect->pos.y += pEffect->posdest.y;
			pEffect->pos.x += pEffect->posdest.x;

			// ライフの減少
			pEffect->nLife -= 1;

			// 寿命チェック
			if (pEffect->nLife == 0)
			{
				// 0になったらフォルスに変える
				pEffect->bUse = false;
			}
		}
		// 4頂点ずつずれる
		pVtx += PVTEX_MAX;
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}

// ポータルのエフェクト
void SetEffectPortal(D3DXVECTOR3 pos,D3DXVECTOR3 posDest, D3DXCOLOR col, D3DXVECTOR3 move, D3DXVECTOR3 posdicetance, int nIdx, int nLife, int nFrame)
{
	//ポインタ
	VERTEX_3D *pVtx;

	// 構造体の情報取得
	Effect *pEffect;
	pEffect = &g_aEffect[0];

	//頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);


	//弾の設定
	for (int nCntBullet = 0; nCntBullet < nIdx; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == false)
		{//使用されていない弾

		 // 移動の設定
			float fAngle = (float)((rand() % 628) - 628) / 100.f;

			pEffect->posdest.x = posDest.x;
			pEffect->posdest.y = posDest.y;
			pEffect->posdest.z = posDest.z;

		 // 位置の設定
			pEffect->pos.x = sinf(fAngle - D3DX_PI + posdicetance.x) * 100.0f;
			pEffect->pos.y = cosf(fAngle + D3DX_PI + posdicetance.y) * 100.0f;
			pEffect->pos.z = posDest.z;


			// 情報代入
			pEffect->move.z = 0;
			pEffect->move.x = sinf(fAngle - D3DX_PI) * 3.0f;
			pEffect->move.y = cosf(fAngle + D3DX_PI) * 3.0f;

			// 色情報を設定
			pEffect->color.r = col.r;
			pEffect->color.b = col.b;
			pEffect->color.g = col.g;
			pEffect->color.a = col.a;

			// 色情報を代入
			pVtx[0].col = pEffect->color;
			pVtx[1].col = pEffect->color;
			pVtx[2].col = pEffect->color;
			pVtx[3].col = pEffect->color;

			// 寿命の設定
			pEffect->nLife = nLife+10000;
			pEffect->nFrame = nFrame;

			pEffect->type = EFFECT_TYPE_PORTAL;

			// 弾を発射
			pEffect->bUse = true;

			break;
		}
		pVtx += PVTEX_MAX;	// 頂点情報を4進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();
}


Effect * GetEffect(void)
{
	return &g_aEffect[0];
}

