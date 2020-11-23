//
//
// ウォールヘッダー [wall.h]
//
//
//
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

//
// プロトタイプ宣言
//
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetVertexWall(int nIdx);

#endif