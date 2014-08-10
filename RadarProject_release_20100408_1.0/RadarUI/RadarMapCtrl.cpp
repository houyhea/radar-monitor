// RadarMapCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarMapCtrl.h"
#include <math.h>
#include <wingdi.h>	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.14159265358979 

/////////////////////////////////////////////////////////////////////////////
// CRadarMapCtrl

CRadarMapCtrl::CRadarMapCtrl()
{
	//m_map_maxRange=30;						//检测的最大距离 m
	//m_map_minRange=0;						//检测的最小距离 m


	m_map_graduation=40;					//单位刻度，表示一个刻度是多少像素。单位：px
	m_map_scale=100;						//比例尺，表示一米是多少像素。单位：px/m (像素每米)
	m_map_scaleMax=1000;					//最大1000像素表示一米，即一个像素 1mm					
	m_map_scaleMin=1;						//最小1像素表示一米
	m_map_zoomValue=2;					

	m_map_totalPx=280;						//地图上的总长，用于设定地图的表示范围。单位：px
	m_map_angleDelta=(int)(1/0.2);				//画地图背景轮廓的角度增量。单位：0.2（不可能0.2度一画，需要抽样画，不然太多。）
	
	m_map_bkgrdMap.bReady=FALSE;
	m_map_warningResult.objNum=0;
	
	m_state=RDReadyScan;		
	m_bMeasure=false;
	
	m_Font.CreateFont(
		18,                        // nHeight,INIT
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_SEMIBOLD,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial")                    // nPitchAndFamily
		); 
}

CRadarMapCtrl::~CRadarMapCtrl()
{
	if(m_zoomInBtn!=NULL)
		delete m_zoomInBtn;
	if(m_zoomOutBtn!=NULL)
		delete m_zoomOutBtn;

	if(m_hbmpStateing!=NULL)
		DeleteObject(m_hbmpStateing);
	if(m_hbmpStated!=NULL)
		DeleteObject(m_hbmpStated);
	if(m_hbmpStateStart!=NULL)
		DeleteObject(m_hbmpStateStart);
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}


BEGIN_MESSAGE_MAP(CRadarMapCtrl, CStatic)
	//{{AFX_MSG_MAP(CRadarMapCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ZOOMLICK, OnZoomClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarMapCtrl message handlers

void CRadarMapCtrl::ReSize()
{
	
	CRect rc1;
	GetWindowRect(&rc1);//获取到了相对屏幕的坐标
	GetParent()->ScreenToClient(&rc1);//当前控件的父亲，就是对话框，得到客户区坐标

	//rc1.left=400;
	//rc1.top=10;

	rc1.bottom  = rc1.top+m_height;
	rc1.right=rc1.left+m_width;

	MoveWindow(&rc1);


}
void CRadarMapCtrl::SetSize(const CRect& rect)
{
	CRect rc;
	m_rSize = rect;
	
	if(m_zoomInBtn != NULL)
	{
		CRect rect(m_rSize);
		rect.top+=m_zoomInTopPadding;
		rect.bottom = rect.top  + m_zoomInBtnHeight;
		rect.left+=m_zoomInLeftPadding;
		rect.right=rect.left+m_zoomInBtnWidth;

		m_zoomInBtn->SetSize(rect);
	}
	if(m_zoomOutBtn != NULL)
	{
		CRect rect(m_rSize);
		rect.top+=m_zoomOutTopPadding;
		rect.bottom = rect.top  + m_zoomOutBtnHeight;
		rect.left+=m_zoomOutLeftPadding;
		rect.right=rect.left+m_zoomOutBtnWidth;

		m_zoomOutBtn->SetSize(rect);
	}

}

void CRadarMapCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	GetClientRect(&m_rSize);

	SetSize(m_rSize);	

	OnCustomDraw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}


