//===========================================================================================================
//
// カメラの設定 [camera.h]
// Author: fukuyama syuya
//
//===========================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=================================================================================================
//カメラの構造体
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 posV;							//視点
	D3DXVECTOR3 posVDest;						//目的の視点
	D3DXVECTOR3 posR;							//注視点
	D3DXVECTOR3 posRDest;						//目的の注視点
	D3DXVECTOR3 vecU;							//上方向ベクトル
	D3DXVECTOR3 rot;							//カメラの向き
	D3DXMATRIX mtxPlojection;					//プロジェクションマトリックス
	D3DXMATRIX mtxView;							//ビューマトリックス
}Camera;

//=================================================================================================
//プロトタイプ宣言
//=================================================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif

