#pragma once


// CProductReport �Ի���

class CProductReport : public CDialogEx
{
	DECLARE_DYNAMIC(CProductReport)

public:
	CProductReport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProductReport();

// �Ի�������
	enum { IDD = IDD_REPORT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