//自绘界面
void CRadarMapCtrl::OnCustomDraw(CDC *pDC)
{
	DrawBg();

	DrawCoordinate();

	if(m_map_bkgrdMap.bReady)
	{
		DrawMap();
	}
	if(m_map_warningResult.objNum>0)
	{
		DrawWarningResult();
	}
	if(m_map_warningObjects.size()>0
		&& (m_state==RDPlayBack))
	{
		PlayBackWaringObject();
	}
	
	if(m_zoomInBtn != NULL)
		m_zoomInBtn->Draw(&m_dcMemory);	
	if(m_zoomOutBtn != NULL)
		m_zoomOutBtn->Draw(&m_dcMemory);
	
	DrawState(pDC);
	
	//最后统一拷贝到PDC中，双缓冲
	CRect   rect;   
	GetClientRect(&rect);   
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_dcMemory,0,0,SRCCOPY);

}

//画坐标
void CRadarMapCtrl::DrawCoordinate()
{
	
	CPoint startPoint,endPoint;

	//画横轴
	startPoint.x=0;
	startPoint.y=m_height/2;
	endPoint.x=m_width;
	endPoint.y=m_height/2;
	DrawLine(startPoint,endPoint);

	//画横轴箭头
	startPoint.x=endPoint.x;
	startPoint.y=endPoint.y;
	endPoint.x=endPoint.x-5;
	endPoint.y=endPoint.y-5;
	DrawLine(startPoint,endPoint);
	
	startPoint.x=m_width;
	startPoint.y=m_height/2;
	endPoint.x=startPoint.x-5;
	endPoint.y=startPoint.y+5;
	DrawLine(startPoint,endPoint);

	//画纵轴
	startPoint.x=m_width/2;
	startPoint.y=0;
	endPoint.x=m_width/2;
	endPoint.y=m_height;  
	DrawLine(startPoint,endPoint);

	//画纵轴箭头
	startPoint.x=startPoint.x;
	startPoint.y=startPoint.y;
	endPoint.x=startPoint.x-5;
	endPoint.y=startPoint.y+5;
	DrawLine(startPoint,endPoint);
	
	startPoint.x=m_width/2;
	startPoint.y=0;
	endPoint.x=startPoint.x+5;
	endPoint.y=startPoint.y+5;
	DrawLine(startPoint,endPoint);	

	//画圆形刻度
	for(int i=0;i<=m_map_totalPx/m_map_graduation;i++)
	{
		startPoint.x=m_width/2-i*m_map_graduation;
		startPoint.y=m_height/2-i*m_map_graduation;
		endPoint.x=m_width/2+i*m_map_graduation;
		endPoint.y=m_height/2+i*m_map_graduation;
		DrawCircle(startPoint.x,startPoint.y,endPoint.x,endPoint.y);
		
	}
	//画单位刻度表示的距离值
	double mpergraduation=m_map_graduation/m_map_scale;//计算单位刻度表示的距离，单位：米，m
	
	CFont* pOldFont=m_dcMemory.SelectObject(&m_Font);  
	m_dcMemory.SetTextColor(RGB(255,255,255));
	CString str;
	str.Format("单位刻度：%2.2f 米",mpergraduation);
	CRect rfont;
	rfont.left=5;
	rfont.top=5;
	rfont.bottom=m_height-5;
	rfont.right=m_width-5;
	
	m_dcMemory.DrawText(str,&rfont,DT_LEFT);
	//m_dcMemory.SelectObject(pOldFont);


}
//画地图
void CRadarMapCtrl::DrawMap()
{
	if(!m_map_bkgrdMap.bReady)
		return;
	CRect rect;
	GetClientRect(&rect);
	
	CDC * pDC=GetDC();
	//得到画布
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* oldbitmap=(CBitmap*)memDC.SelectObject(bmp);
	
	//先把m_dcmemory的拷贝过来
	memDC.BitBlt(0,0,rect.Width(),rect.Height(),&m_dcMemory,0,0,SRCCOPY);
	
	int cnt=(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle)/m_map_angleDelta + 1;
	CPoint points[1440];
	points[0].x=m_width/2;
	points[0].y=m_height/2;
	//内部解析角度
	double m_angleResolution=((double)(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle))/(m_map_bkgrdMap.mapDataLength-1);
	
	int j=1;
	for(int i=0;i<m_map_bkgrdMap.mapDataLength;i+=m_map_angleDelta)
	{
		int showPx=(int)(m_map_bkgrdMap.data[i]*m_map_scale/1000);
		
		if(showPx>m_map_totalPx)
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),(int)((double)(m_map_totalPx/m_map_scale) * 1000));
		}
		else
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),m_map_bkgrdMap.data[i]);
		}
		//DrawPoint(i,m_map_bkgrdMap.data[i]);
		//DrawLine(points[0],points[j]);
		j++;	
	}
	
	CPen   penBlue(PS_SOLID,   1,   RGB(50,200,255));   //蓝色
	CPen*   pOldPen   =   memDC.SelectObject(&penBlue);       
	
	CBrush   brushRed(RGB(0,  50,   200)); //蓝色
	CBrush*   pOldBrush   =   memDC.SelectObject(&brushRed);   	
	
	memDC.Polygon(points,j);
	
	memDC.SelectObject(pOldPen);   
	memDC.SelectObject(pOldBrush);   
	
	///////////////半透明
	BLENDFUNCTION bm;
	bm.BlendOp=AC_SRC_OVER;
	bm.BlendFlags=0;
	bm.SourceConstantAlpha=230;//0--255, 0是完全透明
	bm.AlphaFormat=0;  
	AlphaBlend(m_dcMemory.m_hDC,0,0,rect.Width(),rect.Height(),memDC.m_hDC,0,0,rect.Width(),rect.Height(),bm); 
	
	////////////////////////////////////////////////////////以下是正常画图
	/*
	if(!m_map_bkgrdMap.bReady)
	return;
	
	  int cnt=(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle)/m_map_angleDelta + 1;
	  CPoint points[1440];
	  points[0].x=m_width/2;
	  points[0].y=m_height/2;
	  //内部解析角度
	  double m_angleResolution=((double)(m_map_bkgrdMap.stopAngle-m_map_bkgrdMap.startAngle))/(m_map_bkgrdMap.mapDataLength-1);
	
	int j=1;
	for(int i=0;i<m_map_bkgrdMap.mapDataLength;i+=m_map_angleDelta)
	{
		int showPx=(int)(m_map_bkgrdMap.data[i]*m_map_scale/1000);
		
		if(showPx>m_map_totalPx)
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),(int)((double)(m_map_totalPx/m_map_scale) * 1000));
		}
		else
		{
			points[j]=ToCpoint((int)(m_map_bkgrdMap.startAngle+i*m_angleResolution),m_map_bkgrdMap.data[i]);
		}
		//DrawPoint(i,m_map_bkgrdMap.data[i]);
		//DrawLine(points[0],points[j]);
		j++;	
	}

	//CPen   penBlue(PS_SOLID,   1,   RGB(255,0,0));	//默认
	//CPen   penBlue(PS_SOLID,   1,   RGB(100,255,0));   //绿色
	CPen   penBlue(PS_SOLID,   1,   RGB(50,200,255));   //蓝色
	CPen*   pOldPen   =   m_dcMemory.SelectObject(&penBlue);       
	
	//CBrush   brushRed(RGB(123,  122,   23)); //默认
	//CBrush   brushRed(RGB(60,  200,   0)); //绿色
	CBrush   brushRed(RGB(0,  50,   200)); //蓝色
	CBrush*   pOldBrush   =   m_dcMemory.SelectObject(&brushRed);   	
	
	m_dcMemory.Polygon(points,j);

	//m_dcMemory.SelectObject(pOldPen);   
	//m_dcMemory.SelectObject(pOldBrush); 
*/
}
void CRadarMapCtrl::DrawWarningResult()
{
	if(m_map_warningResult.objNum<=0)
		return;
	for(int i=0;i<m_map_warningResult.objNum;i++)
	{
		//检测如果当前比例尺下，实际距离超出坐标显示，则不再绘制
		int showPx=(int)(m_map_warningResult.obj[i].distance*m_map_scale/1000);
		if(showPx<=m_map_totalPx)
		{
			//DrawPoint(m_map_warningResult.obj[i].angle,m_map_warningResult.obj[i].distance);		
			DrawObj(m_map_warningResult.obj[i].angle,m_map_warningResult.obj[i].distance,m_map_warningResult.obj[i].objWidth);
		}
	}
}


