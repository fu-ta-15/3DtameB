//=============================================================================
//
// ライトの処理 [light.h]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "light.h"

//=============================================================================
// グローバル変数
//=============================================================================
D3DLIGHT9 g_light[3];	//ライトの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXVECTOR3 vecDir;				//設定用方向ベクトル

									//デバイスの取得
	pDevice = GetDevice();

	//----------ライト1つ目----------//
	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;	//平行光源

											//ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);	//正規化する
	g_light[0].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_light[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);


	//----------ライト2つ目----------//
	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//ライトの種類を設定
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;	//平行光源

											//ライトの拡散光を設定
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, 0.8f, -0.8f);
	D3DXVec3Normalize(&vecDir, &vecDir);	//正規化する
	g_light[0].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(1, &g_light[1]);

	//ライトを有効にする
	pDevice->LightEnable(1, TRUE);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLight(void)
{

}