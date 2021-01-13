#include "Title1.h"
#include "Fade.h"
#include "Xinput.h"
#include "Input.h"
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle1 = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTitle1[TITLE1_COMPONENT] = {};
TITLE1 *pTitle1;
int g_nCntAnimeTl2;
int g_nCntAnimeTl3;
HRESULT InitTitle1(void)
{
	g_nCntAnimeTl2 = 0;
	g_nCntAnimeTl3 = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pTitle1 = (TITLE1 *)malloc(TITLE1_COMPONENT * sizeof(TITLE1));

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/Title1BackGround.jpg", &g_pTextureTitle1[0])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/GameLogo.png", &g_pTextureTitle1[1])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/PressButton.png", &g_pTextureTitle1[2])))return E_FAIL;

	pTitle1[0].bUse = true;
	pTitle1[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTitle1[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	pTitle1[1].bUse = true;
	pTitle1[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, -1000, 0);
	pTitle1[1].size = D3DXVECTOR2(WIDTH_SCREEN / 4, HEIGHT_SCREEN / 5);

	pTitle1[2].bUse = false;
	pTitle1[2].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, 800, 0);
	pTitle1[2].size = D3DXVECTOR2(WIDTH_SCREEN / 4, HEIGHT_SCREEN / 8);

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE1_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle1, NULL))) return E_FAIL;

	g_pVtxBuffTitle1->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < TITLE1_COMPONENT; nCntTitle++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pTitle1[nCntTitle].pos.x - pTitle1[nCntTitle].size.x, pTitle1[nCntTitle].pos.y - pTitle1[nCntTitle].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTitle1[nCntTitle].pos.x + pTitle1[nCntTitle].size.x, pTitle1[nCntTitle].pos.y - pTitle1[nCntTitle].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTitle1[nCntTitle].pos.x - pTitle1[nCntTitle].size.x, pTitle1[nCntTitle].pos.y + pTitle1[nCntTitle].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTitle1[nCntTitle].pos.x + pTitle1[nCntTitle].size.x, pTitle1[nCntTitle].pos.y + pTitle1[nCntTitle].size.y, 0.0f);
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
	g_pVtxBuffTitle1->Unlock();
	return S_OK;
}

void UninitTitle1(void)
{
	if (g_pVtxBuffTitle1 != NULL)
	{
		g_pVtxBuffTitle1->Release();
		g_pVtxBuffTitle1 = NULL;
	}
	for (int nCnt = 0; nCnt < TITLE1_COMPONENT; nCnt++)
	{
		if (g_pTextureTitle1[nCnt] != NULL)
		{
			g_pTextureTitle1[nCnt]->Release();
			g_pTextureTitle1[nCnt] = NULL;
		}
	}
	free(pTitle1);
}

void UpdateTitle1(void)
{
	VERTEX_2D *pVtx;
	GAMEPAD *pPad = GetGamePad();
	g_nCntAnimeTl2++;
	g_nCntAnimeTl3++;
	if (g_nCntAnimeTl2 % 1 == 0) if (pTitle1[1].pos.y < 350)  pTitle1[1].pos.y += 10;
	
	if (g_nCntAnimeTl3 % 50 == 0 && pTitle1[1].pos.y >= 350) 
		pTitle1[2].bUse = !pTitle1[2].bUse;

	if ((GetkeyboardTrigger(DIK_RETURN) == true || pPad->bStart == true))
	{
		SetFade(FADE_OUT, MODE_TUTORIAL);
		pPad->bStart = false;
	}

	g_pVtxBuffTitle1->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[4].pos = D3DXVECTOR3(pTitle1[1].pos.x - pTitle1[1].size.x, pTitle1[1].pos.y - pTitle1[1].size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(pTitle1[1].pos.x + pTitle1[1].size.x, pTitle1[1].pos.y - pTitle1[1].size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(pTitle1[1].pos.x - pTitle1[1].size.x, pTitle1[1].pos.y + pTitle1[1].size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(pTitle1[1].pos.x + pTitle1[1].size.x, pTitle1[1].pos.y + pTitle1[1].size.y, 0.0f);
	g_pVtxBuffTitle1->Unlock();
}

void DrawTitle1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTitle1, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TITLE1_COMPONENT; nCnt++)
	{
		if (pTitle1[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle1[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}