#pragma once


// CSGMLine �Ի���

class CSGMLine : public CDialogEx
{
	DECLARE_DYNAMIC(CSGMLine)

public:
	CSGMLine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSGMLine();

// �Ի�������
	enum { IDD = IDD_SGMSETTINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
