#pragma once


// CLogin 对话框

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	_RecordsetPtr m_pRs;  // 查询结果集
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
	enum { IDD = IDD_LOGIN_DIALOG };

	CString m_UserName;  // 用户名
	CString m_PassWord;  // 密码
	CButton m_Login;     // 登录按钮
	CButton m_Cancel;    // 取消按钮

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
};
