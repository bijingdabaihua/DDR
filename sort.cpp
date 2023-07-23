#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
    // 注册窗口类
    const char CLASS_NAME[]  = "Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindow(CLASS_NAME, "Sample Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150,
        nullptr, nullptr, hInstance, nullptr);

    // 创建按钮
    HWND hwndButton1 = CreateWindow("BUTTON", "Button 1", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 100, 30, hwnd, nullptr, hInstance, nullptr);
    HWND hwndButton2 = CreateWindow("BUTTON", "Button 2", WS_TABSTOP | WS_VISIBLE | WS_CHILD,
        150, 50, 100, 30, hwnd, nullptr, hInstance, nullptr);

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);

    // 消息循环
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if ((HWND)lParam == hwndButton1)
                {
                    MessageBox(hwnd, "Button 1 clicked", "Notification", MB_OK);
                }
                else if ((HWND)lParam == hwndButton2)
                {
                    MessageBox(hwnd, "Button 2 clicked", "Notification", MB_OK);
                }
            }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
