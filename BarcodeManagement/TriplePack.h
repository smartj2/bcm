#pragma once

#include <string>
#include "afxwin.h"
#include "afxcmn.h"
using namespace std;

// CTriplePack �Ի���

class CTriplePack : public CDialogEx
{
	DECLARE_DYNAMIC(CTriplePack)

public:
	_RecordsetPtr m_pRs; // ��ѯ�����
	CString TraySize;        // ���̴�С
	CTriplePack(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTriplePack();

// �Ի�������
	enum { IDD = IDD_TRIPLEPACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int bnum;
	int tray;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CString m_MarkBox;
	CString m_Qty;
	CString m_ATLCode;
	CString m_MYCode;

	CString m_SGMQA;
	CString m_SGMLine;
	CString m_Remark;
	CString m_Current;

	CComboBox m_Model;
	CComboBox m_MI;
	CComboBox m_Material;
	CComboBox m_ATLLen;
	CComboBox m_MYLen;

	CComboBox m_ATLWeek;
	CComboBox m_MYWeek;
	CComboBox m_MYDay;
	CListCtrl m_BCMList;
	CProgressCtrl m_PackProgress;

	afx_msg void OnCbnSelchangeModelCombo();
	afx_msg void OnEnChangeMycodeEdit();
	afx_msg void OnEnChangeAtlcodeEdit();
	afx_msg void OnBnClickedPackButton();
	afx_msg void OnBnClickedExitButton();

	bool CheckCoreCode(const CString& coreCode);
	bool CheckBatteryCode(const CString& batteryCode);
	
	string CString2String(const CString cStr);
	CString String2CString(const string str);
	int CString2Int(const CString cStr);
	CString Int2CString(const int num);
};
