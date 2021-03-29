//=================================================================================================================
//
// タイトルの処理　〔title.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================
#define MAX_TITLE (5)							// タイトル最大数
#define MOVE_LOGO (D3DXVECTOR3(0.0f,2.0f,0.0f))	// ロゴの移動量

//=================================================================================================================
//列挙型
//=================================================================================================================
typedef enum
{
	TITLE_BG = 0,	// 背景
	TITLE_LOGO,		// ロゴ
	TITLE_PUSH,		// エンターを押す
	TITLE_MAX
}TITLE;

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdataTitle(void);
void DrawTitle(void);

#endif
