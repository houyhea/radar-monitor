// RadarHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarHistoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CRadarHistoryDlg dialog


CRadarHistoryDlg::CRadarHistoryDlg(CWnd* pParent /*=NULL*/)
: CRadarBaseDlg(CRadarHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarHistoryDlg)
	//}}AFX_DATA_INIT
	::CoInitialize(NULL); //初始化COM
	//载入图片资源
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_HISTORY_BG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
}
CRadarHistoryDlg::~CRadarHistoryDlg()
{
	CoUninitialize();
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);
}

void CRadarHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CRadarBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarHistoryDlg)
	DDX_Control(pDX, IDC_BUTTON_RETURN, m_returnBtn);
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_refreshBtn);
	DDX_Control(pDX, IDC_TREE_TIME, m_treeTime);
	DDX_Control(pDX, IDC_STATIC_MAP, m_mapCtrl);
	DDX_Control(pDX, IDC_LIST_RECORD, m_listAlarmRecord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarHistoryDlg, CRadarBaseDlg)
//{{AFX_MSG_MAP(CRadarHistoryDlg)
ON_BN_CLICKED(IDC_BUTTON_RETURN, OnButtonReturn)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_TIME, OnSelchangedTreeTime)
ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarHistoryDlg message handlers
BOOL CRadarHistoryDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();
	app=CRADAR_APP;
	if(app==NULL)
	{
		MessageBox("app未初始化！");
		exit(0);
	}
	InitMapCtrl();
	
	m_returnBtn.MoveWindow(79,102,98,32);
	m_returnBtn.LoadBmp(UI_HISTORY_RETURNN,UI_HISTORY_RETURNH,UI_HISTORY_RETURND);

	m_refreshBtn.MoveWindow(207,102,118,32);
	m_refreshBtn.LoadBmp(UI_HISTORY_REFRESHN,UI_HISTORY_REFRESHH,UI_HISTORY_REFRESHD);

	m_treeTime.MoveWindow(22,181,356,112);
	m_listAlarmRecord.MoveWindow(22,331,356,283);
	//报警记录
	m_listAlarmRecord.InsertColumn(0,"时间",LVCFMT_CENTER,100);
    m_listAlarmRecord.InsertColumn(1,"目标",LVCFMT_CENTER,60);
	m_listAlarmRecord.InsertColumn(2,"角度(度)",LVCFMT_CENTER,60);
	m_listAlarmRecord.InsertColumn(3,"距离(m)",LVCFMT_CENTER,60);
	m_listAlarmRecord.InsertColumn(4,"宽度(m)",LVCFMT_CENTER,60);
	
	BrowseFile(0,DIR_HISTORY);//遍历历史数据目录
	m_treeTime.Expand(m_treeTime.GetParentItem(strHtEnd),TVE_EXPAND);//展开最后一个目录

	m_treeTime.SetFocus();			  
	return FALSE;
}
void CRadarHistoryDlg::InitMapCtrl()
{
	m_mapCtrl.InitData(MAP_ZOOMIN
		,MAP_ZOOMIND
		,MAP_ZOOMOUT
		,MAP_ZOOMOUTD
		,MAP_BG
		,MAP_STATEING
		,MAP_STATED
		,MAP_STATESTART
		,MAP_STATE_PLAYBACK);
	
	CRect rzoomin;
	int height;
	height=590;
	rzoomin.left=height-48-10;
	rzoomin.right=rzoomin.left+24;
	rzoomin.top=10;
	rzoomin.bottom=34;
	
	CRect rzoomout(rzoomin);
	rzoomout.left+=24;
	rzoomout.right+=24;
	
	CRect rstate;
	rstate.left=10;
	rstate.right=rstate.left+96;
	rstate.top=height-24-10;
	rstate.bottom=rstate.top+24;
	m_mapCtrl.MoveWindow(420,30,10,10);
	
	m_mapCtrl.InitSizes(height,height,rzoomin,rzoomout,rstate);
	m_mapCtrl.m_state=RDPlayBack;

}

void CRadarHistoryDlg::OnButtonReturn() 
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

