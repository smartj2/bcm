#pragma once


// CSinglePack �Ի���

class CSinglePack : public CDialogEx
{
	DECLARE_DYNAMIC(CSinglePack)

public:
	CSinglePack(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSinglePack();

// �Ի�������
	enum { IDD = IDD_SINGLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
