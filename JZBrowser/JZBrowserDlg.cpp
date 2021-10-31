
// JZBrowserDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "JZBrowser.h"
#include "JZBrowserDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "SetupWizard.h"


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
//	virtual void OnCancel();
//	virtual void OnOK();
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
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


// CJZBrowserDlg 对话框



CJZBrowserDlg::CJZBrowserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JZBROWSER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJZBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
}

BEGIN_MESSAGE_MAP(CJZBrowserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GO, &CJZBrowserDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_GO_BACK, &CJZBrowserDlg::OnBnClickedGoBack)
	ON_BN_CLICKED(IDC_GO_NEXT, &CJZBrowserDlg::OnBnClickedGoNext)
	ON_BN_CLICKED(IDC_REFRESH, &CJZBrowserDlg::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_STOP, &CJZBrowserDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_GOHOME, &CJZBrowserDlg::OnBnClickedGohome)
	ON_BN_CLICKED(IDC_SYSTEMBROWSER, &CJZBrowserDlg::OnBnClickedSystembrowser)
	ON_BN_CLICKED(IDC_CLEARCACHE, &CJZBrowserDlg::OnBnClickedClearcache)
	ON_BN_CLICKED(IDC_CLEARCOOKIES, &CJZBrowserDlg::OnBnClickedClearcookies)
	ON_BN_CLICKED(IDC_INTERNETOPTIONS, &CJZBrowserDlg::OnBnClickedInternetoptions)
//	ON_WM_CLOSE()
//ON_WM_CLOSE()
//ON_WM_CLOSE()
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_GOSEARCH, &CJZBrowserDlg::OnBnClickedGosearch)
ON_BN_CLICKED(IDC_OPEN_SETTINGS, &CJZBrowserDlg::OnBnClickedOpenSettings)
END_MESSAGE_MAP()


// CJZBrowserDlg 消息处理程序