void CRadarHistoryDlg::OnSelchangedTreeTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//不管有没有数据，先清掉地图和报警信息
	m_mapCtrl.m_map_warningResult.objNum=0;
	m_mapCtrl.m_map_bkgrdMap.bReady=false;
	m_mapCtrl.Invalidate(TRUE);
	m_mapCtrl.ClearWarningObjectsForPlayBack();

	m_listAlarmRecord.DeleteAllItems();
	
	HTREEITEM   hCurItem   =   m_treeTime.GetSelectedItem();   
	CString   str   =   m_treeTime.GetItemText(hCurItem); //获取选中节点的文本
	
	HTREEITEM hParentItem=m_treeTime.GetParentItem(hCurItem);
	CString strParent=m_treeTime.GetItemText(hParentItem);


	//需要先判断选中节点的XML文件是否存在，不存在则什么都不做
	CString selectFileName;
	selectFileName.Format("%s\\%s\\%s.xml",DIR_HISTORY,strParent,str);
	if(m_fileOp.FileExist(selectFileName))
	{	

		BkgrdMap map;
		bool b=GetMap(selectFileName,&map);		
		if(b)
		{
			//画报警节点
			b=GetWarningResult(selectFileName);
			m_mapCtrl.m_map_bkgrdMap=map;
			m_mapCtrl.Invalidate(TRUE);	

		}

	}
	*pResult = 0;
}
bool CRadarHistoryDlg::GetWarningResult(CString xmlFile)
{

	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("初始化出错!");
		return false;
	}
	char * pChar=xmlFile.GetBuffer(xmlFile.GetLength());
	pDoc->load(pChar);//载入数据
	
	MSXML2::IXMLDOMElementPtr node;
	node = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//warningData"));
	if(node==NULL)
		return false;	
	MSXML2::IXMLDOMNodeListPtr nodeList,childNodeList;
	node->get_childNodes(&nodeList);
	long dataCnt;
	nodeList->get_length(&dataCnt); //获取子节点个数  warningResult 
	IXMLDOMNode * dataNode = NULL;
	for(int i=0;i<dataCnt;i++)
	{
		
		CString time;
		int objNum;
		long cnt;
		CString str;
		nodeList->get_item(i,&dataNode);
		time=GetNodeAttributeValue("time",dataNode);
		objNum=atoi(GetNodeAttributeValue("objNum",dataNode));
		time=time.Right(8);
		
		//遍历当前报警结构体的报警节点
		dataNode->get_childNodes(&childNodeList);
		childNodeList->get_length(&cnt); 
		
		for(int j=0;j<cnt;j++)
		{
			IXMLDOMNode * objNode = NULL;
			childNodeList->get_item(j,&objNode);

			//插入报警节点到地图控件
			WaringObject obj;
			CString w_value;
			obj.angle=atoi(GetNodeAttributeValue("angle",objNode));
			obj.distance=atoi(GetNodeAttributeValue("distance",objNode));
			obj.objWidth=atoi(GetNodeAttributeValue("objWidth",objNode));
			m_mapCtrl.m_map_warningObjects.push_back(obj);

			//插入报警节点到报警列表

			int itemCnt=m_listAlarmRecord.GetItemCount();
			int nRow = m_listAlarmRecord.InsertItem(itemCnt, time);//插入行,时间
			
			w_value.Format("目标%d",j);
			m_listAlarmRecord.SetItemText(nRow, 1, w_value);

			w_value.Format("%0.2f",obj.angle*0.2);
			m_listAlarmRecord.SetItemText(nRow, 2, w_value);

			double v=0;
			v=(double)obj.distance/1000;
			
			w_value.Format("%0.2f",v);
			m_listAlarmRecord.SetItemText(nRow, 3, w_value);
			
			v=(double)obj.objWidth/1000;
			w_value.Format("%0.2f",v);
			m_listAlarmRecord.SetItemText(nRow, 4, w_value);
			
			m_listAlarmRecord.EnsureVisible(nRow, FALSE);

			
		}

		//插入隔行
		int itemCnt=m_listAlarmRecord.GetItemCount();
		int nR = m_listAlarmRecord.InsertItem(itemCnt, "-");//插入行
		m_listAlarmRecord.SetItemText(nR, 1, "-");
		m_listAlarmRecord.SetItemText(nR, 2, "-");
		m_listAlarmRecord.SetItemText(nR, 3, "-");
		m_listAlarmRecord.SetItemText(nR, 4, "-");
	}
	return true;
	
}
//根据节点获取地图
bool  CRadarHistoryDlg::GetMap(CString xmlFile,BkgrdMap* map)
{

	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("初始化出错!");
		return false;
	}
	char * pChar=xmlFile.GetBuffer(xmlFile.GetLength());
	pDoc->load(pChar);//载入数据
	
	MSXML2::IXMLDOMElementPtr node;
	node = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//map"));
	if(node==NULL)
		return false;

	CString str;
	str=GetNodeAttributeValue("bReady",node);
	map->bReady=(str=="TRUE");

	str=GetNodeAttributeValue("dataLength",node);
	map->mapDataLength=atoi(str);

	str=GetNodeAttributeValue("time",node);
	map->time=GetTime(str);

	str=GetNodeAttributeValue("startAngle",node);
	map->startAngle=atoi(str);

	str=GetNodeAttributeValue("stopAngle",node);
	map->stopAngle=atoi(str);

	long dataCnt;
	MSXML2::IXMLDOMNodeListPtr nodeList;
	node->get_childNodes(&nodeList);
	nodeList->get_length(&dataCnt); //获取节点个数
	IXMLDOMNode * dataNode = NULL;
	for(int i=0;i<dataCnt;i++)
	{
		nodeList->get_item(i,&dataNode);
		CString value = (char*)(_bstr_t)dataNode->text;
		map->data[i]=atoi(value);

	}

	
	return true;

}
SYSTEMTIME CRadarHistoryDlg::GetTime(CString time)
{
	COleDateTime m_date;
	SYSTEMTIME m_SysTime;
	CString szDate = time;
	m_date.ParseDateTime(szDate);
	m_date.GetAsSystemTime(m_SysTime);

	return m_SysTime;
}
CString CRadarHistoryDlg::GetNodeAttributeValue(CString strAttrName, IXMLDOMNode *pNode)
{
	IXMLDOMNamedNodeMap* pAttrMap;//节点的属性链表
	pNode->get_attributes(&pAttrMap);

	MSXML2::IXMLDOMNodePtr pAttrNode;

	BSTR bsIDText = strAttrName.AllocSysString();
	pAttrNode=pAttrMap->getNamedItem(bsIDText);
	if(pAttrNode==NULL)
		return "";
	pAttrNode->get_text(&bsIDText);
	return CString(bsIDText);
}