void CRadarMapCtrl::DrawLine(CPoint startPoint,CPoint endPoint)
{
	//m_dcMemory.FillSolidRect(&rt, 0x00FFFFFF);			// 白色填充, 注意,这次是画在内存设备环境上
	CRect   rect;   
	GetClientRect(&rect);   

	CPen pen(PS_SOLID,1,RGB(24,143,27));

	CPen *pOldPen=m_dcMemory.SelectObject(&pen);
	m_dcMemory.MoveTo(startPoint);
	m_dcMemory.LineTo(endPoint);	
	m_dcMemory.SelectObject(pOldPen);
}
void CRadarMapCtrl::DrawCircle(int x1,int y1,int x2,int y2)
{
	CBrush   *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	CBrush   *pOldBrush=m_dcMemory.SelectObject(pBrush);   
    
	m_dcMemory.SetBkMode(TRANSPARENT);   //只对文本显示有效

	CPen pen(PS_SOLID,1,RGB(24,143,27));


	CPen *pOldPen=m_dcMemory.SelectObject(&pen);
	m_dcMemory.Ellipse(x1,y1,x2,y2);
	m_dcMemory.SelectObject(pOldPen);
	m_dcMemory.SelectObject(pOldBrush);

}
void CRadarMapCtrl::DrawObj(int angle,int distance,int objWidth)
{
	//CBrush   *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));   
	CBrush   brush;
	brush.CreateSolidBrush(RGB(0,255,0));   
	CBrush   *pOldBrush=m_dcMemory.SelectObject(&brush);   
    
	CPoint point=ToCpoint(angle,distance);


	CPen pen(PS_SOLID,0,RGB(24,143,27));
	CPen *pOldPen=m_dcMemory.SelectObject(&pen);
	m_dcMemory.Ellipse(point.x-5,point.y-5,point.x+2,point.y+2);
	m_dcMemory.SelectObject(pOldBrush);
	
}

