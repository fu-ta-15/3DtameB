//=============================================================================
//
// 壁の処理 [wall.h]
// Author:Taiki Hayasaka
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//=============================================================================
// 壁の構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	bool bUse;				//使用しているかどうか
}Wall;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetVertexWall(int nCntWall);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Wall *GetWall(void);

#endif

