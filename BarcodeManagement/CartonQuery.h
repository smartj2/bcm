#pragma once


// CCartonQuery �Ի���

class CCartonQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CCartonQuery)

public:
	CCartonQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCartonQuery();

// �Ի�������
	enum { IDD = IDD_QUERY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
