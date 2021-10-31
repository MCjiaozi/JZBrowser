#pragma once


// SetupWizard 对话框

class SetupWizard : public CDialogEx
{
	DECLARE_DYNAMIC(SetupWizard)

public:
	SetupWizard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SetupWizard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SetupWizard };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	CString GetConfig(CString AppName, CString KeyName);
	void WriteConfig(CString AppName, CString KeyName, CString Key);
	afx_msg void OnBnClickedRadioHomepage1();
	afx_msg void OnBnClickedRadioSearchengine1();
	afx_msg void OnBnClickedRadioSearchengine2();
	afx_msg void OnBnClickedRadioSearchengine3();
	afx_msg void OnBnClickedRadioSearchengine4();
	afx_msg void OnBnClickedRadioSearchengine5();
	afx_msg void OnBnClickedRadioHomepage2();
	afx_msg void OnBnClickedAdvance();
	afx_msg void OnBnClickedCheckupdate();
};
