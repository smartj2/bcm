#pragma once


// CCartonQuery 对话框

class CCartonQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CCartonQuery)

public:
	CCartonQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCartonQuery();

// 对话框数据
	enum { IDD = IDD_QUERY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
