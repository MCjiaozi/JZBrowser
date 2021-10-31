// SetupWizard.cpp: 实现文件
//

#include "pch.h"
#include "JZBrowser.h"
#include "SetupWizard.h"
#include "afxdialogex.h"


// SetupWizard 对话框

IMPLEMENT_DYNAMIC(SetupWizard, CDialogEx)

SetupWizard::SetupWizard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SetupWizard, pParent)
{

}

SetupWizard::~SetupWizard()
{
}

void SetupWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CFont* f;
	f = new CFont;
	f->CreateFont(
		38, // nHeight
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
		_T("华文中宋")); // lpszFac
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(f);
	CFont* h;
	h = new CFont;
	h->CreateFont(
		18, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		TRUE, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		NULL, // nCharSet
		NULL, // nOutPrecision
		NULL, // nClipPrecision
		NULL, // nQuality
		NULL, // nPitchAndFamily
		_T("微软雅黑")); // lpszFac
	GetDlgItem(IDOK)->SetFont(h);
	GetDlgItem(IDC_STATIC_S1)->SetFont(h);
	GetDlgItem(IDC_RADIO_HomePage_1)->SetFont(h);
	GetDlgItem(IDC_RADIO_HomePage_2)->SetFont(h);
	GetDlgItem(IDC_EDIT_HomePage)->SetFont(h);
	GetDlgItem(IDC_STATIC_S2)->SetFont(h);
	GetDlgItem(IDC_RADIO_SearchEngine_1)->SetFont(h);
	GetDlgItem(IDC_RADIO_SearchEngine_2)->SetFont(h);
	GetDlgItem(IDC_RADIO_SearchEngine_3)->SetFont(h);
	GetDlgItem(IDC_RADIO_SearchEngine_4)->SetFont(h);
	GetDlgItem(IDC_RADIO_SearchEngine_5)->SetFont(h);
	GetDlgItem(IDC_EDIT_SearchEngine)->SetFont(h);
	GetDlgItem(IDC_CHECKUPDATE)->SetFont(h);
	CFont* i;
	i = new CFont;
	i->CreateFont(
		24, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		TRUE, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		NULL, // nCharSet
		NULL, // nOutPrecision
		NULL, // nClipPrecision
		NULL, // nQuality
		NULL, // nPitchAndFamily
		_T("微软雅黑")); // lpszFac
	GetDlgItem(IDC_ADVANCE)->SetFont(i);


	if (GetConfig(_T("Settings"), _T("SetupWizard")) != _T("true") && GetConfig(_T("Settings"), _T("SetupWizard")) != _T("false")) {
		WriteConfig(_T("Settings"), _T("SetupWizard"), _T("false"));
	}
	else if (GetConfig(_T("Settings"), _T("SetupWizard")) == _T("true")) {
		if (GetConfig(_T("Settings"), _T("HomePage")) == _T("default")) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_HomePage_1);
			pBtn->SetCheck(1);
		}
		else {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_HomePage_2);
			pBtn->SetCheck(1);
			GetDlgItem(IDC_EDIT_HomePage)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_HomePage)->SetWindowText(GetConfig(_T("Settings"), _T("HomePage")));
		}
		if (GetConfig(_T("Settings"), _T("SearchEngine")) == _T("default")) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_1);
			pBtn->SetCheck(1);
		}
		else if (GetConfig(_T("Settings"), _T("SearchEngine")) == _T("https://www.baidu.com/s?ie=UTF-8&wd=")) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_1);
			pBtn->SetCheck(1);
		}
		else if (GetConfig(_T("Settings"), _T("SearchEngine")) == _T("https://www.bing.com/search?q=")) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_2);
			pBtn->SetCheck(1);
		}
		else if (GetConfig(_T("Settings"), _T("SearchEngine")) == _T("https://www.google.com/search?q=")) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_3);
			pBtn->SetCheck(1);
		}
		else if (GetConfig(_T("Settings"), _T("SearchEngine")) == _T("https://www.sogou.com/web?query=")) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_4);
			pBtn->SetCheck(1);
		}
		else {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_5);
			pBtn->SetCheck(1);
			GetDlgItem(IDC_EDIT_SearchEngine)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_HomePage)->SetWindowText(GetConfig(_T("Settings"), _T("SearchEngine")));
		}

	}
	else {
		CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_HomePage_1);
		pBtn->SetCheck(1);
		CButton* pBtna = (CButton*)GetDlgItem(IDC_RADIO_SearchEngine_1);
		pBtna->SetCheck(1);
	}
}


