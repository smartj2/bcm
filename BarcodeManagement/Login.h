#pragma once


// CLogin �Ի���

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	_RecordsetPtr m_pRs;  // ��ѯ�����
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_LOGIN_DIALOG };

	CString m_UserName;  // �û���
	CString m_PassWord;  // ����
	CButton m_Login;     // ��¼��ť
	CButton m_Cancel;    // ȡ����ť

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
};
