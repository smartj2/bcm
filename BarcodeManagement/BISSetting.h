#pragma once


// CBISSetting �Ի���

class CBISSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CBISSetting)

public:
	CBISSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBISSetting();

// �Ի�������
	enum { IDD = IDD_BISSETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
