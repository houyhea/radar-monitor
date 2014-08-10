// RadarRoomBtn.cpp: implementation of the CRadarZoomBtn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarZoomBtn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CRadarZoomBtn::CRadarZoomBtn(CWnd* pWnd,int zoom)
		: m_pWnd(pWnd),m_zoomTag(zoom) 
{
	m_enable=true;
}

CRadarZoomBtn::~CRadarZoomBtn()
{
	if(m_hbmpbgEnable!=NULL)
		DeleteObject(m_hbmpbgEnable);
	if(m_hbmpbgDisable!=NULL)
		DeleteObject(m_hbmpbgDisable);
}
void CRadarZoomBtn::Click()
{
	if(m_enable)
		m_pWnd->SendMessage(WM_ZOOMLICK, (LONG)this, (LONG)m_zoomTag);
}
void CRadarZoomBtn::Draw(CDC *pDC)
{
	//根据当前是否是选中状态，重画界面	
	if(m_hbmpbgEnable==NULL || m_hbmpbgDisable==NULL)
		return;
	
	CRect rect(m_rSize);
	
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap * m_pOldBitmap;
	BITMAP	bmpInfo; 
	if(m_enable)
	{
		m_pOldBitmap = (CBitmap*)dcMemory.SelectObject(m_bitmapBgEnable);
		m_bitmapBgEnable.GetBitmap(&bmpInfo);
	}
	else
	{
		m_pOldBitmap = (CBitmap*)dcMemory.SelectObject(m_bitmapBgDisable);
		m_bitmapBgDisable.GetBitmap(&bmpInfo);

	}
	pDC->BitBlt(rect.left, rect.top, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);	
	//dcMemory.SelectObject(m_pOldBitmap);
	
}
void CRadarZoomBtn::LoadBkBitmap(CString bitmapbgEnable,CString bitmapbgDisable)
{
	//m_hbmpbgEnable =(HBITMAP)::LoadImage(0, "path\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hbmpbgEnable =(HBITMAP)::LoadImage(0, bitmapbgEnable, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	
	m_hbmpbgDisable = (HBITMAP)::LoadImage(0, bitmapbgDisable, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpbgEnable!=NULL)
	{
		m_bitmapBgEnable.Attach(m_hbmpbgEnable);
	}
	if(m_hbmpbgDisable!=NULL)
	{
		m_bitmapBgDisable.Attach(m_hbmpbgDisable);
	}
}