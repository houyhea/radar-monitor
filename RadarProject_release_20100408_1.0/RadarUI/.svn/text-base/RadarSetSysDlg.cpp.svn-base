// RadarSetSysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarSetSysDlg.h"
#include "RadarEnumMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarSetSysDlg dialog


CRadarSetSysDlg::CRadarSetSysDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarSetSysDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarSetSysDlg)
	//}}AFX_DATA_INIT
	//载入图片资源
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_SYSTEM_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
}
CRadarSetSysDlg::~CRadarSetSysDlg()
{
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}

void CRadarSetSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CRadarBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarSetSysDlg)
	DDX_Control(pDX, IDC_BUTTON_RADIO_SOUND, m_radio_sound);
	DDX_Control(pDX, IDC_BUTTON_RADIO_ALARM, m_radio_alarm);
	DDX_Control(pDX, IDC_BUTTON_RETURN, m_returnBtn);
	DDX_Control(pDX, IDC_BUTTON_OK, m_okBtn);
	DDX_Control(pDX, IDC_EDIT_ALARMRECORDCNT, m_alarmRecordCnt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarSetSysDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarSetSysDlg)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_RADIO_ALARM, OnButtonRadioAlarm)
	ON_BN_CLICKED(IDC_BUTTON_RADIO_SOUND, OnButtonRadioSound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarSetSysDlg message handlers
BOOL CRadarSetSysDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();
	app=CRADAR_APP;
	if(app==NULL)
	{
		MessageBox("app未初始化！");
		exit(0);
	}
	m_okBtn.MoveWindow(121,203,103,39);
	m_returnBtn.MoveWindow(236,203,103,39);
	m_alarmRecordCnt.MoveWindow(155,167,200,30);

	m_radio_alarm.MoveWindow(155,84,103,39);
	m_radio_sound.MoveWindow(155,126,103,39);

	m_okBtn.LoadBmp(UI_COMMON_CONFIRMN,UI_COMMON_CONFIRMH,UI_COMMON_CONFIRMD);
	m_returnBtn.LoadBmp(UI_COMMON_RETURNN,UI_COMMON_RETURNH,UI_COMMON_RETURND);
	
	m_radio_alarm.LoadBmp(UI_COMMON_RADIO_CHECKED,UI_COMMON_RADIO_UNCHECKED,UI_COMMON_RADIO_UNCHECKED);
	m_radio_sound.LoadBmp(UI_COMMON_RADIO_CHECKED,UI_COMMON_RADIO_UNCHECKED,UI_COMMON_RADIO_UNCHECKED);

	m_radio_alarm.SetState(app->GetAnswerAlarm());
	m_radio_sound.SetState(app->GetSoundAlarm());

	int cnt=app->GetAlarmShwoCnt();
	CString str;
	str.Format("%d",cnt);
	m_alarmRecordCnt.SetWindowText(str);

	return TRUE;
}

void CRadarSetSysDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	int cnt=100;
	try
	{
		CString str;
		m_alarmRecordCnt.GetWindowText(str);
		cnt=atoi(str);
	}
	catch(...)//三个点表示捕获所有类型的异常
	{
		MessageBox("数据格式不正确");	
	}

	int ret=app->SetAnswerAlarm(m_radio_alarm.m_bOn);	
	ret=app->SetSoundAlarm(m_radio_sound.m_bOn);
	ret=app->SetAlarmShwoCnt(cnt);
	if(ret==META_ERR_SUCCESS)
	{
		GetParent()->GetParent()->SendMessage(WM_SYSPARAM_CHANGE, 0, 0);
		MessageBox("设置成功！");	
		EndDialog(0);
	}
	else
	{
		MessageBox("设置失败！错误信息："+CRadarEnumMap::m_appErrorArray[-ret]);	
	}
	
}

void CRadarSetSysDlg::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

BOOL CRadarSetSysDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
}

void CRadarSetSysDlg::OnButtonRadioAlarm() 
{
	// TODO: Add your control notification handler code here
	m_radio_alarm.SetState(!m_radio_alarm.m_bOn);
}

void CRadarSetSysDlg::OnButtonRadioSound() 
{
	// TODO: Add your control notification handler code here
	m_radio_sound.SetState(!m_radio_sound.m_bOn);
}
