#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <string>
using namespace std;

// CSeriesBattery �Ի���

class CSeriesBattery : public CDialogEx
{
	DECLARE_DYNAMIC(CSeriesBattery)

public:
	_RecordsetPtr m_pRs; // ��ѯ�����
	CSeriesBattery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSeriesBattery();

// �Ի�������
	enum { IDD = IDD_SERIES_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int bnum;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_ATLCode1;
	CString m_ATLCode2;
	CComboBox m_Model;
	CComboBox m_ATLWeek;
	CListCtrl m_ATLList;
	afx_msg void OnEnChangeAtlcode1Edit();
	afx_msg void OnEnChangeAtlcode2Edit();

	bool CheckCoreCode(const CString& coreCode);
	
	string CString2String(const CString cStr);
	CString String2CString(const string str);
	int CString2Int(const CString cStr);
	CString Int2CString(const int num);
	CString m_ClearCode;
	afx_msg void OnBnClickedClearButton();
};
