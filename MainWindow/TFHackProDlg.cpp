﻿
// TFHackProDlg.cpp: 实现文件
//

#include "framework.h"
#include "TFHackPro.h"
#include "TFHackProDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"
#include "Main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTFHackProDlg 对话框



CTFHackProDlg::CTFHackProDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TFHACKPRO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CTFHackProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTFHackProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTFHackProDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTFHackProDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTFHackProDlg 消息处理程序

BOOL CTFHackProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTFHackProDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTFHackProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTFHackProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////

UINT LockAmmo(LPVOID lpParam)
{
	//AfxMessageBox(L"进入函数");
	DWORD dwPid = GetProcessPid(L"SFGame.exe");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	//CString str;
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		//str.Format(L"%d", GetLastError());
		//AfxMessageBox(str);
		return 0;
	}
	DWORD dwBaseAddress = GetProcessModuleBaseAddress(dwPid, (WCHAR*)L"SFGame.exe");
	DWORD dwTempAddress = 0;
	DWORD dwAmmo =999;
	DWORD dwTemp = 0;
	DWORD dwRetNum = 0;
	BOOL bFlag = FALSE;
	while (TRUE)
	{
		if (dwBaseAddress == 0){
			//AfxMessageBox(L"开启失败");
			return FALSE;
		}
		ReadProcessMemory(hProcess, (LPVOID)((DWORD)(dwBaseAddress + 0x013ED5C4)), &dwTempAddress, 4, &dwRetNum);
		if (dwTempAddress == 0){
			//AfxMessageBox(L"开启失败");
			return FALSE;
		}
		ReadProcessMemory(hProcess, (LPCVOID)(dwTempAddress + 0x228), &dwTempAddress, 4, &dwRetNum);
		ReadProcessMemory(hProcess, (LPCVOID)(dwTempAddress + 0x40C), &dwTempAddress, 4, &dwRetNum);
		ReadProcessMemory(hProcess, (LPVOID)(dwTempAddress + 0x358), &dwTemp, 4, &dwRetNum);
		if (dwTemp>0||dwTemp<1000)
		{
			WriteProcessMemory(hProcess, (LPVOID)(dwTempAddress + 0x358), &dwAmmo, 4, NULL);
		}
		Sleep(50);
	}
	//CloseHandle(hProcess);
	return FALSE;
}

CWinThread* MyThread1;

void CTFHackProDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	MyThread1 = AfxBeginThread(LockAmmo, NULL);
	//DWORD dwResult = WaitForSingleObject(MyThread, 0);
	//Sleep(800);
	//AfxMessageBox(L"开启成功");
	UpdateData(FALSE);
}


void CTFHackProDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	TCHAR exeFullPath[260];
	const WCHAR* dllName = L"SpeedHackDLL_2.dll";
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	for (int i = wcslen(exeFullPath); i > 0; i--)
	{
		if (exeFullPath[i] == '\\')
		{
			memcpy(&exeFullPath[i + 1], dllName, 38);
			break;
		}
	}
	if (RemoteThreadDllInject(L"SFGame.exe", exeFullPath))
		AfxMessageBox(L"注入成功");

	UpdateData(FALSE);
}
