#pragma once


// CClearData �Ի���

class CClearData : public CDialogEx
{
	DECLARE_DYNAMIC(CClearData)

public:
	CClearData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClearData();

// �Ի�������
	enum { IDD = IDD_CLEAR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_ClearBox;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
