#pragma once


// CSubConPack �Ի���

class CSubConPack : public CDialogEx
{
	DECLARE_DYNAMIC(CSubConPack)

public:
	CSubConPack(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubConPack();

// �Ի�������
	enum { IDD = IDD_PACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
