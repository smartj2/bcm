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
	CListCtrl m_SGMList;
	CString m_SGMQA;
	CString m_SGMLine;
	CString m_SGMTray;
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedCancelButton();
	virtual BOOL OnInitDialog();
};
