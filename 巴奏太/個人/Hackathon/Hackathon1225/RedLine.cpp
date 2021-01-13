////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ���胉�C���̏��� [RedLine.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/25
//
////////////////////////////////////////////////////////////////////////////////
#include "RedLine.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRedLine = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureRedLine = NULL;		//�e�N�X�`���̃|�C���^
D3DXVECTOR3 posRedLine;								//�ʒu
D3DXVECTOR3 rotRedLine;								//����
D3DXMATRIX	mtxworldRedLine;						//���[���h�}�g���b�N�X

////////////////////////////////////////////////////////////////////////////////
//�ǂ̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitRedLine(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bga.png", &g_pTextureRedLine);

	posRedLine = D3DXVECTOR3(0.0f, 60.0f, 200.0f);
	rotRedLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffRedLine, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRedLine->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-500, -300, 0);
	pVtx[1].pos = D3DXVECTOR3(-500, 300, 0);
	pVtx[2].pos = D3DXVECTOR3(500, -300, 0);
	pVtx[3].pos = D3DXVECTOR3(500, 300, 0);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRedLine->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�ǂ̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitRedLine(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffRedLine != NULL)
	{
		g_pVtxBuffRedLine->Release();	//�J��
		g_pVtxBuffRedLine = NULL;		//������
	}
	if (g_pTextureRedLine != NULL)
	{
		g_pTextureRedLine->Release();	//�J��
		g_pTextureRedLine = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�ǂ̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateRedLine(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//�ǂ̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawRedLine(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���A���t�@�u�����f�B���O���s�Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// ���A���t�@�u�����f�B���O�X�e�[�g��ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxworldRedLine);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotRedLine.y, rotRedLine.x, rotRedLine.z);
	D3DXMatrixMultiply(&mtxworldRedLine, &mtxworldRedLine, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posRedLine.x, posRedLine.y, posRedLine.z);
	D3DXMatrixMultiply(&mtxworldRedLine, &mtxworldRedLine, &mtxTrans);

	//���[���h�}�g���b�N�X
	pDevice->SetTransform(D3DTS_WORLD, &mtxworldRedLine);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRedLine, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}