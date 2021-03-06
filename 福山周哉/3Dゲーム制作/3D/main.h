//===================================================================
//
// ウインドウの処理　[main.h]
// Author: fukuyama syuya
//
//===================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

//=================================================================================================
//インクルードファイル
//=================================================================================================
#include <windows.h>
#include "d3dx9.h"						//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"						//入力処理に必要
#pragma comment (lib,"dinput8.lib")		//入力処理に必要
#include "xaudio2.h"					//サウンド再生に必要

//=================================================================================================
//ライブラリのリンク
//=================================================================================================
#pragma comment(lib, "d3d9.lib")		//描画処理
#pragma comment(lib, "d3dx9.lib")		//描画処理
#pragma comment(lib, "dxguid.lib")		//描画処理
#pragma comment(lib, "winmm.lib")		//FPS

//===========================================================================================================
//頂点フォーマット
//===========================================================================================================
#define SCREEN_WIDTH (1280)				//画面の幅
#define SCREEN_HEIGHT (810)				//画面の高さ
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//===========================================================================================================
//頂点フォーマットの構造体
//===========================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;					//頂点座標
	D3DXVECTOR3 nor;					//法線ベクトル
	D3DCOLOR col;						//頂点カラー
	D3DXVECTOR2 tex;					//テクスチャ座標
}VERTEX_3D;

//=================================================================================================
//プロトタイプ宣言
//=================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInsutance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void DrawCoor(void);

#endif


