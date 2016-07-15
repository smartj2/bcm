#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <string>
using namespace std;

// CSubConPack 对话框

class CSubConPack : public CDialogEx
{
	DECLARE_DYNAMIC(CSubConPack)

public:
	_RecordsetPtr m_pRs; // 查询结果集
	CString TraySize;        // 托盘大小
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
	CString m_Qty;
	CString m_ATLCode;		//电芯码
	CString m_MYCode;		//电池码
	
	CString m_SGMQA;
	CString m_SGMLine;
	CString m_Remark;

	CComboBox m_Model;
	CComboBox m_MI;
	CComboBox m_Material;
	CComboBox m_ATLLen;
	CComboBox m_MYLen;

	CComboBox m_ATLWeek;
	CComboBox m_MYWeek;
	CListCtrl m_BCMList;
	CProgressCtrl m_PackProgress;
	
	afx_msg void OnEnKillfocusPackEdit();
	afx_msg void OnCbnSelchangeModelCombo();
	afx_msg void OnEnChangeAtlcodeEdit();
	afx_msg void OnEnChangeMycodeEdit();
	afx_msg void OnBnClickedPackButton();
	afx_msg void OnBnClickedExitButton();

	bool CheckCoreCode(const CString& coreCode);
	bool CheckBatteryCode(const CString& batteryCode);
	
	string CString2String(const CString cStr);
	CString String2CString(const string str);
	int CString2Int(const CString cStr);
	CString Int2CString(const int num);
};
