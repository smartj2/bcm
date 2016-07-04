#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSubConPack 对话框

class CSubConPack : public CDialogEx
{
	DECLARE_DYNAMIC(CSubConPack)

public:
	_RecordsetPtr m_pRs; // 查询结果集
	void AddToGird();
	CSubConPack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubConPack();

// 对话框数据
	enum { IDD = IDD_PACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
