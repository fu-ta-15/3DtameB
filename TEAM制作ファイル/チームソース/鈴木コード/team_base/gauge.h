//##################################################################################################################################################################//
//
// �Q�[�W�w�b�_�t�@�C�� [gauge.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

//=====================================================================================================================================================================//
// �Q�[�W�̎��
//=====================================================================================================================================================================//
typedef enum
{
	GAUGE_TYPE_PLAYER = 0,
	GAUGE_TYPE_ACTION,
	GAUGE_TYPE_PORTAL,
	GAUGE_TYPE_BOSS,
	GAUGE_TYPE_MAX
}GAUGE_TYPE;
typedef enum
{
	GAUGE_COVER_PLAYER = 0,
	GAUGE_COVER_ACTION,
	GAUGE_COVER_PORTAL,
	GAUGE_COVER_BOSS,
	GAUGE_COVER_MAX
}GAUGE_COVER;


//=====================================================================================================================================================================//
// �Q�[�W�̍\����
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR col;
	GAUGE_COVER type;
	bool bset;
}GaugeCover;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 changesize;
	D3DXCOLOR col;
	GAUGE_TYPE type;
	bool bset;
}Gauge;

//=====================================================================================================================================================================//
//�v���g�^�C�v�錾
//=====================================================================================================================================================================//
HRESULT InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
void DrawGaugeCover(void);
void SetGeauge(GAUGE_TYPE Gtype, GAUGE_COVER GCtype, D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
Gauge *GetGauge(void);
GaugeCover *GetGaugeCover(void);

#endif 