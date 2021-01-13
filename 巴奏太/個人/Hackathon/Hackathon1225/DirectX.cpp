#include "DirectX.h"
#include "Sound.h"
#include "XInput.h"
#include "Fade.h"
#include "Input.h"

#include "Title.h"
#include "Title1.h"
#include "Tutorial.h"
#include "ClearAndOver.h"
#include "Ranking.h"

#include "Player.h"
#include "Light.h"
#include "Camera.h"
#include "MeshField.h"
#include "UI.h"
#include "Model.h"
#include "BillBoard.h"
#include "meteorite.h"
#include "ModelBillBoard.h"

#include "Pause.h"
#include "RedLine.h"

LPD3DXFONT g_pFont = NULL;
LPDIRECT3D9 g_pD3D = NULL;//user pc's graphics caxrd information get
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_Mode;
bool g_bPause;
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)//why use HRESULT?
{
	g_bPause = false;
	g_Mode = MODE_TITLE;
	srand((int)time(0));
	//check the user's hardware character
	D3DDISPLAYMODE d3ddm;//graphics card mode

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//create a d3d object
	if (g_pD3D == NULL) return E_FAIL;

	//check the default graphics card's displaymode
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))return E_FAIL;

	//prepare for get userdevice interface
	D3DPRESENT_PARAMETERS d3dpp;//struct group
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = 1920;
	d3dpp.BackBufferHeight = 1080;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;//FULLSCREEN mode is false
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//check pc device about vertex draw（graphics card version 2 HAL and REF 3 object window handle 4 定点运算标志类型 互斥 5 point to a struct, this struct is describe the device Set which we want to create. 6 return device pointer
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
	//Render set base
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//Render set about fade (alpha)
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//FPS表示 create
	D3DXCreateFont
	(
		g_pD3DDevice,
		30,//size
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont
	);

	Initkeyboard(hInstance, hWnd);
	InitFade(MODE_TITLE);
	InitSound(hWnd);
	SetMode(MODE_TITLE);

	return S_OK;
}

void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
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
	Uninitkeyboard();
	UninitSound();
	StopSound();
}

void Update(void)
{
	Updatekeyboard();
	UpdateXinput();
	UpdateFade();
	UpdateMode(g_Mode);
}

void Draw(void)
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//BeginScene and EndScene to tell the system when it should be start or end the rendering, u can put anyother rendering set between
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		DrawMode(g_Mode);
		DrawFade();
		SetCamera();
		g_pD3DDevice->EndScene();
	}
	//show the rendering
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
void SetMode(MODE mode)
{
	switch (g_Mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TITLE1:
		UninitTitle1();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_STAGE:
		UninitPlayer();
		UninitCamera();
		UninitBillboard();
		UninitModel();
		//UninitMeteorite();
		UninitBillboardMod();
		UninitUI();
		UninitRedLine();
		UninitPause();
		StopSound(SOUND_LABEL_BGM000);
		break;
	case MODE_OAC:
		UninitOAC();
		break;
	case MODE_RANKING:
		UninitRank();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TITLE1:
		InitTitle1();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_STAGE:
		PlaySound(SOUND_LABEL_BGM000);
		InitOAC();
		InitBillboardMod();
		InitCamera();
		InitLight();
		InitBillboard();
		//InitMeteorite();
		InitModel();
		InitPlayer();
		InitUI();
		InitRedLine();
		InitPause();
		break;
	case MODE_OAC:
		break;
	case MODE_RANKING:
		InitRank();
		break;
	}
	g_Mode = mode;
}
void UpdateMode(MODE mode)
{
	switch (mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TITLE1:
		UpdateTitle1();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_STAGE:
		if (GetkeyboardTrigger(DIK_P) == true)
		{
			g_bPause = g_bPause ? false : true;
		}

		if (g_bPause != true)
		{
			UpdateModel();
			UpdatePlayer();
			UpdateCamera();
			UpdateBillboard();
			UpdateBillboardMod();
			//UpdateMeteorite();
			UpdateUI();
			UpdateRedLine();
		}
		else
		{
			UpdatePause();
		}
		
		break;
	case MODE_OAC:
		UpdateOAC();
		break;
	case MODE_RANKING:
		UpdateRank();
		break;
	}
}

void DrawMode(MODE mode)
{
	switch (mode)
	{
	case MODE_TITLE:
		DrawTitle();
		break;
	case MODE_TITLE1:
		DrawTitle1();
		break;
	case MODE_TUTORIAL:
		DrawTutorial();
		break;
	case MODE_STAGE:
		DrawPlayer();
		DrawModel();
		DrawUI();
		//DrawMeteorite();
		DrawBillboardMod();
		DrawBillboard();
		DrawRedLine();
		if (g_bPause == true)
		{
			DrawPause();
		}
		break;
	case MODE_OAC:
		DrawOAC();
		break;
	case MODE_RANKING:
		DrawRank();
		break;
	}
}

MODE GetMode(void)
{
	return g_Mode;//今のmod type
}

void SetPause(bool bPause)
{
	g_bPause = bPause;
}