#pragma once

#include "d3dx9.h"
#include "d3dx9math.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"
#include <XInput.h>
#include <time.h>
#include <stdio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")//D3DXCreateTextureFromFile
#pragma comment(lib, "winmm.lib")//FPS計測
#pragma comment(lib, "dinput8.lib")//keyboard
#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "dxguid.lib")//IID_IDirectInput8A,GUID_SysKeyboard,GUID_Key
#pragma comment(lib, "xinput.lib")

#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define WIDTH_SCREEN 1920
#define HEIGHT_SCREEN 1080
float const PI = 3.14f;

typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR3 nor; //法線vector
	D3DCOLOR col; //頂点color
	D3DXVECTOR2 tex; //UV座標
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;//2D頂点情報を保存する

typedef enum
{
	MODE_TITLE = 0, //
	MODE_TITLE1,
	MODE_TUTORIAL,
	MODE_STAGE,
	MODE_OAC,
	MODE_RANKING,
	MODE_MAX,
}MODE;

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Update(void);
void Draw(void);
void Uninit(void);
LPDIRECT3DDEVICE9 GetDevice(void);

void UpdateMode(MODE mode);
void DrawMode(MODE mode);
MODE GetMode(void);
void SetMode(MODE mode);
void SetPause(bool bPause);