/**	描述:画点
 *	参数:
 *		angle:			点在当前地图坐标中与X轴的夹角，按照1=0.2度来表示
 *		didtance:		距离值，单位：mm	
 *	返回值:
 *	*/
void CRadarMapCtrl::DrawPoint(int angle,int distance)
{
	CPoint point=ToCpoint(angle,distance);
	m_dcMemory.SetPixel(point,RGB(255,255,255));
}
CPoint CRadarMapCtrl::ToCpoint(int angle,int distance)
{
	//需要换算到控件中的CPoint坐标
	//比如：5000mm，角度50，
	
	double d_distance=distance;

	double ang=angle*0.2;				//得到实际度数
	double x_distance,y_distance;		//实际长度（m）
	
	double l=d_distance/1000;				//斜边换算成m
	
	ang = ang / 180.0 * PI;
	x_distance= l*cos(ang); 
	y_distance= l*sin(ang);
	
	CPoint point, originPoint;
	originPoint.x=m_width/2;
	originPoint.y=m_height/2;
	
	point.x=(long)(originPoint.x+x_distance*m_map_scale);	//获取实际坐标点，相对于控件client的左上角
	point.y=(long)(originPoint.y-y_distance*m_map_scale);	//之所以是减，是因为，极坐标是逆时针旋转的。
	
	return point;
}