BOOL CJZBrowserDlg::OnInitDialog()
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
	m_web.put_Silent(TRUE);
	if (GetConfig(_T("Settings"), _T("SetupWizard")) != _T("true") && GetConfig(_T("Settings"), _T("SetupWizard")) != _T("false")) {
		WriteConfig(_T("Settings"), _T("SetupWizard"), _T("false"));
	}
	else if(GetConfig(_T("Settings"), _T("SetupWizard")) != _T("true")){
		SetupWizard Dlg;
		Dlg.DoModal();
	}
	CString commandL = AfxGetApp()->m_lpCmdLine;
	CString commandS;
	CString commandH;
	CString commandB;
	CString commandT;
	CString commandURL=_T("");
	CString LastWindow = _T("");
	for (int comx = 1;; comx++) {
		if (AfxExtractSubString(commandS, commandL, comx, '-') == TRUE) {
			if (AfxExtractSubString(commandH, commandS, 0, ' ') == TRUE) {
				commandB = "";
				for (int comy = 1;; comy++) {
					if (AfxExtractSubString(commandT, commandS, comy, ' ') == TRUE) {
						if (comy == 1)commandB += commandT;
						else commandB += _T(" ") + commandT;
					}
					else break;
				}
				if (commandH == _T("url")) {
					commandURL = commandB;
				}
				if (commandH == _T("NewWindowFromTemp")) {
					wchar_t buffer[MAX_PATH];
					GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
					CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\temp");
					GetPrivateProfileString(_T("NewWindow"), _T("url"), _T("default"), LastWindow.GetBuffer(MAX_PATH), MAX_PATH, lpPath);
					LastWindow.ReleaseBuffer();
				}
			}
		}
		else break;
	}
	if(LastWindow!=_T(""))m_web.Navigate(LastWindow, NULL, NULL, NULL, NULL);
	else if (commandURL != _T(""))m_web.Navigate(commandURL, NULL, NULL, NULL, NULL);
	else if (GetConfig(_T("Settings"), _T("HomePage")) != _T("default")) {
		m_web.Navigate(GetConfig(_T("Settings"), _T("HomePage")), NULL, NULL, NULL, NULL);
	}
	else BrowserGoHome();
	CFont* f;
	f = new CFont;
	f->CreateFont(
		18, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FALSE, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		NULL, // nCharSet
		NULL, // nOutPrecision
		NULL, // nClipPrecision
		NULL, // nQuality
		NULL, // nPitchAndFamily
		_T("微软雅黑")); // lpszFac
	GetDlgItem(IDC_AddressBar1)->SetFont(f);
	GetDlgItem(IDC_STATIC_ADDRESS)->SetFont(f);
	GetDlgItem(IDC_BUTTON_GO)->SetFont(f);
	GetDlgItem(IDC_GO_BACK)->SetFont(f);
	GetDlgItem(IDC_GO_NEXT)->SetFont(f);
	GetDlgItem(IDC_REFRESH)->SetFont(f);
	GetDlgItem(IDC_STOP)->SetFont(f);
	GetDlgItem(IDC_GOHOME)->SetFont(f);
	GetDlgItem(IDC_SYSTEMBROWSER)->SetFont(f);
	GetDlgItem(IDC_CLEARCACHE)->SetFont(f);
	GetDlgItem(IDC_CLEARCOOKIES)->SetFont(f);
	GetDlgItem(IDC_STATE)->SetFont(f);
	GetDlgItem(IDC_SEARCHBAR)->SetFont(f);
	GetDlgItem(IDC_GOSEARCH)->SetFont(f);
	GetDlgItem(IDC_STATIC_SEARCH)->SetFont(f);
	GetDlgItem(IDC_OPEN_SETTINGS)->SetFont(f);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJZBrowserDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJZBrowserDlg::OnPaint()
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
HCURSOR CJZBrowserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CJZBrowserDlg, CDialogEx)
	ON_EVENT(CJZBrowserDlg, IDC_EXPLORER1, 273, CJZBrowserDlg::NewWindow3Explorer1, VTS_PDISPATCH VTS_PBOOL VTS_UI4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CJZBrowserDlg, IDC_EXPLORER1, 113, CJZBrowserDlg::TitleChangeExplorer1, VTS_BSTR)
	ON_EVENT(CJZBrowserDlg, IDC_EXPLORER1, 252, CJZBrowserDlg::NavigateComplete2Explorer1, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CJZBrowserDlg, IDC_EXPLORER1, 250, CJZBrowserDlg::BeforeNavigate2Explorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CJZBrowserDlg, IDC_EXPLORER1, 259, CJZBrowserDlg::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()





void CJZBrowserDlg::BrowserGoHome() {
	if (GetConfig(_T("Settings"), _T("HomePage")) != _T("default")) {
		m_web.Navigate(GetConfig(_T("Settings"), _T("HomePage")), NULL, NULL, NULL, NULL);
	}
	else m_web.GoHome();
}


void CJZBrowserDlg::BrowserGoSearch() {
	CString SearchEngine;
	CString SearchName;
	if (GetConfig(_T("Settings"), _T("SearchEngine")) != _T("default")) {
		SearchEngine = GetConfig(_T("Settings"), _T("SearchEngine"));
	}
	else SearchEngine = _T("https://www.baidu.com/s?ie=UTF-8&wd=");
	SearchEngine.ReleaseBuffer();
	GetDlgItemText(IDC_SEARCHBAR, SearchName);
	m_web.Navigate(SearchEngine + URLEncode(SearchName, NULL), NULL, NULL, NULL, NULL);
}


CString CJZBrowserDlg::GetConfig(CString AppName, CString KeyName) {
	CString Key;
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\config.ini");
	GetPrivateProfileString(AppName, KeyName, _T("default"), Key.GetBuffer(MAX_PATH), MAX_PATH, lpPath);
	Key.ReleaseBuffer();
	return Key;
}


void CJZBrowserDlg::WriteConfig(CString AppName, CString KeyName, CString Key) {
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\config.ini");
	WritePrivateProfileString(AppName, KeyName, Key, lpPath);
}


// 对 CString URL 进行编码  // strNoEncode 为不编码的字符
CString CJZBrowserDlg::URLEncode(CString strToEncode, CString strNoEncode)
{
	// 默认不转换的字符
	if (strNoEncode.IsEmpty())
	{
		strNoEncode = _T("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:/.?_-=&");
	}

	CString strEncoded;  // 转换结果
	for (int i = 0; i < strToEncode.GetLength(); i++)
	{
		CString strCur = strToEncode.Mid(i, 1);  // 当前要被转换的字符

		// 判断是否需要转换
		BOOL bNoEncode = FALSE;
		for (int j = 0; j < strNoEncode.GetLength(); j++)
		{
			if (strCur == strNoEncode.Mid(j, 1))
			{
				bNoEncode = TRUE;
				break;
			}
		}

		// 不需要转换的字符直接拼接到要输出的字符串中
		if (bNoEncode)
		{
			strEncoded += strCur;
			continue;
		}

		// 需要转换的字符先转码
		LPCWSTR unicode = T2CW(strCur);
		int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, 0, 0, 0, 0);
		char* utf8 = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, unicode, len, utf8, len, 0, 0);

		// 转码后的字符格式化拼接到输出的字符串中
		for (int k = 0; k < len - 1; k++) // 不处理最后一个字符串终止符号
		{
			strEncoded.AppendFormat(_T("%%%02X"), utf8[k] & 0xFF);
		}
	}
	return strEncoded;
}


