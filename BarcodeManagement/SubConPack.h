#pragma once


// CSubConPack 对话框

class CSubConPack : public CDialogEx
{
	DECLARE_DYNAMIC(CSubConPack)

public:
	CSubConPack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSubConPack();

// 对话框数据
	enum { IDD = IDD_PACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
