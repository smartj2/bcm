#pragma once


// CSeriesBattery �Ի���

class CSeriesBattery : public CDialogEx
{
	DECLARE_DYNAMIC(CSeriesBattery)

public:
	CSeriesBattery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSeriesBattery();

// �Ի�������
	enum { IDD = IDD_SERIES_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
