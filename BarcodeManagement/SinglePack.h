#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <string>
using namespace std;

// CSinglePack �Ի���

class CSinglePack : public CDialogEx
{
	DECLARE_DYNAMIC(CSinglePack)

public:
	_RecordsetPtr m_pRs; // ��ѯ�����
	CString TraySize;        // ���̴�С
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
	CString m_MarkBox;
	CString m_Qty;
	CString m_SGMQA;
	CString m_Remark;
	CString m_ATLCode;
	CString m_SGMLine;
	CString m_Current;

	CComboBox m_Model;
	CComboBox m_MI;
	CComboBox m_Material;
	CComboBox m_ATLLen;
	CComboBox m_ATLWeek;
	CListCtrl m_BCMList;
	afx_msg void OnCbnSelchangeModelCombo();
	afx_msg void OnEnChangeAtlcodeEdit();
	afx_msg void OnBnClickedPackButton();
	afx_msg void OnBnClickedExitButton();

	bool CheckCoreCode(const CString& coreCode);
	
	string CString2String(const CString cStr);
	CString String2CString(const string str);
	int CString2Int(const CString cStr);
	CString Int2CString(const int num);
};
