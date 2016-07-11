#pragma once


// CAlertBox 对话框

class CAlertBox : public CDialogEx
{
	DECLARE_DYNAMIC(CAlertBox)

public:
	CAlertBox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAlertBox();

// 对话框数据
	enum { IDD = IDD_ALERT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConfirmButton();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
