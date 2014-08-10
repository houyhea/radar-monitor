// RadarSetRadarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarSetRadarDlg.h"
#include "RadarEnumMap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarSetRadarDlg dialog


CRadarSetRadarDlg::CRadarSetRadarDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarSetRadarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarSetRadarDlg)
	//}}AFX_DATA_INIT
	//载入图片资源
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_RADAR_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
}

CRadarSetRadarDlg::~CRadarSetRadarDlg()
{
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}

void CRadarSetRadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarSetRadarDlg)
	DDX_Control(pDX, IDC_BUTTON_RADIO_SAVEFILE, m_radio_saveData);
	DDX_Control(pDX, IDC_BUTTON_RETURN, m_returnBtn);
	DDX_Control(pDX, IDC_BUTTON_OK, m_okBtn);
	DDX_Control(pDX, IDC_EDIT_VALIDDISTANCE, m_validDistance);
	DDX_Control(pDX, IDC_EDIT_FILE, m_rawDataFile);
	DDX_Control(pDX, IDC_BUTTON_FILE, m_fileBtn);
	DDX_Control(pDX, IDC_EDIT_MOTORRATE, m_motorRate);
	DDX_Control(pDX, IDC_EDIT_STOPANGLE, m_stopAngle);
	DDX_Control(pDX, IDC_EDIT_STARTANGLE, m_startAngle);
	DDX_Control(pDX, IDC_EDIT_IPPORT, m_ipPort);
	DDX_Control(pDX, IDC_EDIT_IPADDR, m_ipAddr);
	DDX_Control(pDX, IDC_EDIT_COMPORT, m_comPort);
	DDX_Control(pDX, IDC_EDIT_BITRATE, m_bitRate);
	DDX_Control(pDX, IDC_COMBO_RADAR, m_radarList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarSetRadarDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarSetRadarDlg)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_CBN_SELCHANGE(IDC_COMBO_RADAR, OnSelchangeComboRadar)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_RADIO_SAVEFILE, OnButtonRadioSavefile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarSetRadarDlg message handlers
BOOL CRadarSetRadarDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();
	app=CRADAR_APP;
	if(app==NULL)
	{
		MessageBox("app未初始化！");
		exit(0);
	}
	
	m_okBtn.MoveWindow(164,579,103,39);
	m_returnBtn.MoveWindow(274,579,103,39);

	m_radarList.MoveWindow(193,95,230,100);
	m_bitRate.MoveWindow(193,167,230,26);
	m_comPort.MoveWindow(193,202,230,26);
	m_startAngle.MoveWindow(193,238,230,26);
	m_stopAngle.MoveWindow(193,273,230,26);
	m_ipAddr.MoveWindow(193,307,230,26);
	m_ipPort.MoveWindow(193,343,230,26);
	m_motorRate.MoveWindow(193,379,230,26);
	m_validDistance.MoveWindow(193,412,230,26);

	m_radio_saveData.MoveWindow(193,495,103,39);
	m_rawDataFile.MoveWindow(193,535,230,26);

	m_fileBtn.MoveWindow(433,535,50,26);

	m_okBtn.LoadBmp(UI_COMMON_CONFIRMN,UI_COMMON_CONFIRMH,UI_COMMON_CONFIRMD);
	m_returnBtn.LoadBmp(UI_COMMON_RETURNN,UI_COMMON_RETURNH,UI_COMMON_RETURND);
	m_radio_saveData.LoadBmp(UI_COMMON_RADIO_CHECKED,UI_COMMON_RADIO_UNCHECKED,UI_COMMON_RADIO_UNCHECKED);

	m_radarList.InsertString(0,"日本SCIP雷达");
	m_radarList.InsertString(1,"德国劳易测雷达-SOCKET");
	m_radarList.InsertString(2,"德国劳易测雷达-串口");
	m_radarList.InsertString(3,"WSN第一代激光雷达");
	
	HardConfigInfo c;
	app->GetRadarConfig(&c);
	switch(c.radar)
	{
	case SCIP:
		m_radarList.SetCurSel(0);
		break;
	case LeuzeSocket:
		m_radarList.SetCurSel(1);
		break;
	case LeuzeCom:
		m_radarList.SetCurSel(2);
		break;
	case CustomTcpRadar:
		m_radarList.SetCurSel(3);
		break;
	default:
		m_radarList.SetCurSel(0);
		break;

	}
	OnSelchangeComboRadar();

	CString str;
	str.Format("%d",c.BitRate);
	m_bitRate.SetWindowText(str);

	str.Format("%d",c.port);
	m_ipPort.SetWindowText(str);

	long angle=(long)(c.startAngle*0.2);
	str.Format("%d",angle);
	m_startAngle.SetWindowText(str);

	angle=(long)(c.stopAngle*0.2);
	str.Format("%d",angle);
	m_stopAngle.SetWindowText(str);

	str.Format("%s",c.comDevice);
	m_comPort.SetWindowText(str);

	str.Format("%s",c.ip);
	m_ipAddr.SetWindowText(str);

	str.Format("%d",c.motorRate);
	m_motorRate.SetWindowText(str);

	m_radio_saveData.SetState(c.saveRawData);
	
	str.Format("%s",c.rawDataFile);
	m_rawDataFile.SetWindowText(str);

	str.Format("%d",c.validDistance);
	m_validDistance.SetWindowText(str);


	return TRUE;
}

void CRadarSetRadarDlg::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

void CRadarSetRadarDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	HardConfigInfo c;
	CString str;

	EnumRadar index=SCIP;
	index=(EnumRadar)m_radarList.GetCurSel();
	

	c.radar=index;
	try
	{
		char * temp;
		m_bitRate.GetWindowText(str);
		c.BitRate=atoi(str);
		
		m_motorRate.GetWindowText(str);
		c.motorRate=atoi(str);
		
		m_startAngle.GetWindowText(str);
		c.startAngle=atol(str)*5; //转化为0.2度单位
		
		m_stopAngle.GetWindowText(str);
		c.stopAngle=atol(str)*5;
		
		m_comPort.GetWindowText(str);
		temp=str.GetBuffer(str.GetLength());
		memcpy(c.comDevice,temp,50);
		
		
		m_ipAddr.GetWindowText(str);
		temp=str.GetBuffer(str.GetLength());
		memcpy(c.ip,temp,50);
		
		m_ipPort.GetWindowText(str);
		c.port=atoi(str);	
		
		
		c.saveRawData=(m_radio_saveData.m_bOn);
		
		m_rawDataFile.GetWindowText(str);
		temp=str.GetBuffer(str.GetLength());
		memcpy(c.rawDataFile,temp,500);
		
		m_validDistance.GetWindowText(str);
		c.validDistance=atoi(str);
	}
	catch(...)//三个点表示捕获所有类型的异常
	{
		MessageBox("数据格式不正确");
		return;
	}
	//同时保存算法部分的雷达类型
	AlgorithmConfigInfo algc;	
	app->GetAlgConfig(&algc);
	algc.radarType=(int)m_radarList.GetCurSel();
	app->SetAlgConfig(&algc);

	int ret=app->SetRadarConfig(&c);
	if(ret==META_ERR_SUCCESS)
	{
		MessageBox("设置成功！");
		EndDialog(0);
	}
	else
	{
		MessageBox("设置失败！错误信息："+CRadarEnumMap::m_appErrorArray[-ret]);
	}
}


//下拉列表选择事件			
void CRadarSetRadarDlg::OnSelchangeComboRadar() 
{
	// TODO: Add your control notification handler code here
	EnumRadar index=SCIP;
	index=(EnumRadar)m_radarList.GetCurSel();

	switch(index)
	{
	case SCIP:
		m_bitRate.SetReadOnly(FALSE);
		m_comPort.SetReadOnly(FALSE);
		m_startAngle.SetReadOnly(FALSE);
		m_stopAngle.SetReadOnly(FALSE);
		m_ipAddr.SetReadOnly(TRUE);
		m_ipPort.SetReadOnly(TRUE);
		m_motorRate.SetReadOnly(TRUE);
		m_validDistance.SetReadOnly(FALSE);
		break;
	case LeuzeSocket:
		m_bitRate.SetReadOnly(TRUE);
		m_comPort.SetReadOnly(TRUE);
		m_startAngle.SetReadOnly(FALSE);
		m_stopAngle.SetReadOnly(FALSE);
		m_ipAddr.SetReadOnly(FALSE);
		m_ipPort.SetReadOnly(FALSE);
		m_motorRate.SetReadOnly(TRUE);
		m_validDistance.SetReadOnly(TRUE);
		break;
	case LeuzeCom:
		m_bitRate.SetReadOnly(FALSE);
		m_comPort.SetReadOnly(FALSE);
		m_startAngle.SetReadOnly(FALSE);
		m_stopAngle.SetReadOnly(FALSE);
		m_ipAddr.SetReadOnly(TRUE);
		m_ipPort.SetReadOnly(TRUE);
		m_motorRate.SetReadOnly(TRUE);
		m_validDistance.SetReadOnly(TRUE);
		break;
	case CustomTcpRadar:
		m_bitRate.SetReadOnly(TRUE);
		m_comPort.SetReadOnly(TRUE);
		m_startAngle.SetReadOnly(FALSE);
		m_stopAngle.SetReadOnly(FALSE);
		m_ipAddr.SetReadOnly(FALSE);
		m_ipPort.SetReadOnly(FALSE);
		m_motorRate.SetReadOnly(TRUE);
		m_validDistance.SetReadOnly(FALSE);
		break;
	default:
		m_bitRate.SetReadOnly(FALSE);
		m_comPort.SetReadOnly(FALSE);
		m_startAngle.SetReadOnly(FALSE);
		m_stopAngle.SetReadOnly(FALSE);
		m_ipAddr.SetReadOnly(TRUE);
		m_ipPort.SetReadOnly(TRUE);
		m_motorRate.SetReadOnly(TRUE);
		m_validDistance.SetReadOnly(TRUE);
		break;
	}	
}

void CRadarSetRadarDlg::OnButtonFile() 
{
	// TODO: Add your control notification handler code here
	char buff[500];
	GetCurrentDirectory(500,buff);//打开文件对话框之前，保存当前的工作目录

	CFileDialog   DlgOpenFile(   TRUE,   ".txt",   "rawData",     
		OFN_EXPLORER,
		"Text Files(*.txt)|*.txt||",     
		this);   
	int   iResult   =   DlgOpenFile.DoModal();   
	
	if(   iResult   !=   IDOK   )   
	{   
		return;   
	}   
    SetCurrentDirectory(buff);//文件对话框改变了当前工作目录，所以这里需要重新设置回来。

	CString fName=DlgOpenFile.GetPathName();	//获取包括路径的文件名
	m_rawDataFile.SetWindowText(fName);
}

BOOL CRadarSetRadarDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
}

void CRadarSetRadarDlg::OnButtonRadioSavefile() 
{
	// TODO: Add your control notification handler code here

	m_radio_saveData.SetState(!m_radio_saveData.m_bOn);

}
