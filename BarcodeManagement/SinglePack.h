#pragma once


// CSinglePack 对话框

class CSinglePack : public CDialogEx
{
	DECLARE_DYNAMIC(CSinglePack)

public:
	CSinglePack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSinglePack();

// 对话框数据
	enum { IDD = IDD_SINGLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
