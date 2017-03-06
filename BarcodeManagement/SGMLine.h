#pragma once
#include "afxcmn.h"


// CSGMLine �Ի���

class CSGMLine : public CDialogEx
{
	DECLARE_DYNAMIC(CSGMLine)

public:
	_RecordsetPtr m_pRs;
	CSGMLine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSGMLine();

// �Ի�������
	enum { IDD = IDD_SGMSETTINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_SGMList;

	CString m_Model;
	CString m_BMI;
	CString m_Year;
	CString m_Capacity;
	CString m_MYLen;
	CString m_ATLYear;

	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedModButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnNMDblclkSgmList(NMHDR *pNMHDR, LRESULT *pResult);
};
