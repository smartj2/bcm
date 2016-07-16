#pragma once


// CClearData 对话框

class CClearData : public CDialogEx
{
	DECLARE_DYNAMIC(CClearData)

public:
	CClearData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClearData();

// 对话框数据
	enum { IDD = IDD_CLEAR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_ClearBox;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
