#include "Shadow.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //’¸“_buffer‚Ìpointer
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL; //texture‚Ìpointer
D3DXMATRIX g_mtxWorldShadow; //¢ŠEmatrix
SHADOW *pShadow;
int g_ShadowNum;
void SetShadow(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nIndex)
{
	pShadow[nIndex].pos = pos;
	pShadow[nIndex].pos.y = 0.f;
	pShadow[nIndex].size = size;
	pShadow[nIndex].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
}//return ID of Shadow's mod


HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	g_ShadowNum = 10;
	pShadow = (SHADOW *)malloc(g_ShadowNum * sizeof(SHADOW));
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
		return E_FAIL;

	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-10.f, 0.f, 10.f);
	pVtx[1].pos = D3DXVECTOR3(10.f, 0.f, 10.f);
	pVtx[2].pos = D3DXVECTOR3(-10.f, 0.f, -10.f);
	pVtx[3].pos = D3DXVECTOR3(10.f, 0.f, -10.f);

	pVtx[0].nor = D3DXVECTOR3(-10.f, 1.f, 10.f);
	pVtx[1].nor = D3DXVECTOR3(10.f, 1.f, 10.f);
	pVtx[2].nor = D3DXVECTOR3(-10.f, 1.f, -10.f);
	pVtx[3].nor = D3DXVECTOR3(10.f, 1.f, -10.f);

	pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);

	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

void UninitShadow(void)
{
	if (g_pVtxBuffShadow != NULL)
		g_pVtxBuffShadow = NULL;
	if (g_pTextureShadow != NULL)
		g_pTextureShadow = NULL;
}

void UpdateShadow(void)
{

}

void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nCnt = 0; nCnt < g_ShadowNum; nCnt++)
	{
		//?
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //close the lighting and diffuse effect
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); //turn on & turn off
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //alpha test function
		pDevice->SetRenderState(D3DRS_ALPHAREF, 100); //alpha number

		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		D3DXMatrixIdentity(&g_mtxWorldShadow); //’PˆÊs—ñ
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pShadow[nCnt].rot.y, pShadow[nCnt].rot.x, pShadow[nCnt].rot.z); //the opreation is Roll->Pitch->Yaw ÅŒãoutput‰ñ‚³‚ê‚½matrix
		D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot); //¢ŠEmatrix‚ÌŽü‚è@Param1 out put matrix = ¢ŠEmatrix * ‰ñ‚³‚ê‚½matrix
		D3DXMatrixTranslation(&mtxTrans, pShadow[nCnt].pos.x, pShadow[nCnt].pos.y, pShadow[nCnt].pos.z); //¢ŠEmatrix‘S‘Ì@ˆÚ“®‚µ‚½‚¢‹——£‚Æ‚¢‚¤matrix‚Ì‡ŽZ
		D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans); //¢ŠEmatrix‚ÌˆÚ“®

		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow); //set the world into Map
		pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureShadow);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}