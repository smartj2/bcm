#pragma once


// CSeriesBattery 对话框

class CSeriesBattery : public CDialogEx
{
	DECLARE_DYNAMIC(CSeriesBattery)

public:
	CSeriesBattery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSeriesBattery();

// 对话框数据
	enum { IDD = IDD_SERIES_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