void CRadarHistoryDlg::BrowseFile(int CallNum, CString strFile)
{
	CallNum++;
	CFileFind ff;
	CString szDir = strFile;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	
	BOOL res = ff.FindFile(szDir);
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			//如果是一个子目录，用递归继续往深一层找
			CString strPath = ff.GetFilePath();
			CString strTitle = ff.GetFileTitle();
			int i =0;
			switch(CallNum)
			{
			case 1:
				strHTFir = m_treeTime.InsertItem(strTitle,0,0,NULL);						
				break;
			case 2:
				strHTSec = m_treeTime.InsertItem(strTitle,0,0,strHTFir);											
				break;
			case 3:
				strHtThi = m_treeTime.InsertItem(strTitle,0,0,strHTSec);					
				break;
			case 4:
				strHtFor = m_treeTime.InsertItem(strTitle,0,0,strHtThi);					
				break;
			default:
				strHtFif = m_treeTime.InsertItem(strTitle,0,0,strHtFor);
				break;					
			}
			BrowseFile(CallNum,strPath);
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			//显示当前访问的文件
			CString strPath;
			CString strTitle;
			strPath = ff.GetFilePath();
			strTitle = ff.GetFileTitle();
			switch(CallNum)
			{
			case 1:
				strRoot = m_treeTime.InsertItem(strTitle,0,0,NULL);
				break;
			case 2:
				strHtEnd = m_treeTime.InsertItem(strTitle,0,0,strHTFir);
				break;
			case 3:
				strHtEnd = m_treeTime.InsertItem(strTitle,0,0,strHTSec);				
				break;
			case 4:
				strHtEnd = m_treeTime.InsertItem(strTitle,0,0,strHtThi);
				break;
			case 5:
				strHtEnd = m_treeTime.InsertItem(strTitle,0,0,strHtFor);
				break;
			default:
				strHtEnd = m_treeTime.InsertItem(strTitle,0,0,strHtFif);
				break;
			}
		}
	}
	ff.Close();//关闭
}

void CRadarHistoryDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	m_treeTime.DeleteAllItems( );
	BrowseFile(0,DIR_HISTORY);//遍历历史数据目录
	m_treeTime.Expand(m_treeTime.GetParentItem(strHtEnd),TVE_EXPAND);//展开最后一个目录
	m_treeTime.SetFocus();

	m_mapCtrl.m_map_warningResult.objNum=0;
	m_mapCtrl.m_map_bkgrdMap.bReady=false;
	m_mapCtrl.ClearWarningObjectsForPlayBack();
	m_mapCtrl.Invalidate(TRUE);

	m_listAlarmRecord.DeleteAllItems();
}

BOOL CRadarHistoryDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
	//return CRadarBaseDlg::OnEraseBkgnd(pDC);
}
