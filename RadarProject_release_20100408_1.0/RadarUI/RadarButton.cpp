// RadarButton.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRadarButton

CRadarButton::CRadarButton()
{
	m_bHover=false;
}

CRadarButton::~CRadarButton()
{
	if(m_hbmpNormal!=NULL)
		DeleteObject(m_hbmpNormal);
	if(m_hbmpHover!=NULL)
		DeleteObject(m_hbmpHover);

}


BEGIN_MESSAGE_MAP(CRadarButton, CButton)
	//{{AFX_MSG_MAP(CRadarButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarButton message handlers
void CRadarButton::LoadBmp(CString bmpNormal,CString bmpHover,CString bmpDisable)
{
		//载入图片资源
	m_hbmpNormal = (HBITMAP)::LoadImage(0, bmpNormal, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpNormal!=NULL)
	{
		m_bmpNormal.Attach(m_hbmpNormal);
	}
	//载入图片资源
	m_hbmpHover = (HBITMAP)::LoadImage(0, bmpHover, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpHover!=NULL)
	{
		m_bmpHover.Attach(m_hbmpHover);
	}

	//载入图片资源
	m_hbmpDisable = (HBITMAP)::LoadImage(0, bmpDisable, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpDisable!=NULL)
	{
		m_bmpDisable.Attach(m_hbmpDisable);
	}

}
void CRadarButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bHover ==FALSE)
	{
		//鼠标在按钮之上
		m_bHover =TRUE;
		

		//按钮重绘
		InvalidateRect(NULL,FALSE);
		
	
		//跟踪鼠标
		//当鼠标离开按钮区域会收到WM_MOUSELEAVE,该消息直接调用OnMouseOut()
		TRACKMOUSEEVENT	tme;
		tme.cbSize =sizeof(TRACKMOUSEEVENT);
		tme.dwFlags =TME_LEAVE;
		tme.dwHoverTime=0;
		tme.hwndTrack =m_hWnd;
		::TrackMouseEvent(&tme);
		
	}
	
	CButton::OnMouseMove(nFlags, point);
}

void CRadarButton::OnMouseOut (WPARAM   wParam,   LPARAM   lParam )
{
	//鼠标已离开按钮区域
    m_bHover =FALSE;

	//重绘按钮
	InvalidateRect(NULL,FALSE);
	
}

//返回鼠标是否在按钮区域内
BOOL CRadarButton::MouseOver()
{
	return m_bHover;
}

void CRadarButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

void CRadarButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	// TODO: Add your code to draw the specified item
	CDC	*pDC =CDC::FromHandle(lpDIS->hDC);
	
	HDC  memDC ;
	
	HBITMAP  hOldBitmap;	//save old bitmap temp
	BITMAP bmp;
	
	memDC = CreateCompatibleDC (pDC->m_hDC) ;
	
	if(IsWindowEnabled())
	{
		if(m_bHover)
		{
			GetObject(m_hbmpHover, sizeof(BITMAP), &bmp);
			hOldBitmap =(HBITMAP) SelectObject(memDC,m_hbmpHover) ;
		}
		else
		{
			GetObject(m_hbmpNormal, sizeof(BITMAP), &bmp);
			hOldBitmap =(HBITMAP) SelectObject(memDC,m_hbmpNormal) ;
		}
	}
	else
	{
		GetObject(m_hbmpDisable, sizeof(BITMAP), &bmp);
		hOldBitmap =(HBITMAP) SelectObject(memDC,m_hbmpDisable) ;
		
	}
	//将图片COPY到指定的像素位置
	BitBlt (pDC->m_hDC,0, 0, bmp.bmWidth, bmp.bmHeight, memDC, 0, 0, SRCCOPY ) ;
	SelectObject (memDC,hOldBitmap ) ;
}
