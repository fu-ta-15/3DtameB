//-----------------------------------------------------------------------------
//
// �|�[�^������ �w�b�_�[ [portal.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _PORTAL_H_
#define _PORTAL_H_
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PORTAL_WIDTH (30)		// portal width
#define PORTAL_HEIGHT (30)		// portal height

//-----------------------------------------------------------------------------
// �|�[�^���̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	bool bActive;			// �g���邩
	bool bDraw;				// �`�悷�邩
} Portal;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitPortal(void);
void UninitPortal(void);
void UpdatePortal(void);
void DrawPortal(void);
void ActivatePortal(bool bActive, bool bDraw);
Portal GetPortal(void);


#endif