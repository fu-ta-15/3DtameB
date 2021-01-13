#include "meshfield.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL; //頂点bufferのpointer
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL; //textureのpointer
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL; //index bufferのpointer
D3DXVECTOR3 g_posMeshfield; //位置
D3DXVECTOR3 g_rotMeshfield; //向き
D3DXMATRIX g_mtxWorldMeshfield; //世界matrix
D3DXVECTOR2 g_Size;
D3DXVECTOR2 g_Matrix; //polygon　matrix の x->row y->column を保存する
HRESULT InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	g_Matrix = D3DXVECTOR2(10.f, 10.f);//X行 * Y列の設定 polygon数は x-1, y-1
	g_Size = D3DXVECTOR2(1000.f, 1000.f);//polygon size 200 * 200	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureMeshfield);
	g_posMeshfield = D3DXVECTOR3(0.f, 0.f, 0.f);
	g_rotMeshfield = D3DXVECTOR3(0.f, 0.f, 0.f);

	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * (int)(g_Matrix.x * g_Matrix.y),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL)))
		return E_FAIL;

	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);
	//一个一个的小polygon组成整体 size是整体size的倍数除
	//用列数来判断换行的操作
	//全部的polygon数循环 IF判断
	//X=3 Y=3 のpolygon vertex number = 9
	for (int nCnt = 0; nCnt < (g_Matrix.x * g_Matrix.y); nCnt++)
	{
		int nRemainder_y = nCnt % (int)g_Matrix.y; //目下の列の計算
		int nRemainder_x = nCnt / (int)g_Matrix.y; //目下の行を計算する
												   //座標の計算
		pVtx[nCnt].pos = D3DXVECTOR3(
			(-g_Size.x + (nRemainder_y) * ((g_Size.x * 2) / (g_Matrix.y - 1))),//一番左から右に計算する　毎回の移動距離は一つちっさいpolygonのxsize
			0.f,
			g_Size.y - nRemainder_x * ((g_Size.y * 2) / (g_Matrix.x - 1)));//一番上から下に計算する　毎回の移動距離は一つちっさいpolygonのysize
		pVtx[nCnt].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		pVtx[nCnt].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		//texture
		pVtx[nCnt].tex = D3DXVECTOR2((float)nRemainder_y, (float)nRemainder_x);
	}
	g_pVtxBuffMeshfield->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * 2 * (int)(g_Matrix.x * g_Matrix.y + 2 * g_Matrix.x - 1), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshfield, NULL);
	WORD *pIdx;
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	int nCntEveryRow = -1;
	int nCntRow = 0;
	int nCntColumn = (int)g_Matrix.y;
	//すべてのpolygon vertexを辿る
	for (int nCnt = 0; nCnt < (2 * ((g_Matrix.x - 1) * (g_Matrix.y - 1) + 2 * (g_Matrix.x - 1) - 1)); nCnt++)
	{
		if (nCnt % 2 == 0)
		{
			pIdx[nCnt] = nCntColumn;
			nCntColumn++;
		}
		else
		{
			pIdx[nCnt] = nCntEveryRow + 1;
			if ((nCntEveryRow % (int)g_Matrix.y) == g_Matrix.y - 2 && nCntRow != g_Matrix.x - 2)
			{
				nCnt++;
				pIdx[nCnt] = nCntEveryRow + 1;
				nCnt++;
				pIdx[nCnt] = nCntColumn;
				nCnt++;
				pIdx[nCnt] = nCntColumn;
				nCntColumn++;
				nCntRow++;
			}
			nCntEveryRow++;
		}
	}
	g_pIdxBuffMeshfield->Unlock();
	return S_OK;
}
void UninitMeshfield(void)
{
	if (g_pVtxBuffMeshfield != NULL)
		g_pVtxBuffMeshfield = NULL;
	if (g_pTextureMeshfield != NULL)
		g_pTextureMeshfield = NULL;
	if (g_pIdxBuffMeshfield != NULL)
		g_pIdxBuffMeshfield = NULL;
}
void UpdateMeshfield(void)
{

}
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用のmatrix
	D3DXMatrixIdentity(&g_mtxWorldMeshfield); //単位行列
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z); //the opreation is Roll->Pitch->Yaw 最後output回されたmatrix
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot); //世界matrixの周り　Param1 out put matrix = 世界matrix * 回されたmatrix
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z); //世界matrix全体　移動したい距離というmatrixの合算
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans); //世界matrixの移動
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield); //set the world into Map
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));
	pDevice->SetIndices(g_pIdxBuffMeshfield);//
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, g_pTextureMeshfield);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (int)(2 * ((g_Matrix.x - 1) * (g_Matrix.y - 1) + 2 * (g_Matrix.x - 1) - 1)), 0, (int)((g_Matrix.x - 1) * (g_Matrix.y - 1) * 2 + (3 * g_Matrix.x - 1)));//important!! 最後のpramaは三角形数、隠している描画しないのは（線状）計数する必要！= (3 * (行数-1))
}