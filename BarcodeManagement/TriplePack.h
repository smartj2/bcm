#pragma once


// CTriplePack �Ի���

class CTriplePack : public CDialogEx
{
	DECLARE_DYNAMIC(CTriplePack)

public:
	CTriplePack(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTriplePack();

// �Ի�������
	enum { IDD = IDD_TRIPLEPACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
