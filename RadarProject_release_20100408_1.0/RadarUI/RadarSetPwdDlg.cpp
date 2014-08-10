// RadarSetPwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarSetPwdDlg.h"
#include "RadarEnumMap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarSetPwdDlg dialog


CRadarSetPwdDlg::CRadarSetPwdDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarSetPwdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarSetPwdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//载入图片资源
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_PWD_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
}
CRadarSetPwdDlg::~CRadarSetPwdDlg()
{
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}

void CRadarSetPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarSetPwdDlg)
	DDX_Control(pDX, IDC_BUTTON_RETURN, m_returnBtn);
	DDX_Control(pDX, IDC_BUTTON_OK, m_okBtn);
	DDX_Control(pDX, IDC_EDIT_OLDPWD, m_oldPwd);
	DDX_Control(pDX, IDC_EDIT_NEWPWD1, m_newPwd1);
	DDX_Control(pDX, IDC_EDIT_NEWPWD, m_newPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarSetPwdDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarSetPwdDlg)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarSetPwdDlg message handlers
BOOL CRadarSetPwdDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();
	app=CRADAR_APP;
	if(app==NULL)
	{
		MessageBox("app未初始化！");
		exit(0);
	}

	m_oldPwd.MoveWindow(148,89,211,31);
	m_newPwd.MoveWindow(148,126,211,31);
	m_newPwd1.MoveWindow(148,164,211,31);

	m_okBtn.MoveWindow(111,216,103,39);
	m_returnBtn.MoveWindow(226,216,103,39);

	m_okBtn.LoadBmp(UI_COMMON_CONFIRMN,UI_COMMON_CONFIRMH,UI_COMMON_CONFIRMD);
	m_returnBtn.LoadBmp(UI_COMMON_RETURNN,UI_COMMON_RETURNH,UI_COMMON_RETURND);
	return TRUE;
}
void CRadarSetPwdDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	char pwd[50];
	CString s;
	m_oldPwd.GetWindowText(s);
	memcpy(pwd,s,50);
	int ret=app->CheckPwd(pwd,50); 
	if(ret==META_ERR_PWD)
	{
		MessageBox("旧密码错误！");
		return;
	}
	m_newPwd.GetWindowText(s);
	CString s1;
	m_newPwd1.GetWindowText(s1);
	if(strcmp(s,s1)!=0)
	{
		MessageBox("两次输入密码不一致！");
		return;
	}

	memcpy(pwd,s,50);
	ret=app->ChangePwd(pwd,50);
	if(ret==META_ERR_SUCCESS)
	{
		MessageBox("修改成功！");
		EndDialog(0);
	}
	else
	{
		MessageBox("修改失败！错误信息："+CRadarEnumMap::m_appErrorArray[-ret]);
	}
	
}

void CRadarSetPwdDlg::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

BOOL CRadarSetPwdDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
}
