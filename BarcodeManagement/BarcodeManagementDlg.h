
// BarcodeManagementDlg.h : ͷ�ļ�
//

#pragma once


// CBarcodeManagementDlg �Ի���
class CBarcodeManagementDlg : public CDialogEx
{
// ����
public:
	CMenu m_pMenu;
	CBarcodeManagementDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BARCODEMANAGEMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBISSetting();
	afx_msg void OnSGMSetting();
	afx_msg void OnCartonPacking();
	afx_msg void OnCartonQuery();
	afx_msg void OnAboutbox();
	afx_msg void OnSingleMenu();
};
