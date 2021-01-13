#pragma once
//-----------------------------------------------------------------------------
//
// XINPUT ヘッダー [xinputtest.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _XINPUTTEST_H_
#define _XINPUTTEST_H_
#include "DirectX.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689

//-----------------------------------------------------------------------------
// ゲームパッド入力
//-----------------------------------------------------------------------------
typedef struct
{
	bool bDpadUp;
	bool bDpadDOWN;
	bool bDpadLEFT;
	bool bDpadRIGHT;
	bool bX;
	bool bY;
	bool bA;
	bool bB;
	bool bLShoulder;
	bool bRShoulder;
	bool bLTrigger;
	bool bRTrigger;
	bool bLThumbUP;
	bool bLThumbDOWN;
	bool bStart;
}GAMEPAD;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitXinput(void);
void UninitXinput(void);
void UpdateXinput(void);
void DrawXinput(void);
GAMEPAD *GetGamePad(void);

#endif

