#pragma once


// CSGMLine 对话框

class CSGMLine : public CDialogEx
{
	DECLARE_DYNAMIC(CSGMLine)

public:
	CSGMLine(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSGMLine();

// 对话框数据
	enum { IDD = IDD_SGMSETTINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