BEGIN_MESSAGE_MAP(SetupWizard, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetupWizard::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_HomePage_1, &SetupWizard::OnBnClickedRadioHomepage1)
	ON_BN_CLICKED(IDC_RADIO_SearchEngine_1, &SetupWizard::OnBnClickedRadioSearchengine1)
	ON_BN_CLICKED(IDC_RADIO_SearchEngine_2, &SetupWizard::OnBnClickedRadioSearchengine2)
	ON_BN_CLICKED(IDC_RADIO_SearchEngine_3, &SetupWizard::OnBnClickedRadioSearchengine3)
	ON_BN_CLICKED(IDC_RADIO_SearchEngine_4, &SetupWizard::OnBnClickedRadioSearchengine4)
	ON_BN_CLICKED(IDC_RADIO_SearchEngine_5, &SetupWizard::OnBnClickedRadioSearchengine5)
	ON_BN_CLICKED(IDC_RADIO_HomePage_2, &SetupWizard::OnBnClickedRadioHomepage2)
	ON_BN_CLICKED(IDC_ADVANCE, &SetupWizard::OnBnClickedAdvance)
	ON_BN_CLICKED(IDC_CHECKUPDATE, &SetupWizard::OnBnClickedCheckupdate)
END_MESSAGE_MAP()


// SetupWizard 消息处理程序


CString SetupWizard::GetConfig(CString AppName, CString KeyName) {
	CString Key;
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\config.ini");
	GetPrivateProfileString(AppName, KeyName, _T("default"), Key.GetBuffer(MAX_PATH), MAX_PATH, lpPath);
	return Key;
}


void SetupWizard::WriteConfig(CString AppName, CString KeyName, CString Key) {
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\config.ini");
	WritePrivateProfileString(AppName, KeyName, Key, lpPath);
}


void SetupWizard::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SetupWizard::OnOK();
}


void SetupWizard::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (((CButton*)GetDlgItem(IDC_RADIO_HomePage_1))->GetCheck() == 1) {
		WriteConfig(_T("Settings"), _T("HomePage"), _T("default"));
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_HomePage_2))->GetCheck() == 1) {
		CString HomePage;
		GetDlgItemText(IDC_EDIT_HomePage, HomePage);
		WriteConfig(_T("Settings"), _T("HomePage"), HomePage);
	}
	if (((CButton*)GetDlgItem(IDC_RADIO_SearchEngine_1))->GetCheck() == 1) {
		WriteConfig(_T("Settings"), _T("SearchEngine"), _T("https://www.baidu.com/s?ie=UTF-8&wd="));
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_SearchEngine_2))->GetCheck() == 1) {
		WriteConfig(_T("Settings"), _T("SearchEngine"), _T("https://www.bing.com/search?q="));
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_SearchEngine_3))->GetCheck() == 1) {
		WriteConfig(_T("Settings"), _T("SearchEngine"), _T("https://www.google.com/search?q="));
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_SearchEngine_4))->GetCheck() == 1) {
		WriteConfig(_T("Settings"), _T("SearchEngine"), _T("https://www.sogou.com/web?query="));
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO_SearchEngine_5))->GetCheck() == 1) {
		CString SearchEngine;
		GetDlgItemText(IDC_EDIT_SearchEngine, SearchEngine);
		WriteConfig(_T("Settings"), _T("SearchEngine"), SearchEngine);
	}
	WriteConfig(_T("Settings"), _T("SetupWizard"), _T("true"));
	CDialogEx::OnOK();
}


void SetupWizard::OnBnClickedRadioHomepage1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_HomePage)->EnableWindow(FALSE);
}


void SetupWizard::OnBnClickedRadioHomepage2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_HomePage)->EnableWindow(TRUE);
}


void SetupWizard::OnBnClickedRadioSearchengine1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SearchEngine)->EnableWindow(FALSE);
}


void SetupWizard::OnBnClickedRadioSearchengine2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SearchEngine)->EnableWindow(FALSE);
}


void SetupWizard::OnBnClickedRadioSearchengine3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SearchEngine)->EnableWindow(FALSE);
}


void SetupWizard::OnBnClickedRadioSearchengine4()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SearchEngine)->EnableWindow(FALSE);
}


void SetupWizard::OnBnClickedRadioSearchengine5()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SearchEngine)->EnableWindow(TRUE);
}


void SetupWizard::OnBnClickedAdvance()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\MCjiaozi\\JZBrowser\\config.ini");
	ShellExecute(NULL, NULL, lpPath, NULL, NULL, SW_SHOW);
}


void SetupWizard::OnBnClickedCheckupdate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sPath;
	CFileFind Cfind;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	ShellExecute(NULL, NULL, sPath + _T("\\updater.exe"), NULL, NULL, SW_SHOW);
}
