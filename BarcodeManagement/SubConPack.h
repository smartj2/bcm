#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSubConPack �Ի���

class CSubConPack : public CDialogEx
{
	DECLARE_DYNAMIC(CSubConPack)

public:
	_RecordsetPtr m_pRs; // ��ѯ�����
	void AddToGird();
	CSubConPack(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubConPack();

// �Ի�������
	enum { IDD = IDD_PACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_Gird;
	CString m_MarkBox;
	CString m_Barcode;
	CComboBox m_ATL_Barcode;
	CComboBox m_MI;
	CComboBox m_Piece;
	CComboBox m_Qty;
	afx_msg void OnBnClickedPackButton();
	afx_msg void OnBnClickedExitButton();
	afx_msg void OnEnChangeBarcodeEdit();
};
