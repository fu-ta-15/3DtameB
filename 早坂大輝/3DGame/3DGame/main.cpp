//=============================================================================
//
// DirectX01 [main.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"						//�C���N���[�h�t�@�C��
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "Billboard.h"

#include <stdio.h>

//=============================================================================
// �}�N����`
//=============================================================================
#define CLASS_NAME "WindowClass"				//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "3DGame"					//�E�B���h�E�̖��O
#define WINDOW_POS_X (100)						//�E�B���h�E�̍���X
#define WINDOW_POS_Y (100)						//�E�B���h�E�̍���Y
#define ID_TIMER (121)							//�^�C�}�[��ID
#define TIMER_INTERVAL (1000/60)				//�^�C�}�[�̔����Ԋu

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawPoint(void);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3D9 g_pD3D = NULL;					//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;					//�t�H���g�ւ̃|�C���^
int g_nCountFPS;							//FPS�J�E���^

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,	//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)
	};
	HWND hWnd;	//�E�B���h�E�n���h��(���ʎq)
	MSG msg;	//���b�Z�[�W���i�[����

	DWORD dwExecLastTime;	//�������s�ŏI����
	DWORD dwFPSLastTime;	//FPS�v���ŏI����
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwFrameCount;		//�t���[���J�E���g

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();	//���ݎ�����ݒ�
	dwFrameCount = 0;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̑傫������
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,		//X���W
		CW_USEDEFAULT,		//Y���W
		rect.right,			//��
		rect.bottom,		//����
		NULL,
		NULL,
		hInstance,
		NULL);

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{ //Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{ //DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{	//0.5�b
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=============================================================================
// �E�B���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//�L�[���������ꍇ
	case  WM_KEYDOWN:
		//ESC�������ꂽ�ꍇ
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
		}
		break;

		//�~�{�^�����������ꍇ
	case WM_CLOSE:
		DestroyWindow(hWnd);

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�ϐ��錾
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���g�p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = true;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����h(���l�̍���)�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X(�`�挳)�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

																			//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�

																			//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//�t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	InitKeyboard(hInstance, hWnd);

	//�|���S���̏���������
	InitPolygon();

	//�ǂ̏���������
	InitWall();

	//�r���{�[�h�̏���������
	InitBillboard();

	//���f���̏���������
	InitModel();

	//�e�̏���������
	InitShadow();

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�ǂ̔z�u
	SetWall();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�|���S���̏I������
	UninitPolygon();

	//�ǂ̏I������
	UninitWall();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//���f���̏I������
	UninitModel();

	//�e�̏I������
	UninitShadow();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//�t�H���g�I�u�W�F�N�g�̊J��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�|���S���̍X�V����
	UpdatePolygon();

	//�ǂ̍X�V����
	UpdateWall();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	//���f���̍X�V����
	UpdateModel();

	//�e�̍X�V����
	UpdateShadow();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	//�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);	//�E�B���h�E�̐F

	//�J�����̐ݒ菈��
	SetCamera();

	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

#ifdef _DEBUG

		//FPS�̕`�揈��
		DrawFPS();

		//���W
		DrawPoint();

#endif

		//�|���S���̕`�揈��
		DrawPolygon();

		//�ǂ̕`�揈��
		DrawWall();

		//�r���{�[�h�̕`�揈��
		DrawBillboard();

		//���f���̕`�揈��
		DrawModel();

		//�e�̕`�揈��
		DrawShadow();

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// FPS�̕`��
//=============================================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH -30, SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(0, 255, 255, 255));
}

//=============================================================================
// ���W�̕\��
//=============================================================================
void DrawPoint(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	RECT rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[512];
	int nNum = sprintf(&aStr[0], "[�J�����̎��_  :(%.2f : %.2f : %.2f)]\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	nNum += sprintf(&aStr[nNum], "[�J�����̒����_:(%.2f : %.2f : %.2f)]\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	nNum += sprintf(&aStr[nNum], "[�J�����̌���  :(%.2f)]", pCamera->rot.y);

//	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// �ǂ̔z�u
//=============================================================================
void SetWall(void)
{
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//��
//	SetWall(D3DXVECTOR3(0.0f, 0.0f, -90.0f), D3DXVECTOR3(0.0f, -3.14f, 0.0f));	//��O

}