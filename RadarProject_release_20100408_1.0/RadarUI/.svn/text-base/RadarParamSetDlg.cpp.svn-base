// RadarParamSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarParamSetDlg.h"
#include "RadarSetPwdDlg.h"
#include "RadarSetRadarDlg.h"
#include "RadarSetAlgDlg.h"
#include "RadarSetSysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarParamSetDlg dialog


CRadarParamSetDlg::CRadarParamSetDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarParamSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarParamSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//ÔØÈëÍ¼Æ¬×ÊÔ´
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_PARAM_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
}
CRadarParamSetDlg::~CRadarParamSetDlg()
{
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}

void CRadarParamSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarParamSetDlg)
	DDX_Control(pDX, IDC_BUTTON_SYS, m_sysBtn);
	DDX_Control(pDX, IDC_BUTTON_RETURN, m_returnBtn);
	DDX_Control(pDX, IDC_BUTTON_RADAR, m_radarBtn);
	DDX_Control(pDX, IDC_BUTTON_PWD, m_pwdBtn);
	DDX_Control(pDX, IDC_BUTTON_ALG, m_algBtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarParamSetDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarParamSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
	ON_BN_CLICKED(IDC_BUTTON_PWD, OnButtonPwd)
	ON_BN_CLICKED(IDC_BUTTON_RADAR, OnButtonRadar)
	ON_BN_CLICKED(IDC_BUTTON_SYS, OnButtonSys)
	ON_BN_CLICKED(IDC_BUTTON_ALG, OnButtonAlg)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarParamSetDlg message handlers
BOOL CRadarParamSetDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pwdBtn.MoveWindow(123,81,103,39);
	m_sysBtn.MoveWindow(237,81,103,39);
	m_radarBtn.MoveWindow(123,121,103,39);
	m_algBtn.MoveWindow(237,121,103,39);

	m_returnBtn.MoveWindow(178,167,103,39);

	m_pwdBtn.LoadBmp(UI_PARAM_PWDSETN,UI_PARAM_PWDSETH,UI_PARAM_PWDSETD);
	m_sysBtn.LoadBmp(UI_PARAM_SYSSETN,UI_PARAM_SYSSETH,UI_PARAM_SYSSETD);
	m_radarBtn.LoadBmp(UI_PARAM_RADARSETN,UI_PARAM_RADARSETH,UI_PARAM_RADARSETD);
	m_algBtn.LoadBmp(UI_PARAM_ALGSETN,UI_PARAM_ALGSETH,UI_PARAM_ALGSETD);
	m_returnBtn.LoadBmp(UI_COMMON_RETURNN,UI_COMMON_RETURNH,UI_COMMON_RETURND);
	return TRUE;
}
void CRadarParamSetDlg::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);	
}

void CRadarParamSetDlg::OnButtonPwd() 
{
	// TODO: Add your control notification handler code here
	CRadarSetPwdDlg dlg;
	dlg.DoModal();
	//MessageBox("dd");
}

void CRadarParamSetDlg::OnButtonRadar() 
{
	// TODO: Add your control notification handler code here
	CRadarSetRadarDlg dlg;
	dlg.DoModal();
}

void CRadarParamSetDlg::OnButtonSys() 
{
	// TODO: Add your control notification handler code here
	CRadarSetSysDlg dlg;
	dlg.DoModal();
}

void CRadarParamSetDlg::OnButtonAlg() 
{
	// TODO: Add your control notification handler code here
	CRadarSetAlgDlg dlg;
	dlg.DoModal();
}

BOOL CRadarParamSetDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
}
