//-----------------------------------------------------------------------------
//
// XINPUTの処理 [xinputtest.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "Xinput.h"
#include "fade.h"

typedef enum
{
	KEYKEY_X = 0,
	KEYKEY_Y,
	KEYKEY_B,
	KEYKEY_A,
	KEYKEY_START,
	KEYKEY_MAX
}KEYKEY;

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
GAMEPAD g_pad;

//-----------------------------------------------------------------------------
// リザルトの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitXinput(void)
{
	return S_OK;
}

//-----------------------------------------------------------------------------
// XINPUT 終了処理
//-----------------------------------------------------------------------------
void UninitXinput(void)
{
}

//-----------------------------------------------------------------------------
// XINPUT 更新処理
//-----------------------------------------------------------------------------
void UpdateXinput(void)
{
	XINPUT_STATE state;
	XINPUT_KEYSTROKE Key;

	ZeroMemory(&state, sizeof(XINPUT_STATE));	//ステートの中身をリセット
	GAMEPAD padKey;

	// XInputのコントローラのstateを取得
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{//コントローラ接続している

	 // X,Y,A,Bボタン
	 //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) g_pad.bA = true;	// Aボタン
	 ////if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) g_pad.bB = true;
	 //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) g_pad.bX = true;
	 //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) g_pad.bY = true;
	 //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) g_pad.bStart = true;

		XInputGetKeystroke(0, NULL, &Key);
		//XInputGetKeystroke(0, NULL, &Key[KEYKEY_Y]);
		//XInputGetKeystroke(0, NULL, &Key[KEYKEY_B]);
		//XInputGetKeystroke(0, NULL, &Key[KEYKEY_A]);
		//XInputGetKeystroke(0, NULL, &Key[KEYKEY_START]);

		if (Key.VirtualKey == VK_PAD_B && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			g_pad.bB = true;
		}
		if (Key.VirtualKey == VK_PAD_A && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			g_pad.bA = true;
		}
		if (Key.VirtualKey == VK_PAD_X && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			g_pad.bX = true;
		}
		if (Key.VirtualKey == VK_PAD_Y && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			g_pad.bY = true;
		}
		if (Key.VirtualKey == VK_PAD_START && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			g_pad.bStart = true;
		}
		//if (Key[KEYKEY_Y].VirtualKey == VK_PAD_Y && Key[KEYKEY_Y].Flags == XINPUT_KEYSTROKE_KEYDOWN) g_pad.bY = true;
		//if (Key[KEYKEY_A].VirtualKey == VK_PAD_A && Key[KEYKEY_A].Flags == XINPUT_KEYSTROKE_KEYDOWN) g_pad.bA = true;
		//if (Key[KEYKEY_B].VirtualKey == VK_PAD_B && Key[KEYKEY_B].Flags == XINPUT_KEYSTROKE_KEYDOWN)
		//{
		//	g_pad.bB = true;
		//}
		//if (Key[KEYKEY_START].VirtualKey == VK_PAD_START && Key[KEYKEY_START].Flags == XINPUT_KEYSTROKE_KEYDOWN) g_pad.bStart = true;


	}
	else
	{//接続していない

	}
}
//-----------------------------------------------------------------------------
// XINPUT 描画処理
//-----------------------------------------------------------------------------
void DrawXinput(void)
{
}

//-----------------------------------------------------------------------------
// コントローラの情報を取得
//-----------------------------------------------------------------------------
GAMEPAD *GetGamePad(void)
{
	return &g_pad;
}