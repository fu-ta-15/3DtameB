//=================================================================================================================
//
// カメラの処理　〔camera.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "camera.h"
#include "light.h"
#include "input.h"

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
D3DLIGHT9 g_Light;	//ライトの情報

//*****************************************************************************************************************
//	ライトの初期化処理
//*****************************************************************************************************************
void InitLight(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//設定用方向ベクトル
	D3DXVECTOR3 vecDir;

	//デバイスの取得
	pDevice = GetDevice();

	//ライトをクリアする
	ZeroMemory(&g_Light, sizeof(D3DLIGHT9));

	//ライトの種類の設定
	g_Light.Type = D3DLIGHT_DIRECTIONAL;
	//g_Light.Type = D3DLIGHT_SPOT;
	//g_Light.Type = D3DLIGHT_POINT;

	//ライトの拡散光の設定
	g_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//正規化する

	g_Light.Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_Light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//*****************************************************************************************************************
//	ライトの終了処理
//*****************************************************************************************************************
void UninitLight(void)
{
	
}

//*****************************************************************************************************************
//　ライトの更新処理
//*****************************************************************************************************************
void UpdateLight(void)
{
	//設定用方向ベクトル
		D3DXVECTOR3 vecDir;

	if (GetKeyboardPress(DIK_O) == true)
	{
		
	}

}