void CJZBrowserDlg::NewWindow3Explorer1(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\temp");
	WritePrivateProfileString(_T("NewWindow"), _T("url"), CString(bstrUrl), lpPath);
	CString sPath;
	CFileFind Cfind;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	ShellExecute(NULL, NULL, sPath+_T("\\JZBrowser.exe"), _T("-NewWindowFromTemp"), NULL, SW_SHOW);
	*Cancel = TRUE;
	// TODO: 在此处添加消息处理程序代码
}


void CJZBrowserDlg::TitleChangeExplorer1(LPCTSTR Text)
{
	// TODO: 在此处添加消息处理程序代码
	this->SetWindowText((CString)Text + _T(" - 饺子浏览器"));
}

void CJZBrowserDlg::NavigateComplete2Explorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码
	GetDlgItem(IDC_AddressBar1)->SetWindowText(m_web.get_LocationURL());
}


void CJZBrowserDlg::OnBnClickedButtonGo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Address;
	GetDlgItemText(IDC_AddressBar1, Address);
	m_web.Navigate(Address, NULL, NULL, NULL, NULL);
}


void CJZBrowserDlg::OnBnClickedGoBack()
{
	// TODO: 在此添加控件通知处理程序代码
	m_web.GoBack();
}


void CJZBrowserDlg::OnBnClickedGoNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_web.GoForward();
}


void CJZBrowserDlg::OnBnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	m_web.Refresh();
	GetDlgItem(IDC_STATE)->SetWindowText(_T("已刷新页面。"));
}


void CJZBrowserDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_web.Stop();
	GetDlgItem(IDC_STATE)->SetWindowText(_T("已停止载入页面。"));
}


void CJZBrowserDlg::OnBnClickedGohome()
{
	// TODO: 在此添加控件通知处理程序代码
	BrowserGoHome();
}


void CJZBrowserDlg::OnBnClickedSystembrowser()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, NULL, m_web.get_LocationURL(), NULL, NULL, SW_SHOW);
}


void CJZBrowserDlg::OnBnClickedClearcache()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, NULL, _T("RunDll32.exe"), _T("InetCpl.cpl,ClearMyTracksByProcess 8"), NULL, SW_SHOW);
}


void CJZBrowserDlg::OnBnClickedClearcookies()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, NULL, _T("RunDll32.exe"), _T("InetCpl.cpl,ClearMyTracksByProcess 2"), NULL, SW_SHOW);
}


void CJZBrowserDlg::OnBnClickedInternetoptions()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, NULL, _T("inetcpl.cpl"), NULL, NULL, SW_SHOW);
}


void CJZBrowserDlg::BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	// TODO: 在此处添加消息处理程序代码
	GetDlgItem(IDC_STATE)->SetWindowText(_T("正在载入：") + CString((LPCTSTR)_bstr_t(URL))+_T(" ..."));
}

void CJZBrowserDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CJZBrowserDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CJZBrowserDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDCANCEL);
	//CDialogEx::OnClose();
}


BOOL CJZBrowserDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message && 13 == pMsg->wParam)
	{
		if (GetDlgItem(IDC_AddressBar1) == GetFocus())
		{
			CString Address;
			GetDlgItemText(IDC_AddressBar1, Address);
			m_web.Navigate(Address, NULL, NULL, NULL, NULL);
			return TRUE;
		}
		else if (GetDlgItem(IDC_SEARCHBAR) == GetFocus())
		{
			BrowserGoSearch();
			return TRUE;
		}
		else
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CJZBrowserDlg::OnBnClickedGosearch()
{
	// TODO: 在此添加控件通知处理程序代码
	BrowserGoSearch();
}


void CJZBrowserDlg::OnBnClickedOpenSettings()
{
	// TODO: 在此添加控件通知处理程序代码
	SetupWizard* pOneDlgObj = new SetupWizard;
	if (pOneDlgObj)
	{
		BOOL ret = pOneDlgObj->Create(IDD_SetupWizard, GetDesktopWindow());
	}
	pOneDlgObj->ShowWindow(SW_SHOW);
}


void CJZBrowserDlg::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码
	GetDlgItem(IDC_STATE)->SetWindowText(_T("完成。"));
}
