//===================================================================
//
// メインの処理　[main.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "wall.h"
#include "stdio.h"
#include "input.h"
#include "model.h"
#include "billboard.h"

//=================================================================================================
//マクロ定義
//=================================================================================================
#define CLASS_NAME "WindowClass"		//ウインドウクラスの名前
#define WINDOW_NAME "ウインドウの表示"	//ウインドウの名前
#define WINDOW_POS_X (50)				//X座標
#define WINDOW_POS_Y (50)				//Y座標
#define ID_TIMER (121)					//タイマーのID
#define TIMER_INTERVAL (1000/60)		//タイマー発生間隔
#define MAX_LINE (15)					//敵の横数

//=================================================================================================
//グローバル変数
//=================================================================================================
LPDIRECT3D9 g_pD3D = NULL;							//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				//Direct3Dデバイスへのポインタ	
LPD3DXFONT g_pFont = NULL;							//フォントのポインタ
int g_nCountFPS;									//FPSカウンタ

//=================================================================================================
//メイン関数
//=================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
		"CLASS_NAME",
		LoadIcon(NULL,IDI_APPLICATION),
		
	};
	HWND hWnd;
	MSG msg;

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);		//ウインドウの調整

	//ウインドウの作成
	hWnd = CreateWindowEx(
		0,
		"CLASS_NAME",//ウインドウクラスの名前
		WINDOW_NAME,//ウインドウの名前
		//クラウドスタイル
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,		//ウインドウの左上X座標
		CW_USEDEFAULT,		//ウインドウの左上Y座標
		SCREEN_WIDTH,		//幅
		SCREEN_HEIGHT,		//高さ
		NULL,
		NULL,
		hInstance,
		NULL);
	DWORD dwExecLastTime;			//処理実行最終時刻
	DWORD dwFPSLastTime;			//FPS計測最終時刻
	DWORD dwCurrentTime;			//現在時刻
	DWORD dwFrameCount;				//フレームカウント

	dwExecLastTime =
	dwFPSLastTime =
	dwCurrentTime = timeGetTime();			//現在時刻を設定
	dwFrameCount = 0;

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//DirectXの処理
				//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	//終了処理
	Uninit();

	//ウインドウクラスの登録解除
	UnregisterClass(
		"CLASS_NAME",
		wcex.hInstance);
	return (int)msg.wParam;
}

//=================================================================================================
//ウインドウプロシージャ
//=================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUIT
		break;
	case WM_KEYDOWN://キーを押した
		switch (wParam)
		{
		case VK_ESCAPE://ESCキー
			nID = MessageBox(NULL, "ウインドウを閉じますよろしいですか", "ウインドウの削除", MB_YESNO | MB_TOPMOST);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				nID = MessageBox(NULL, "終了しませんでした", "消えないよ", MB_OK);
			}
			break;
		}
		break;

	case WM_CREATE:
		//タイマーの初期化
		SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);
		break;


		case WM_CLOSE:
		nID = MessageBox(NULL, "本当に閉じますいいですか", "閉じるよん", MB_YESNO | MB_ICONQUESTION);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
	
}

//=================================================================================================
//初期化処理
//=================================================================================================
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

		//ディスクプレイモードを取得
		if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}

		//デバイスのプレゼンテーションパラメーターの設定
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
		//レンダーステートの説定
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//サンプラーステート
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);			//縮小時、補間
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);			//拡大時、補間
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);			//U値、繰り返し
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);			//V値、繰り返し

		//テクスチャステージステートの設定
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);			//アルファ値の合成
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		//キーボードの初期化処理
		InitKeyboard(hInstance, hWnd);

		//ポリゴンの初期化
		InitPolygon();

		//モデルの初期化
		InitModel();

		//影の初期化
		InitShadow();

		//壁の初期化
		InitWall();

		//ビルボードの初期化処理
		InitBillboard();

		//カメラの終了処理
		InitCamera();

		//ライトの初期化処理
		InitLight();

		//サウンドの初期化処理
		//InitSound(hWnd);

		//フォント
		D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

		//フェードの初期化処理
		//InitFade(MODE_TITLE);


	return S_OK;
}

//=================================================================================================
//終了処理
//=================================================================================================
void Uninit(void)
{
	//キーボードの終了処理
	UninitKeyboard();

	//ポリゴンの終了処理
	UninitPolygon();

	//モデルの終了処理
	UninitModel();

	//影の終了処理
	UninitShadow();

	//壁の終了処理
	UninitWall();

	//ビルボードの終了処理
	UninitBillboard();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//フェードの終了処理
	//UninitFade();

	//サウンドの終了処理
	//UninitSound();

	//Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
		
	}
	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=================================================================================================
//更新処理
//=================================================================================================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//ポリゴンの更新
	UpdatePolygon();

	//モデルの更新処理
	UpdateModel();

	//影の更新
	UpdateShadow();

	//壁の更新処理
	UpdateWall();

	//ビルボードの更新処理
	UpdateBillboard();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();
}

//=================================================================================================
//描画処理
//=================================================================================================
void Draw(void)
{
	//バックバッファ&バッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//カメラの描画処理
		SetCamera();
		
		//ポリゴンの描画処理
		DrawPolygon();

		//モデルの描画処理
		//DrawModel();

		//影の描画処理
		DrawShadow();

		//壁の描画処理
		DrawWall();

		//ビルボードの描画処理
		DrawBillboard();

		//FPS
		#ifdef _DEBUG
			DrawFPS();
		#endif

		//座標の表示
		DrawCoor();

		//描画の終了
		g_pD3DDevice->EndScene();

	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=================================================================================================
//FPS
//=================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=================================================================================================
//座標の表示
//=================================================================================================
void DrawCoor(void)
{
	Camera *camera;

	camera = GetCamera();

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	int nNum = sprintf(&aStr[0], "移動:%.3f\n", camera->posV.x);
	nNum += sprintf(&aStr[nNum], "カメラの視点:%.3f\n", camera->posR.x);
	//wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));
}