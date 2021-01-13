#include "Tutorial.h"
#include "Fade.h"
#include "Input.h"
#include "Xinput.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TUTORIAL_COMPONENT] = {};
TUTORIAL *pTutorial;
int g_nCntAnimeTutorial;
D3DXCOLOR g_colorFade1;
HRESULT InitTutorial(void)
{
	g_colorFade1 = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_nCntAnimeTutorial = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pTutorial = (TUTORIAL *)malloc(TUTORIAL_COMPONENT * sizeof(TUTORIAL));

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/tutorial.png", &g_pTextureTutorial[0])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/danger.jpg", &g_pTextureTutorial[1])))return E_FAIL;

	pTutorial[0].bUse = true;
	pTutorial[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTutorial[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	pTutorial[1].bUse = true;
	pTutorial[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTutorial[1].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TUTORIAL_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL))) return E_FAIL;

	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < TUTORIAL_COMPONENT; nCntTitle++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pTutorial[nCntTitle].pos.x - pTutorial[nCntTitle].size.x, pTutorial[nCntTitle].pos.y - pTutorial[nCntTitle].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTutorial[nCntTitle].pos.x + pTutorial[nCntTitle].size.x, pTutorial[nCntTitle].pos.y - pTutorial[nCntTitle].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTutorial[nCntTitle].pos.x - pTutorial[nCntTitle].size.x, pTutorial[nCntTitle].pos.y + pTutorial[nCntTitle].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTutorial[nCntTitle].pos.x + pTutorial[nCntTitle].size.x, pTutorial[nCntTitle].pos.y + pTutorial[nCntTitle].size.y, 0.0f);
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
	g_pVtxBuffTutorial->Unlock();
	return S_OK;
}

void UninitTutorial(void)
{
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	for (int nCnt = 0; nCnt < TUTORIAL_COMPONENT; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	free(pTutorial);
}

void UpdateTutorial(void)
{
	GAMEPAD *pPad = GetGamePad();
	VERTEX_2D *pVtx;
	g_nCntAnimeTutorial++;
	if (g_nCntAnimeTutorial > 200)
	{
		g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[4].col = g_colorFade1;
		pVtx[5].col = g_colorFade1;
		pVtx[6].col = g_colorFade1;
		pVtx[7].col = g_colorFade1;
		if (g_colorFade1.a != 0)
			g_colorFade1.a -= 0.01f;
		g_pVtxBuffTutorial->Unlock();
	}

	if ((GetkeyboardTrigger(DIK_RETURN) == true || pPad->bStart == true) && g_colorFade1 == 0)
	{
		SetFade(FADE_OUT, MODE_STAGE);
		pPad->bStart = false;
	}
}

void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TUTORIAL_COMPONENT; nCnt++)
	{
		if (pTutorial[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTutorial[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}