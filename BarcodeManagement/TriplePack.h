#pragma once


// CTriplePack 对话框

class CTriplePack : public CDialogEx
{
	DECLARE_DYNAMIC(CTriplePack)

public:
	CTriplePack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTriplePack();

// 对话框数据
	enum { IDD = IDD_TRIPLEPACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
