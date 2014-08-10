// RadarSetAlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarSetAlgDlg.h"
#include "RadarEnumMap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarSetAlgDlg dialog


CRadarSetAlgDlg::CRadarSetAlgDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarSetAlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarSetAlgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//载入图片资源
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_ALG_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
}
CRadarSetAlgDlg::~CRadarSetAlgDlg()
{
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}


void CRadarSetAlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CRadarBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarSetAlgDlg)
	DDX_Control(pDX, IDC_BUTTON_RETURN, m_returnBtn);
	DDX_Control(pDX, IDC_BUTTON_OK, m_okBtn);
	DDX_Control(pDX, IDC_EDIT_WIDTH_THRESHOLD, m_widthThreshold);
	DDX_Control(pDX, IDC_EDIT_SAMEOBLENGTH, m_sameObLength);
	DDX_Control(pDX, IDC_EDIT_FUSHION_TIME, m_fushionTime);
	DDX_Control(pDX, IDC_EDIT_FUSHION_STEP_NUM, m_fushionStepNum);
	DDX_Control(pDX, IDC_EDIT_BULD_MAP_PRD, m_buldMapPrd);
	DDX_Control(pDX, IDC_EDIT_BKGRDOFFSET, m_bkgrdOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarSetAlgDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarSetAlgDlg)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarSetAlgDlg message handlers
BOOL CRadarSetAlgDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();
	
	// TODO: Add extra initialization here

	app=CRADAR_APP;
	if(app==NULL)
	{
		MessageBox("app未初始化！");
		exit(0);
	}
	//初始化控件位置
	m_bkgrdOffset.MoveWindow(222,83,212,27);
	m_sameObLength.MoveWindow(222,120,212,27);
	m_widthThreshold.MoveWindow(222,155,212,27);
	m_fushionStepNum.MoveWindow(222,191,212,27);
	m_fushionTime.MoveWindow(222,228,212,27);
	m_buldMapPrd.MoveWindow(222,264,212,27);


	m_okBtn.MoveWindow(171,311,103,39);
	m_returnBtn.MoveWindow(286,311,103,39);
	m_okBtn.LoadBmp(UI_COMMON_CONFIRMN,UI_COMMON_CONFIRMH,UI_COMMON_CONFIRMD);
	m_returnBtn.LoadBmp(UI_COMMON_RETURNN,UI_COMMON_RETURNH,UI_COMMON_RETURND);



	AlgorithmConfigInfo c;
	
	app->GetAlgConfig(&c);
	
	CString str;
	
	str.Format("%d",c.bkgrdOffset);
	m_bkgrdOffset.SetWindowText(str);

	str.Format("%d",c.bldmapPeriod);
	m_buldMapPrd.SetWindowText(str);

	str.Format("%d",c.chkWidthThreshold);
	m_widthThreshold.SetWindowText(str);

	str.Format("%d",c.fushionStepNum);
	m_fushionStepNum.SetWindowText(str);

	str.Format("%d",c.fushionTime);
	m_fushionTime.SetWindowText(str);

	str.Format("%d",c.sameobLength);
	m_sameObLength.SetWindowText(str);



	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CRadarSetAlgDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	AlgorithmConfigInfo cfg;
	CString str;
	try
	{
		m_bkgrdOffset.GetWindowText(str);
		cfg.bkgrdOffset=atoi(str);
		
		m_buldMapPrd.GetWindowText(str);
		cfg.bldmapPeriod=atoi(str);
		
		m_widthThreshold.GetWindowText(str);
		cfg.chkWidthThreshold=atoi(str);
		
		m_fushionStepNum.GetWindowText(str);
		cfg.fushionStepNum=atoi(str);
		
		m_fushionTime.GetWindowText(str);
		cfg.fushionTime=atoi(str);
		
		m_sameObLength.GetWindowText(str);
		cfg.sameobLength=atoi(str);

		HardConfigInfo c;
		app->GetRadarConfig(&c);
		cfg.radarType=(int)c.radar;

	}
	catch(...)//三个点表示捕获所有类型的异常
	{
		MessageBox("数据格式不正确");
		return;
	}
	int ret=app->SetAlgConfig(&cfg);
	if(ret==META_ERR_SUCCESS)
	{
		MessageBox("设置成功");
		EndDialog(0);
	}
	else
	{
		CString err;
		CRadarEnumMap::m_appErrorArray[-ret];
		err.Format("设置失败，错误信息：%s",CRadarEnumMap::m_appErrorArray[-ret]);
		MessageBox(err);
		return;
	}


	
	//cfg.bkgrdOffset
}

void CRadarSetAlgDlg::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

BOOL CRadarSetAlgDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
}
