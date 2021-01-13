#include "ModelBillboard.h"
#include "Model.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboardMod = NULL; //頂点bufferのpointer
LPDIRECT3DTEXTURE9 g_pTextureBillboardMod[BILLBOARDMOD_TEXTURE_NUM] = {}; //textureのpointer
BILLBOARDMOD *pBillboardMod;

void SetBillboardMod(void)
{
	for (int nCnt = 0; nCnt < BILLBOARDMOD_NUMBER; nCnt++)
	{
		pBillboardMod[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillboardMod[nCnt].size = D3DXVECTOR2(10.0f, 10.0f);
		pBillboardMod[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillboardMod[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBillboardMod[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pBillboardMod[nCnt].bUse = false;
		pBillboardMod[nCnt].bAnime = false;
		pBillboardMod[nCnt].nPatternAnime = 0;
		pBillboardMod[nCnt].nTextureID = 4;
	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_RED; nCntModel++)
	{
		pBillboardMod[nCntModel].nTextureID = 1;
	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_BLUE; nCntModel++)
	{
		pBillboardMod[nCntModel + 50].nTextureID = 2;
	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_YELLOW; nCntModel++)
	{
		pBillboardMod[nCntModel + 100].nTextureID = 3;
	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_GREEN; nCntModel++)
	{
		pBillboardMod[nCntModel + 150].nTextureID = 0;
	}
}

void SetBillboardMod(D3DXVECTOR3 pos, int nType)
{
	VERTEX_3D *pVtx;
	g_pVtxBuffBillboardMod->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < BILLBOARDMOD_NUMBER; nCnt++, pVtx += 4)
	{
		if (pBillboardMod[nCnt].bUse == false)
		{
			pBillboardMod[nCnt].bUse = true;
			pVtx[0].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x - pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y + pBillboardMod[nCnt].size.y, 0.f);
			pVtx[1].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x + pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y + pBillboardMod[nCnt].size.y, 0.f);
			pVtx[2].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x - pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y - pBillboardMod[nCnt].size.y, 0.f);
			pVtx[3].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x + pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y - pBillboardMod[nCnt].size.y, 0.f);
			break;
		}
	}
	g_pVtxBuffBillboardMod->Unlock();
}

HRESULT InitBillboardMod(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	D3DXCreateTextureFromFile(pDevice, "data/Texture/A.png", &g_pTextureBillboardMod[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/B.png", &g_pTextureBillboardMod[1]);//red
	D3DXCreateTextureFromFile(pDevice, "data/Texture/X.png", &g_pTextureBillboardMod[2]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Y.png", &g_pTextureBillboardMod[3]);
	pBillboardMod = (BILLBOARDMOD *)malloc(BILLBOARDMOD_NUMBER * sizeof(BILLBOARDMOD)); //メモリ定義
	SetBillboardMod();
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * BILLBOARDMOD_NUMBER * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboardMod,
		NULL)))
		return E_FAIL;
	g_pVtxBuffBillboardMod->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < BILLBOARDMOD_NUMBER; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x - pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y + pBillboardMod[nCnt].size.y, 0.f);
		pVtx[1].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x + pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y + pBillboardMod[nCnt].size.y, 0.f);
		pVtx[2].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x - pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y - pBillboardMod[nCnt].size.y, 0.f);
		pVtx[3].pos = D3DXVECTOR3(pBillboardMod[nCnt].pos.x + pBillboardMod[nCnt].size.x, pBillboardMod[nCnt].pos.y - pBillboardMod[nCnt].size.y, 0.f);
		pVtx[0].nor = pBillboardMod[nCnt].nor;
		pVtx[1].nor = pBillboardMod[nCnt].nor;
		pVtx[2].nor = pBillboardMod[nCnt].nor;
		pVtx[3].nor = pBillboardMod[nCnt].nor;
		pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
		pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
		pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
		pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);
	}
	g_pVtxBuffBillboardMod->Unlock();
	return S_OK;
}

