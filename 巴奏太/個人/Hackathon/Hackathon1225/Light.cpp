#include "Light.h"

D3DLIGHT9 *pLight;

void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[3]; //vectorの方向
	pLight = (D3DLIGHT9 *)malloc(3 * sizeof(D3DLIGHT9));
	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		ZeroMemory(&pLight[nCnt], sizeof(D3DLIGHT9)); //clear the last light pointer's information
		pLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;
		pLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]); //単位matrixにする　正規化　light size keep equal 1.0f
		pLight[nCnt].Direction = vecDir[nCnt];
		pDevice->SetLight(nCnt, &pLight[nCnt]); //set種類番号1のlight
		pDevice->LightEnable(nCnt, TRUE); //種類番号1のlight　有効にする
	}
}