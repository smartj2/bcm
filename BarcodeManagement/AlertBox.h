#pragma once


// CAlertBox �Ի���

class CAlertBox : public CDialogEx
{
	DECLARE_DYNAMIC(CAlertBox)

public:
	CAlertBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlertBox();

// �Ի�������
	enum { IDD = IDD_ALERT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConfirmButton();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
