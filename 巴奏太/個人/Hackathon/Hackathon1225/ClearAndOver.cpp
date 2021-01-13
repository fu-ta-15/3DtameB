//========================================================*==*************************===================
//
// [OverAndClear.cpp]
// Author : Yo Jitaku
//
//=============================================================================
#include "ClearAndOver.h"
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOAC = NULL;//頂点buffのpointer
LPDIRECT3DTEXTURE9 g_pTextureOAC[2] = {};//画像のpointer
OAC g_aOAC[2];//gameover and gameclear
int g_nCntTimeOAC;

HRESULT InitOAC(void)
{
	LPDIRECT3DDEVICE9 pDeviceOAC = GetDevice();
	VERTEX_2D *pVtx;
	//初期化
	g_nCntTimeOAC = 0;
	g_aOAC[0].bUse = false;
	g_aOAC[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	g_aOAC[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0.0f);
	g_aOAC[1].bUse = false;
	g_aOAC[1].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	g_aOAC[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0.0f);

	D3DXCreateTextureFromFile(pDeviceOAC, "data/Texture/GameOver.png", &g_pTextureOAC[0]);
	D3DXCreateTextureFromFile(pDeviceOAC, "data/Texture/GameClear.png", &g_pTextureOAC[1]);

	if (FAILED(pDeviceOAC->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffOAC, NULL))) return E_FAIL;

	g_pVtxBuffOAC->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < 2; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aOAC[nCnt].pos.x - g_aOAC[nCnt].size.x, g_aOAC[nCnt].pos.y - g_aOAC[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aOAC[nCnt].pos.x + g_aOAC[nCnt].size.x, g_aOAC[nCnt].pos.y - g_aOAC[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aOAC[nCnt].pos.x - g_aOAC[nCnt].size.x, g_aOAC[nCnt].pos.y + g_aOAC[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aOAC[nCnt].pos.x + g_aOAC[nCnt].size.x, g_aOAC[nCnt].pos.y + g_aOAC[nCnt].size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	g_pVtxBuffOAC->Unlock();
	return S_OK;
}

void UninitOAC(void)
{
	if (g_pVtxBuffOAC != NULL)
	{
		g_pVtxBuffOAC->Release();
		g_pVtxBuffOAC = NULL;
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureOAC[nCnt] != NULL)
		{
			g_pTextureOAC[nCnt]->Release();
			g_pTextureOAC[nCnt] = NULL;
		}
	}
}

void UpdateOAC(void)
{
	g_nCntTimeOAC++;
	if (g_nCntTimeOAC % 100 == 0) SetFade(FADE_OUT, MODE_RANKING);
}

void DrawOAC(void)
{
	LPDIRECT3DDEVICE9 pDeviceOAC = GetDevice();

	pDeviceOAC->SetStreamSource(0, g_pVtxBuffOAC, 0, sizeof(VERTEX_2D));//頂点Data flowの設定
	pDeviceOAC->SetFVF(FVF_VERTEX_2D);//頂点modの設定

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_aOAC[nCnt].bUse == true)
		{
			pDeviceOAC->SetTexture(0, g_pTextureOAC[nCnt]);//Textureの設定
			pDeviceOAC->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);//頂点の描画
		}
	}
}

OAC *GetOAC(void)
{
	return &g_aOAC[0];
}