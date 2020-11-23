//=============================================================================
//
// カメラの処理 [camera.h]
// Author:Taiki Hayasaka
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=============================================================================
// カメラの構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 rot;			//カメラの向き
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
}Camera;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);		//Drawの最初に呼び出す
Camera *GetCamera(void);


#endif