#pragma once


// CRelieveBinding �Ի���

class CRelieveBinding : public CDialogEx
{
	DECLARE_DYNAMIC(CRelieveBinding)

public:
	CRelieveBinding(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRelieveBinding();

// �Ի�������
	enum { IDD = IDD_RELIEVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
