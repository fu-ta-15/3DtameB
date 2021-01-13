#include "UI.h"
#include "Player.h"
#include "Fade.h"
#include "ClearAndOver.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_TYPE] = {};
UI *pUI;
int nCntTime = 0;
void SetUI(void)
{
	//health
	for (int nCnt = 0; nCnt < UI_COMPONENT; nCnt++)
	{
		if (nCnt < 3)//hp
		{
			pUI[nCnt].bUse = true;
			pUI[nCnt].pos = D3DXVECTOR3(400 + (float)nCnt * 100, 950, 0);
			pUI[nCnt].size = D3DXVECTOR2(40, 40);
			pUI[nCnt].nTexture = 0;
			pUI[nCnt].nPatternAnime = 0;
		}
		else if (nCnt == 3 || nCnt == 4)
		{
			pUI[3].bUse = true;
			pUI[3].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 - 40, 100, 0);
			pUI[3].size = D3DXVECTOR2(40, 50);
			pUI[3].nDisplayNumber = 8;//表示したいnumber
			pUI[3].nZeroNumber = UI_COMPONENT - 1 - nCnt;//MAX_COMPONENT_SCORE - 1 - nCntNumber;//計算するとき　その位の後ろの0の個数
			pUI[3].nMultipleNumber = 0;//除数としての整数1->00000
			pUI[3].nTexture = 1;

			pUI[4].bUse = true;
			pUI[4].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 40, 100, 0);
			pUI[4].size = D3DXVECTOR2(40, 50);
			pUI[4].nDisplayNumber = 9;//表示したいnumber
			pUI[4].nZeroNumber = UI_COMPONENT - 1 - nCnt;//MAX_COMPONENT_SCORE - 1 - nCntNumber;//計算するとき　その位の後ろの0の個数
			pUI[4].nMultipleNumber = 0;//除数としての整数1->00000
			pUI[4].nTexture = 1;
		}
		else//score
		{
			pUI[nCnt].bUse = true;
			pUI[nCnt].pos = D3DXVECTOR3(1300 + (float)(nCnt - 6) * 60, 950, 0);
			pUI[nCnt].size = D3DXVECTOR2(20, 40);
			pUI[nCnt].nDisplayNumber = 0;//表示したいnumber
			pUI[nCnt].nZeroNumber = UI_COMPONENT - 1 - nCnt;//MAX_COMPONENT_SCORE - 1 - nCntNumber;//計算するとき　その位の後ろの0の個数
			pUI[nCnt].nMultipleNumber = 0;//除数としての整数1->00000
			pUI[nCnt].nTexture = 1;
		}
	}
}

HRESULT InitUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pUI = (UI *)malloc(UI_COMPONENT * sizeof(UI));

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP.png", &g_pTextureUI[0])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Number.png", &g_pTextureUI[1])))return E_FAIL;

	SetUI();

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * UI_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUI, NULL))) return E_FAIL;

	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntUI = 0; nCntUI < UI_COMPONENT; nCntUI++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pUI[nCntUI].pos.x - pUI[nCntUI].size.x, pUI[nCntUI].pos.y - pUI[nCntUI].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pUI[nCntUI].pos.x + pUI[nCntUI].size.x, pUI[nCntUI].pos.y - pUI[nCntUI].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pUI[nCntUI].pos.x - pUI[nCntUI].size.x, pUI[nCntUI].pos.y + pUI[nCntUI].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pUI[nCntUI].pos.x + pUI[nCntUI].size.x, pUI[nCntUI].pos.y + pUI[nCntUI].size.y, 0.0f);
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (nCntUI < 3)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
			pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
			pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		}
		else
		{
			pVtx[0].tex = D3DXVECTOR2((pUI[nCntUI].nDisplayNumber * 0.1f), 0.0);
			pVtx[1].tex = D3DXVECTOR2((pUI[nCntUI].nDisplayNumber * 0.1f + 0.1f), 0.0);
			pVtx[2].tex = D3DXVECTOR2((pUI[nCntUI].nDisplayNumber * 0.1f), 1.0);
			pVtx[3].tex = D3DXVECTOR2((pUI[nCntUI].nDisplayNumber * 0.1f + 0.1f), 1.0);
		}
	}
	g_pVtxBuffUI->Unlock();
	return S_OK;
}

void UninitUI(void)
{
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
	for (int nCnt = 0; nCnt < UI_TYPE; nCnt++)
	{
		if (g_pTextureUI[nCnt] != NULL)
		{
			g_pTextureUI[nCnt]->Release();
			g_pTextureUI[nCnt] = NULL;
		}
	}
	free(pUI);
}

