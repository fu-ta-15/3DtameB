#include "Main.h"
#include "DirectX.h"
int g_nCountFPS;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow)
{
	//FPS
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//window class set
	WNDCLASSEX WCEX;
	WCEX.cbClsExtra = 0;
	WCEX.cbSize = sizeof(WCEX);
	WCEX.cbWndExtra = 0;
	WCEX.hbrBackground = (HBRUSH)COLOR_WINDOW;
	WCEX.hCursor = NULL;
	WCEX.hIcon = NULL;
	WCEX.hIconSm = NULL;
	WCEX.hInstance = hInstance;
	WCEX.lpfnWndProc = WindowProc;
	WCEX.lpszClassName = "WCEX1";
	WCEX.lpszMenuName = NULL;
	WCEX.style = CS_CLASSDC;

	//window class register
	RegisterClassEx(&WCEX);

	//window create
	HWND hWnd = CreateWindowEx
	(
		NULL,
		"WCEX1",
		"WND1",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//DirectX window create
	if (FAILED(Init(hInstance, hWnd, TRUE))) return -1;

	ShowWindow(hWnd, nCmdShow); //SW_SHOWMAXIMIZED -> FULLSCREEN mode
	UpdateWindow(hWnd);

	MSG msg;
	while (true)
	{
		//peekmessage is just watch message loop (getmessage have PM_REMOVE already. when some messages came)
		//hWnd means the message which come from the hWnd window, could been used.
		//if successed will return any number except 0, when 0 has been returned it's means false
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)//NULL Šm•Û‘S•”‚Ìó‘Ô‚Åmessage‚ðŽæ‚é‚Å‚«‚éB
		{
			if (msg.message == WM_QUIT) break;//whether the message means quit
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			//if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))//????????????????????????????
			{
				dwExecLastTime = dwCurrentTime;
				Update();
				Draw();
				dwFrameCount++;
			}
		}
	}
	Uninit();

	UnregisterClass("WCEX1", WCEX.hInstance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nMsg;

	switch (uMsg)
	{
	case WM_CLOSE:
		nMsg = MessageBox(NULL, "Sure To Close?", "Confirm", MB_YESNO | MB_ICONQUESTION);
		if (nMsg == IDYES)	DestroyWindow(hWnd);//manual close and send a destroy message to system (WM_DESTROY)
		else return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//insert a WM_QUIT message into the message loop
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nMsg = MessageBox(NULL, "Sure To Close?", "Confirm", MB_YESNO | MB_ICONQUESTION);
			if (nMsg == IDYES)	DestroyWindow(hWnd);
			else return 0;
			break;
		}
		break;
	default:
		break;
	}

	//default window procedure
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

