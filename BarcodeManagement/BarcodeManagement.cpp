
// BarcodeManagement.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "BarcodeManagementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBarcodeManagementApp

BEGIN_MESSAGE_MAP(CBarcodeManagementApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBarcodeManagementApp ����

CBarcodeManagementApp::CBarcodeManagementApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBarcodeManagementApp ����

CBarcodeManagementApp theApp;


// CBarcodeManagementApp ��ʼ��

BOOL CBarcodeManagementApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��

	::CoInitialize(NULL);
	try
	{
		m_pCon.CreateInstance(__uuidof(Connection));
		//m_pCon.CreateInstance("ADODB.Recordset");
	   //_bstr_t strConnect="Provider=SQLOLEDB.1;Persist Security Info=False;User ID=bcm;Initial Catalog=bcm;Data Source=SRV03";
	   _bstr_t strConnect="Provider=SQLOLEDB.1;Persist Security Info=False;User ID=bcm;Initial Catalog=bcm;Data Source=shenshaowei";
	   //_bstr_t strConnect="Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initial Catalog=bcm;Data Source=DEVELOPER";
	   m_pCon->Open(strConnect,"bcm","bcmadmin",adModeUnknown);
		//m_pCon->Open(strConnect,"sa","passw0rd",adModeUnknown);
		/*HRESULT hr = m_pCon.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			m_pCon->ConnectionTimeout = 3;
			hr = m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=../data/bcm.mdb","","",adModeUnknown);
			//::MessageBox(NULL, _T(""), _T("���ӳɹ�"), NULL);
		}*/
	}
	catch(_com_error e)
	{
		CString temp;
		temp.Format("�������ݿ������Ϣ��%s", e.Description());
		AfxMessageBox(temp);
	}

	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CBarcodeManagementDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

