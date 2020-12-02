//===================================================================
//
// ライトの処理　[light.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "light.h"

//=================================================================================================
//グローバル変数
//=================================================================================================
D3DLIGHT9 g_light[3];					//ライトの情報

//=================================================================================================
//初期化処理
//=================================================================================================　
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	D3DXVECTOR3 vecDir;							//設定用方向ベクトル

	//デバイスの取得
	pDevice = GetDevice();

	//ライトをクリアする
	ZeroMemory(&g_light,sizeof(D3DLIGHT9));

	//ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;					//拡散光
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;					//拡散光
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;					//拡散光

	//ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);					//正規化する
	g_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.2f);
	D3DXVec3Normalize(&vecDir, &vecDir);					//正規化する
	g_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.2f, 0.8f, 0.8f);
	D3DXVec3Normalize(&vecDir, &vecDir);					//正規化する
	g_light[2].Direction = vecDir;

	//ライトを設定する
	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=================================================================================================
//終了処理
//=================================================================================================
void UninitLight(void)
{
}

//=================================================================================================
//更新処理
//=================================================================================================　
void UpdateLight(void)
{
}