// 初始化和双缓冲相关的要素
void CRadarMapCtrl::InitialDBB()
{
	CDC *pDC=GetDC();
	CRect rt;
	this->GetClientRect(&rt);

	// 为屏幕DC创建兼容的内存DC
	m_dcMemory.CreateCompatibleDC(NULL);				
	// 创建位图
	m_Bmp.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());//这个地方一定要用pDC，否则会出错
	// 相当于选择画布
	::SelectObject(m_dcMemory.GetSafeHdc(), m_Bmp);			
}

void CRadarMapCtrl::DrawBg()
{
	CPen pen(PS_SOLID,1,RGB(24,143,27));

	CPen *pOldPen=m_dcMemory.SelectObject(&pen);

	CBrush   brush;   
	CRect   rect;   
	COLORREF   rgbBackGnd   =   RGB(0,0,0);   
	GetClientRect(&rect);   
	brush.CreateSolidBrush(rgbBackGnd);   
	m_dcMemory.FillRect(rect,&brush);  

}
void CRadarMapCtrl::DrawState(CDC* pDC)
{
	if(m_hbmpStateing == NULL || m_hbmpStated == NULL || m_hbmpStateStart == NULL)
		return;

	CRect r(m_rSize);
	r.left+=m_stateLeftPadding;
	r.right=r.left+m_stateWidth;
	r.top+=m_stateTopPadding;
	r.bottom=r.top+m_stateHeight;

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	BITMAP	bmpInfo; 
	
	switch(m_state)
	{
	case RDReadyScan:		//待启动
		dcMemory.SelectObject(m_bmpStateStart);
		m_bmpStateStart.GetBitmap(&bmpInfo);
		break;
	case RDStudying:		//学习中
		dcMemory.SelectObject(m_bmpStateing);
		m_bmpStateing.GetBitmap(&bmpInfo);
		break;
	case RDScanning:		//学习完毕,扫描中
		dcMemory.SelectObject(m_bmpStated);
		m_bmpStated.GetBitmap(&bmpInfo);
		break;
	case RDPlayBack:		//回放
		dcMemory.SelectObject(m_bmpStatePlayBack);
		m_bmpStated.GetBitmap(&bmpInfo);
		break;
	default:		//待启动
		dcMemory.SelectObject(m_bmpStateStart);
		m_bmpStateStart.GetBitmap(&bmpInfo);
		break;
	}
	m_dcMemory.BitBlt(r.left, r.top, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);
	
}
void CRadarMapCtrl::InitData(CString bmpZoomIn
						   ,CString bmpZoomInD
						   ,CString bmpZoomOut
						   ,CString bmpZoomOutD
						   ,CString bmpBg
						   ,CString bmpStateing
						   ,CString bmpStated
						   ,CString bmpStateStart
						   ,CString bmpStatePlayBack)
{
	m_zoomInBtn=new CRadarZoomBtn(this,1);
	m_zoomOutBtn=new CRadarZoomBtn(this,2);

	//载入图片资源
	m_zoomInBtn->LoadBkBitmap(bmpZoomIn,bmpZoomInD);
	m_zoomOutBtn->LoadBkBitmap(bmpZoomOut,bmpZoomOutD);
	
	m_hbmpStateing = (HBITMAP)::LoadImage(0, bmpStateing, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
	m_hbmpStated = (HBITMAP)::LoadImage(0, bmpStated, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
	m_hbmpStateStart = (HBITMAP)::LoadImage(0, bmpStateStart, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
	m_hbmpStatePlayBack = (HBITMAP)::LoadImage(0, bmpStatePlayBack, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 

	m_hbmpBg =(HBITMAP)::LoadImage(0, bmpBg, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
	
	if(m_hbmpStateing!=NULL)
	{
		m_bmpStateing.Attach(m_hbmpStateing);
		
	}
	if(m_hbmpStated!=NULL)
	{
		m_bmpStated.Attach(m_hbmpStated);
		
	}
	if(m_hbmpStateStart!=NULL)
	{
		m_bmpStateStart.Attach(m_hbmpStateStart);
		
	}
	if(m_hbmpStatePlayBack!=NULL)
	{
		m_bmpStatePlayBack.Attach(m_hbmpStatePlayBack);
		
	}
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
	
}
void CRadarMapCtrl::InitSizes(int width
					,int height
					,CRect	zoomInBtnRect
					,CRect  zoomOutBtnRect
					,CRect  stateRect)
{
	m_width=width;
	m_height=height;

	m_zoomInLeftPadding=zoomInBtnRect.left;
	m_zoomInTopPadding=zoomInBtnRect.top;
	m_zoomInBtnWidth=zoomInBtnRect.Width();
	m_zoomInBtnHeight=zoomInBtnRect.Height();

	m_zoomOutLeftPadding=zoomOutBtnRect.left;
	m_zoomOutTopPadding=zoomOutBtnRect.top;
	m_zoomOutBtnWidth=zoomOutBtnRect.Width();
	m_zoomOutBtnHeight=zoomOutBtnRect.Height();

	m_stateLeftPadding=stateRect.left;
	m_stateTopPadding=stateRect.top;
	m_stateWidth=stateRect.Width();
	m_stateHeight=stateRect.Height();

	ReSize();

	// 初始化和双缓冲相关的要素
	InitialDBB();

}

LRESULT CRadarMapCtrl::OnZoomClick(WPARAM wParam, LPARAM lParam)
{
	//只有在扫描中才可以缩放
	//if(m_state!=RDScanning)
	//	return 0;
	
	CString str;
	str=(lParam==1)?"放大":"缩小";
	//str.Format("%d",lParam);
	//MessageBox(str);
	if(lParam==1)
	{
		this->m_map_scale*=m_map_zoomValue;
		
		if(m_map_scale>m_map_scaleMax)
		{
			m_map_scale=m_map_scaleMax;
			
			
		}

	}
	else
	{
		this->m_map_scale/=m_map_zoomValue;
		if(m_map_scale<m_map_scaleMin)
		{
			m_map_scale=m_map_scaleMin;
			
		}
	}
	CheckZoomBtnEnable();
	Invalidate(TRUE);
	return 0;
}
void CRadarMapCtrl::CheckZoomBtnEnable()
{
	
	m_zoomInBtn->m_enable=(m_map_scale<m_map_scaleMax);
	m_zoomOutBtn->m_enable=(m_map_scale>m_map_scaleMin);
}


BOOL CRadarMapCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//这里什么都不做，直接return true,防止刷背景，出现闪烁
	return   TRUE;   
	
	//return CStatic::OnEraseBkgnd(pDC);
}

void CRadarMapCtrl::PlayBackWaringObject()
{
	for(int i=0;i<m_map_warningObjects.size();i++)
	{
		//检测如果当前比例尺下，实际距离超出坐标显示，则不再绘制
		int showPx=(int)(m_map_warningObjects[i].distance*m_map_scale/1000);
		if(showPx<=m_map_totalPx)
		{
			DrawObj(m_map_warningObjects[i].angle,m_map_warningObjects[i].distance,m_map_warningObjects[i].objWidth);
		}
	}
}
void CRadarMapCtrl::ClearWarningObjectsForPlayBack()
{	
	std::vector<WaringObject>::iterator theIt;
	for(theIt = m_map_warningObjects.begin(); theIt != m_map_warningObjects.end(); ++theIt)
	{
		m_map_warningObjects.erase(theIt);
		theIt--; 
	}
}

void CRadarMapCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(m_zoomInBtn->TestInArea(point))
	{
		m_zoomInBtn->Click();
		return;
	}
	if(m_zoomOutBtn->TestInArea(point))
	{
		m_zoomOutBtn->Click();
		return;
	}
	//记录测量起始点
	m_pos=point;
	m_bMeasure=true;

	//CStatic::OnLButtonDown(nFlags, point);
}

void CRadarMapCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bMeasure=false;

	CStatic::OnLButtonUp(nFlags, point);
}

void CRadarMapCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint x_pos;
	x_pos=point;

	//测距功能未完成。。。
	if (m_bMeasure)
	{

	}
	CStatic::OnMouseMove(nFlags, point);
}
