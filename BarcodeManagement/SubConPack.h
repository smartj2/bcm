#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSubConPack 对话框

class CSubConPack : public CDialogEx
{
	DECLARE_DYNAMIC(CSubConPack)

public:
	_RecordsetPtr m_pRs; // 查询结果集
//	void AddToGird();
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
	CString m_MarkBox;
	CComboBox m_MI;
	CComboBox m_Qty;
	afx_msg void OnEnChangeAtlcodeEdit();
	afx_msg void OnEnChangeMycodeEdit();
	afx_msg void OnBnClickedPackButton();
	afx_msg void OnBnClickedExitButton();

	bool CheckCoreCode(const CString& coreCode);
	bool CheckBatteryCode(const CString& batteryCode);
	CString m_ATLCode;
	CComboBox m_ATLLen;
	CComboBox m_ATLWeek;
	CListCtrl m_BCMList;
	CComboBox m_Material;
	CComboBox m_Model;
	CString m_MYCode;
	CComboBox m_MYLen;
	CComboBox m_MYWeek;
	CComboBox m_SGMQA;
	CComboBox m_SGMLine;
};
