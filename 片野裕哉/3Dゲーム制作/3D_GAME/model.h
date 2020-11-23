//
//
// モデルヘッダー [model.h]
//
//
//
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//
// 構造体
//
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 rotObjective;	// 目的の向き
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
} MODEL;

//
// プロトタイプ宣言
//
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);

#endif