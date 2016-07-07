#pragma once
#include "afxcmn.h"


// CBISSetting 对话框

class CBISSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CBISSetting)

public:
	_RecordsetPtr m_pRs;
	CBISSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBISSetting();

// 对话框数据
	enum { IDD = IDD_BISSETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_ATLLen;
	CString m_Material;
	CString m_MI;
	CString m_Model;
	CString m_Qty;
	CString m_Supplier;
	CListCtrl m_BISList;
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedModButton();
	afx_msg void OnBnClickedExitButton();
};
