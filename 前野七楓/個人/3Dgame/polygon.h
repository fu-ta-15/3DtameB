//=================================================================================================================
//
// ポリゴンの処理　〔polygon.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================
#define F_SIZE_X (200.0f)	//フィールドのサイズX
#define F_SIZE_Z (200.0f)	//フィールドのサイズZ

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

#endif