void UninitBillboardMod(void)
{
	if (g_pVtxBuffBillboardMod != NULL)
		g_pVtxBuffBillboardMod = NULL;
	for (int nCnt = 0; nCnt < BILLBOARDMOD_TEXTURE_NUM; nCnt++)
	{
		if (g_pTextureBillboardMod[nCnt] != NULL)
			g_pTextureBillboardMod[nCnt] = NULL;
	}
}

void UpdateBillboardMod(void)
{
	VERTEX_3D *pVtx;
	MODEL *pModel = GetModel();
	g_pVtxBuffBillboardMod->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_ALL; nCntModel++)
	{
		if (pBillboardMod[nCntModel].nTextureID == 1 && pBillboardMod[nCntModel].bUse == true)
		{
			int nCntfking;
			nCntfking = 0;
		}
		if (pModel[nCntModel].pos.z <= 200.0f && pModel[nCntModel].bUse == true)
		{
			pBillboardMod[nCntModel].pos = pModel[nCntModel].pos;
			pBillboardMod[nCntModel].pos.y = pModel[nCntModel].pos.y + 20.f;
			pBillboardMod[nCntModel].bUse = true;
			pVtx[0].pos = D3DXVECTOR3(pBillboardMod[nCntModel].pos.x - pBillboardMod[nCntModel].size.x, pBillboardMod[nCntModel].pos.y + pBillboardMod[nCntModel].size.y, 0.f);
			pVtx[1].pos = D3DXVECTOR3(pBillboardMod[nCntModel].pos.x + pBillboardMod[nCntModel].size.x, pBillboardMod[nCntModel].pos.y + pBillboardMod[nCntModel].size.y, 0.f);
			pVtx[2].pos = D3DXVECTOR3(pBillboardMod[nCntModel].pos.x - pBillboardMod[nCntModel].size.x, pBillboardMod[nCntModel].pos.y - pBillboardMod[nCntModel].size.y, 0.f);
			pVtx[3].pos = D3DXVECTOR3(pBillboardMod[nCntModel].pos.x + pBillboardMod[nCntModel].size.x, pBillboardMod[nCntModel].pos.y - pBillboardMod[nCntModel].size.y, 0.f);
		}
		else
		{
			pBillboardMod[nCntModel].bUse = false;
		}
	}
	g_pVtxBuffBillboardMod->Unlock();
}

void DrawBillboardMod(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans; //計算用のmatrix

	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //close the lighting and diffuse effect
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //turn on & turn off
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //alpha test function
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100); //alpha number
	for (int nCntBoard = 0; nCntBoard < BILLBOARDMOD_NUMBER; nCntBoard++)
	{
		if (pBillboardMod[nCntBoard].bUse == true)
		{
			MODEL *pModel = GetModel();
			pBillboardMod[nCntBoard].pos = pModel[nCntBoard].pos;
			pBillboardMod[nCntBoard].pos.y = pModel[nCntBoard].pos.y + 20.f;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pBillboardMod[nCntBoard].mtxworld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 1
			//ポリゴンをカメラに対して正面に向ける
			//逆行列を求める
			D3DXMatrixInverse(&pBillboardMod[nCntBoard].mtxworld, NULL, &mtxView);

			//平行移動の部分は無視する
			pBillboardMod[nCntBoard].mtxworld._41 = 0.0f;
			pBillboardMod[nCntBoard].mtxworld._42 = 0.0f;
			pBillboardMod[nCntBoard].mtxworld._43 = 0.0f;
#endif
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBillboardMod[nCntBoard].pos.x, pBillboardMod[nCntBoard].pos.y, pBillboardMod[nCntBoard].pos.z);
			D3DXMatrixMultiply(&pBillboardMod[nCntBoard].mtxworld, &pBillboardMod[nCntBoard].mtxworld, &mtxTrans);

			//ワールドマトリックス
			pDevice->SetTransform(D3DTS_WORLD, &pBillboardMod[nCntBoard].mtxworld);
			
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboardMod, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillboardMod[pBillboardMod[nCntBoard].nTextureID]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBoard * 4, 2);
		}
	}
	//αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//ライティングを有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}