//
//
// �E�H�[���w�b�_�[ [wall.h]
//
//
//
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

//
// �}�N����`
//
#define MAX_WALL (256)			// �ǂ̍ő吔

//
// �\���̂̒�`
//
typedef struct
{
	D3DXVECTOR3 pos;			// ���S���W
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Wall;

//
// �v���g�^�C�v�錾
//
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetVertexWall(int nIdx);
Wall *GetWall(void);

#endif