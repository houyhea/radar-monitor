// RadarStateButton.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarStateButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarStateButton

CRadarStateButton::CRadarStateButton()
{
		m_bOn=false;
}

CRadarStateButton::~CRadarStateButton()
{
		if(m_hbmpOn!=NULL)
		DeleteObject(m_hbmpOn);
	if(m_hbmpOff!=NULL)
		DeleteObject(m_hbmpOff);

}


BEGIN_MESSAGE_MAP(CRadarStateButton, CButton)
	//{{AFX_MSG_MAP(CRadarStateButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarStateButton message handlers
void CRadarStateButton::LoadBmp(CString bmpOn,CString bmpOff,CString bmpDisable)
{
		//载入图片资源
	m_hbmpOn = (HBITMAP)::LoadImage(0, bmpOn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpOn!=NULL)
	{
		m_bmpOn.Attach(m_hbmpOn);
	}
	//载入图片资源
	m_hbmpOff = (HBITMAP)::LoadImage(0, bmpOff, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpOff!=NULL)
	{
		m_bmpOff.Attach(m_hbmpOff);
	}

	//载入图片资源
	m_hbmpDisable = (HBITMAP)::LoadImage(0, bmpDisable, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpDisable!=NULL)
	{
		m_bmpDisable.Attach(m_hbmpDisable);
	}

}



void CRadarStateButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

void CRadarStateButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	// TODO: Add your code to draw the specified item
	CDC	*pDC =CDC::FromHandle(lpDIS->hDC);
	
	HDC  memDC ;
	
	HBITMAP  hOldBitmap;	//save old bitmap temp
	BITMAP bmp;
	
	memDC = CreateCompatibleDC (pDC->m_hDC) ;
	
	if(IsWindowEnabled())
	{
		if(m_bOn)
		{
			GetObject(m_hbmpOn, sizeof(BITMAP), &bmp);
			hOldBitmap =(HBITMAP) SelectObject(memDC,m_hbmpOn) ;
		}
		else
		{
			GetObject(m_hbmpOff, sizeof(BITMAP), &bmp);
			hOldBitmap =(HBITMAP) SelectObject(memDC,m_hbmpOff) ;
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
void CRadarStateButton::SetState(bool state)
{
	m_bOn=state;
	//按钮重绘
	InvalidateRect(NULL,FALSE);

}
