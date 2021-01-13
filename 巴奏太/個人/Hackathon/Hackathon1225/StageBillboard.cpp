#include "StageBillboard.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL; //頂点bufferのpointer
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARD_TEXTURE_NUM] = {}; //textureのpointer
BILLBOARD *pBillboard;
D3DXMATRIX g_mtxWorldBillboard; //世界matrix

void SetBillboard(void)
{
	//全部初期化
	for (int nCnt = 0; nCnt < BILLBOARD_NUMBER; nCnt++)
	{
		pBillboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillboard[nCnt].size = D3DXVECTOR2(20.0f, 25.0f);
		pBillboard[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillboard[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pBillboard[nCnt].bUse = false;
		pBillboard[nCnt].bAnime = false;
		pBillboard[nCnt].nPatternAnime = 0;
		pBillboard[nCnt].nTextureID = 0;
	}

	//分別定義
}

HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tree000.png", &g_pTextureBillboard[0]);
	pBillboard = (BILLBOARD *)malloc(BILLBOARD_NUMBER * sizeof(BILLBOARD)); //メモリ定義
	SetBillboard();

	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * BILLBOARD_NUMBER * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
		return E_FAIL;

	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BILLBOARD_NUMBER; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pBillboard[nCnt].pos.x - pBillboard[nCnt].size.x, pBillboard[nCnt].pos.y + pBillboard[nCnt].size.y, 0.f);
		pVtx[1].pos = D3DXVECTOR3(pBillboard[nCnt].pos.x + pBillboard[nCnt].size.x, pBillboard[nCnt].pos.y + pBillboard[nCnt].size.y, 0.f);
		pVtx[2].pos = D3DXVECTOR3(pBillboard[nCnt].pos.x - pBillboard[nCnt].size.x, pBillboard[nCnt].pos.y - pBillboard[nCnt].size.y, 0.f);
		pVtx[3].pos = D3DXVECTOR3(pBillboard[nCnt].pos.x + pBillboard[nCnt].size.x, pBillboard[nCnt].pos.y - pBillboard[nCnt].size.y, 0.f);
		pVtx[0].nor = pBillboard[nCnt].nor;
		pVtx[1].nor = pBillboard[nCnt].nor;
		pVtx[2].nor = pBillboard[nCnt].nor;
		pVtx[3].nor = pBillboard[nCnt].nor;
		pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
		pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
		pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
		pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);
	}
	g_pVtxBuffBillboard->Unlock();
	return S_OK;
}

void UninitBillboard(void)
{
	if (g_pVtxBuffBillboard != NULL)
		g_pVtxBuffBillboard = NULL;
	for (int nCnt = 0; nCnt < BILLBOARD_TEXTURE_NUM; nCnt++)
	{
		if (g_pTextureBillboard[nCnt] != NULL)
			g_pTextureBillboard[nCnt] = NULL;
	}
}

void UpdateBillboard(void)
{
	//move
}

void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans; //計算用のmatrix

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //close the lighting and diffuse effect
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //turn on & turn off
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //alpha test function
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100); //alpha number
	for (int nCnt = 0; nCnt < BILLBOARD_NUMBER; nCnt++)
	{
		if (pBillboard[nCnt].bUse == true)
		{
			D3DXMatrixIdentity(&g_mtxWorldBillboard); //単位行列
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
			//？
			g_mtxWorldBillboard._41 = 0.0f;
			g_mtxWorldBillboard._42 = 0.0f;
			g_mtxWorldBillboard._43 = 0.0f;
			D3DXMatrixTranslation(&mtxTrans, pBillboard[nCnt].pos.x, pBillboard[nCnt].pos.y, pBillboard[nCnt].pos.z); //世界matrix全体　移動したい距離というmatrixの合算
			D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans); //世界matrixの移動
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard); //set the world into Map
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBillboard[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); //turn on & turn off
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS); //alpha test function
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00); //alpha number
}