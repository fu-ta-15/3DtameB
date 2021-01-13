#include "Title.h"
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_COMPONENT] = {};
TITLE *pTitle;
int g_nCntAnimeTl1;
HRESULT InitTitle(void)
{
	g_nCntAnimeTl1 = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pTitle = (TITLE *)malloc(TITLE_COMPONENT * sizeof(TITLE));

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/TitleBackGround.png", &g_pTextureTitle[0])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/TeamLogo.png", &g_pTextureTitle[1])))return E_FAIL;

	pTitle[0].bUse = true;
	pTitle[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTitle[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	pTitle[1].bUse = false;
	pTitle[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTitle[1].size = D3DXVECTOR2(0, 0);

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL))) return E_FAIL;

	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < TITLE_COMPONENT; nCntTitle++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pTitle[nCntTitle].pos.x - pTitle[nCntTitle].size.x, pTitle[nCntTitle].pos.y - pTitle[nCntTitle].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTitle[nCntTitle].pos.x + pTitle[nCntTitle].size.x, pTitle[nCntTitle].pos.y - pTitle[nCntTitle].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTitle[nCntTitle].pos.x - pTitle[nCntTitle].size.x, pTitle[nCntTitle].pos.y + pTitle[nCntTitle].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTitle[nCntTitle].pos.x + pTitle[nCntTitle].size.x, pTitle[nCntTitle].pos.y + pTitle[nCntTitle].size.y, 0.0f);
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
	g_pVtxBuffTitle->Unlock();
	return S_OK;
}

void UninitTitle(void)
{
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	for (int nCnt = 0; nCnt < TITLE_COMPONENT; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
	free(pTitle);
}

void UpdateTitle(void)
{
	VERTEX_2D *pVtx;
	pTitle[1].bUse = true;
	g_nCntAnimeTl1++;
	if (g_nCntAnimeTl1 > 100)
	{
		if (pTitle[1].size.x < WIDTH_SCREEN / 3)
		{
			pTitle[1].size.x += 350 / 2;
			pTitle[1].size.y += 108 / 2;
		}
		if (g_nCntAnimeTl1 > 300) SetFade(FADE_OUT, MODE_TITLE1);
	}
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[4].pos = D3DXVECTOR3(pTitle[1].pos.x - pTitle[1].size.x, pTitle[1].pos.y - pTitle[1].size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(pTitle[1].pos.x + pTitle[1].size.x, pTitle[1].pos.y - pTitle[1].size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(pTitle[1].pos.x - pTitle[1].size.x, pTitle[1].pos.y + pTitle[1].size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(pTitle[1].pos.x + pTitle[1].size.x, pTitle[1].pos.y + pTitle[1].size.y, 0.0f);
	g_pVtxBuffTitle->Unlock();
}

void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TITLE_COMPONENT; nCnt++)
	{
		if (pTitle[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
