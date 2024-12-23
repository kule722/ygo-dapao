// dapao.cpp : 定义应用程序的入口点。  
//  
#include "framework.h"  
#include "dapao.h"  

#define MAX_LOADSTRING 100  
#define WINDOW_WIDTH 400 // 窗口宽度  
#define WINDOW_HEIGHT 300 // 窗口高度  

// 全局变量:  
HINSTANCE hInst;                              // 当前实例  
WCHAR szTitle[MAX_LOADSTRING];                // 标题栏文本  
WCHAR szWindowClass[MAX_LOADSTRING];          // 主窗口类  

// 数据结构  
int X_set[] = { 3, 3, 4, 4, 5, 5 };             // 固定的X集合  
int Y_set[] = { 1, 2, 3, 4, 5, 6 };             // 固定的Y集合  
const int x_size = sizeof(X_set) / sizeof(X_set[0]); // X集合大小  
const int y_size = sizeof(Y_set) / sizeof(Y_set[0]); // Y集合大小  

// 函数声明  
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
void solve(int A, int B);

// 程序入口：Windows 应用  
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DAPAO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DAPAO));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DAPAO));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 设置背景颜色  
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DAPAO);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 保存实例句柄  

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hAInput, hBInput, hCalculateButton, hLabel;

    switch (message)
    {
    case WM_CREATE:
        // 创建输入框和按钮控件  
        hAInput = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 10, 10, 120, 25, hWnd, NULL, hInst, NULL);
        hBInput = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 10, 45, 120, 25, hWnd, NULL, hInst, NULL);
        hCalculateButton = CreateWindowW(L"BUTTON", L"计算", WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 80, 120, 25, hWnd, (HMENU)3, hInst, NULL);

        // 创建标签显示“kule722”并设置其位置  
        hLabel = CreateWindowW(L"STATIC", L"kule722", WS_CHILD | WS_VISIBLE | SS_RIGHT, 300, 250, 100, 25, hWnd, NULL, hInst, NULL);
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        if (wmId == 3) // 计算按钮被点击  
        {
            int A, B;
            WCHAR buffer[10];
            GetWindowTextW(hAInput, buffer, 10);
            A = _wtoi(buffer);
            GetWindowTextW(hBInput, buffer, 10);
            B = _wtoi(buffer);
            solve(A, B);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_GETMINMAXINFO:
    {
        // 设置窗口大小限制  
        MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
        pMinMax->ptMinTrackSize.x = WINDOW_WIDTH; // 最小宽度  
        pMinMax->ptMinTrackSize.y = WINDOW_HEIGHT; // 最小高度  
        pMinMax->ptMaxTrackSize.x = WINDOW_WIDTH; // 最大宽度  
        pMinMax->ptMaxTrackSize.y = WINDOW_HEIGHT; // 最大高度  
        break;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void solve(int A, int B) {
    int found = 0;
    WCHAR result[1024] = L"符合条件的解为：\n";

    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            int X = X_set[i];
            int Y = Y_set[j];
            if (2 * X + Y == A && X + Y == B) {
                WCHAR temp[100];
                swprintf(temp, 100, L"选择 X = %d, Y = %d\n", X, Y);
                wcscat_s(result, sizeof(result) / sizeof(WCHAR), temp);
                found = 1;
            }
        }
    }

    if (!found) {
        wcscat_s(result, sizeof(result) / sizeof(WCHAR), L"没有找到符合条件的解。\n");
    }

    MessageBox(NULL, result, L"结果", MB_OK);
}

// “关于”框的消息处理程序。  
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}