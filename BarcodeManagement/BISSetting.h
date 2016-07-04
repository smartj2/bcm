#pragma once


// CBISSetting 对话框

class CBISSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CBISSetting)

public:
	CBISSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBISSetting();

// 对话框数据
	enum { IDD = IDD_BISSETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
