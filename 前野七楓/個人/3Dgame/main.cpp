//=================================================================================================================
//
// 3Dゲームの処理　〔main.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "shadow.h"
#include "player.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "bullet.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define ID_BUTTON000	(101)		//ボタン000のID
#define ID_EDIT000		(111)		//エディットのID
#define ID_TIMER		(121)		//タイマーのID
#define TIMER_INTERVAL	(1000/60)	//タイマー発生間隔
#define WINDOW_POS_X    (500)		//ウィンドウの左上X座標
#define WINDOW_POS_Y    (100)		//ウィンドウの左上Y座標

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//=================================================================================================================
//　グローバル変数
//=================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;				//フォントへのポインタ
int g_nCountFPS;						//FPSカウンタ
										//MODE g_mode = MODE_TITLE;				//モードの種類

//*****************************************************************************************************************
//	メイン関数
//*****************************************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//変数宣言
	RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };
	WNDCLASSEX wcex =

	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"ファイル",
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;					//ウィンドウハンドル（識別子）
	MSG msg;					//メッセージを格納する
	DWORD dwExecLastTime;		//処理実行最終時刻
	DWORD dwFPSLastTime;		//FPS計測最終時刻
	DWORD dwCurrentTime;		//現在時刻
	DWORD dwFameCount;			//フレームカウント

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFameCount = 0;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの大きさを調整する
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの作成
	hWnd = CreateWindowEx(
		0,
		"ファイル",	//ウィンドウクラスの名前
		"ran away from",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);


	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{	//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{	//0.5秒経過
				g_nCountFPS = (dwFameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //最終時刻の保存
				dwFameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime)>(1000 / 60))
			{
				//DirectXの処理
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();
				//描画処理
				Draw();

				dwFameCount++;
			}
		}
	}
	//終了処理
	Uninit();

	//ウィンドウクラスの登録解除
	UnregisterClass(
		"ファイル",
		wcex.hInstance);

	return (int)msg.wParam;

}

//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//変数宣言
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };

	switch (uMsg)
	{

	case WM_CLOSE:	//×ボタンが押された場合
		nID = MessageBox(NULL, "終了しますか？", "注意", MB_YESNO | MB_ICONSTOP);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_DESTROY:	//ウィンドウの破棄
		PostQuitMessage(0);	//WN_QUIT メッセージを返す
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:		//ESCAPEキーが押されたとき
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:

		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//*****************************************************************************************************************
//	初期化処理
//*****************************************************************************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//ディスプレイのプレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}       
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンドの設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ソース（描画元）
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//デスティネーションの合成方法の設定

																			//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値　繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);	//V値　繰り返し

	//テクスチャステージステートの設定 (α値の合成）
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//初期化処理
	InitKeyboard(hInstance, hWnd);

	InitPolygon();
	InitLight();
	InitCamera();
	InitModel();
	InitShadow();
	InitWall();
	InitBillboard();
	InitMeshfield();
	InitBullet();

	D3DXCreateFont(g_pD3DDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	////サウンドの初期化処理
	//InitSound(hWnd);

	////モードの設定
	//SetMode(g_mode);


	return S_OK;
}

//*****************************************************************************************************************
//終了処理
//*****************************************************************************************************************
void Uninit(void)
{
	//終了処理
	UninitKeyboard();

	UninitPolygon();
	UninitLight();
	UninitCamera();
	UninitModel();
	UninitShadow();
	UninitWall();
	UninitBillboard();
	UninitMeshfield();
	UninitBullet();

	////サウンドの終了処理
	//UninitSound();

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの解放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの解放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//*****************************************************************************************************************
// 更新処理
//*****************************************************************************************************************
void Update(void)
{
	//入力デバイスの更新処理
	UpdateKeyboard();

	UpdateCamera();
	UpdatePolygon();
	UpdateLight();
	UpdateModel();
	UpdateShadow();
	UpdateWall();
	UpdateBillboard();
	UpdateMeshfield();
	UpdateBullet();
}

//*****************************************************************************************************************
//	FPSの処理
//*****************************************************************************************************************
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//*****************************************************************************************************************
//	描画処理
//*****************************************************************************************************************
void Draw(void)
{
	//バックバッファ＆Zバッファのクリア（画面のクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 0, 0), 1.0f, 0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		SetCamera();
		//DrawPolygon();
		DrawMeshfield();
		DrawModel();
		DrawShadow();
		DrawWall();
		DrawBillboard();
		DrawBullet();


		////フェードの描画処理
		//DrawFade();

#ifdef _DEBUG
		DrawFPS();			//FPS処理
#endif

		//描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************************************************
//	デバイスの取得
//*****************************************************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

