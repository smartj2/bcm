#pragma once


// CRelieveBinding 对话框

class CRelieveBinding : public CDialogEx
{
	DECLARE_DYNAMIC(CRelieveBinding)

public:
	CRelieveBinding(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRelieveBinding();

// 对话框数据
	enum { IDD = IDD_RELIEVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