void UpdateUI(void)
{
	LPDIRECT3DDEVICE9 pDeviceSc;
	pDeviceSc = GetDevice();
	Player *pPlayer = GetPlayer();
	nCntTime++;
	VERTEX_2D *pVtx;

	if (nCntTime % 60 == 0)
	{
		if (pPlayer->nTime > 0) pPlayer->nTime--;
		else
		{
			OAC *pOAC = GetOAC();
			pOAC[1].bUse = true;
			SetFade(FADE_OUT, MODE_OAC);
		}
	}

	for (int nCntNumber = 0; nCntNumber < UI_COMPONENT; nCntNumber++)
	{
		if (nCntNumber > 2)
		{
			if (nCntNumber > 4)
			{
				{
					//pow function -> headfile<math.h>
					pUI[nCntNumber].nMultipleNumber = (unsigned int)pow(10.0, pUI[nCntNumber].nZeroNumber);
					//(1.%定位 2./位取り)
					pUI[nCntNumber].nDisplayNumber = pPlayer->nScore % (pUI[nCntNumber].nMultipleNumber * 10) / pUI[nCntNumber].nMultipleNumber;
					g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
					pVtx[nCntNumber * 4 + 0].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f), 0.0);
					pVtx[nCntNumber * 4 + 1].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f + 0.1f), 0.0);
					pVtx[nCntNumber * 4 + 2].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f), 1.0);
					pVtx[nCntNumber * 4 + 3].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f + 0.1f), 1.0);
					g_pVtxBuffUI->Unlock();
				}
			}
			else if (nCntNumber == 3)
			{
				//pow function -> headfile<math.h>
				pUI[nCntNumber].nMultipleNumber = (unsigned int)pow(10.0, 1);
				//(1.%定位 2./位取り)
				pUI[nCntNumber].nDisplayNumber = pPlayer->nTime % (pUI[nCntNumber].nMultipleNumber * 10) / pUI[nCntNumber].nMultipleNumber;
				g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
				pVtx[nCntNumber * 4 + 0].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f), 0.0);
				pVtx[nCntNumber * 4 + 1].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f + 0.1f), 0.0);
				pVtx[nCntNumber * 4 + 2].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f), 1.0);
				pVtx[nCntNumber * 4 + 3].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f + 0.1f), 1.0);
				g_pVtxBuffUI->Unlock();
			}
			else if (nCntNumber == 4)
			{
				//pow function -> headfile<math.h>
				pUI[nCntNumber].nMultipleNumber = (unsigned int)pow(10.0, 0);
				//(1.%定位 2./位取り)
				pUI[nCntNumber].nDisplayNumber = pPlayer->nTime % (pUI[nCntNumber].nMultipleNumber * 10) / pUI[nCntNumber].nMultipleNumber;
				g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
				pVtx[nCntNumber * 4 + 0].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f), 0.0);
				pVtx[nCntNumber * 4 + 1].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f + 0.1f), 0.0);
				pVtx[nCntNumber * 4 + 2].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f), 1.0);
				pVtx[nCntNumber * 4 + 3].tex = D3DXVECTOR2((pUI[nCntNumber].nDisplayNumber * 0.1f + 0.1f), 1.0);
				g_pVtxBuffUI->Unlock();
			}
		}
		else
		{
			if (nCntNumber < pPlayer->nHp) pUI[nCntNumber].bUse = true;
			else pUI[nCntNumber].bUse = false;
		}
	}

	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	if (pPlayer->bHit == true && nCntTime % 5 == 0)
	{
		for (int nCnt = 0; nCnt < UI_COMPONENT; nCnt++, pVtx += 4)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		}
		if (nCntTime % 10 == 0)
		{
			pPlayer->nCntHit++;
			if (pPlayer->nCntHit == 15)
			{
				pPlayer->bHit = false;
				pPlayer->nCntHit = 0;
			}
		}
	}
	else if (pPlayer->bHit == true && nCntTime % 5 != 0)
	{
		for (int nCnt = 0; nCnt < UI_COMPONENT; nCnt++, pVtx += 4)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < UI_COMPONENT; nCnt++, pVtx += 4)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
	g_pVtxBuffUI->Unlock();
}
void DrawUI(void)
{
	LPDIRECT3DDEVICE9 pDeviceUI = GetDevice();;

	pDeviceUI->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));
	pDeviceUI->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < UI_COMPONENT; nCnt++)
	{
		if (pUI[nCnt].bUse == true)
		{
			pDeviceUI->SetTexture(0, g_pTextureUI[pUI[nCnt].nTexture]);
			pDeviceUI->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
