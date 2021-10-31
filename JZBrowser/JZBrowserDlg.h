
// JZBrowserDlg.h: 头文件
//

#pragma once
#include "CEXPLORER1.h"


// CJZBrowserDlg 对话框
class CJZBrowserDlg : public CDialogEx
{
// 构造
public:
	CJZBrowserDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JZBROWSER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEXPLORER1 m_web;
	DECLARE_EVENTSINK_MAP()
	void NewWindow3Explorer1(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl);
	void TitleChangeExplorer1(LPCTSTR Text);
	void NavigateComplete2Explorer1(LPDISPATCH pDisp, VARIANT* URL);
	afx_msg void OnBnClickedButtonGo();
	afx_msg void OnBnClickedGoBack();
	afx_msg void OnBnClickedGoNext();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedStop();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedGohome();
	afx_msg void OnBnClickedSystembrowser();
	afx_msg void OnBnClickedClearcache();
	afx_msg void OnBnClickedClearcookies();
	afx_msg void OnBnClickedInternetoptions();
	void BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
//	virtual void OnOK();
//	afx_msg void OnClose();
//	afx_msg void OnClose();
//	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedGosearch();
	void BrowserGoHome();
	CString GetConfig(CString AppName, CString KeyName);
	void CJZBrowserDlg::BrowserGoSearch();
	CString URLEncode(CString strToEncode, CString strNoEncode = _T(""));
	void WriteConfig(CString AppName, CString KeyName,CString Key);
	afx_msg void OnBnClickedOpenSettings();
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
};
