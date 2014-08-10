// RadarBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarBaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarBaseDlg dialog


CRadarBaseDlg::CRadarBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRadarBaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarBaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRadarBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarBaseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarBaseDlg, CDialog)
	//{{AFX_MSG_MAP(CRadarBaseDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarBaseDlg message handlers
void CRadarBaseDlg::ShowBmpPicByHBITMAP(HDC dc,HBITMAP hBitmap,int x,int y)
{
	if(hBitmap!=NULL)
	{
		
		HDC  memDC ;
		
		HBITMAP  hOldBitmap;	//save old bitmap temp
		BITMAP bmp;
		
		memDC = CreateCompatibleDC (dc) ;
		
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		
		hOldBitmap =(HBITMAP) SelectObject(memDC,hBitmap) ;
		
		//将图片COPY到指定的像素位置
		BitBlt (dc,x, y, bmp.bmWidth, bmp.bmHeight, memDC, 0, 0, SRCCOPY ) ;
		SelectObject (memDC,hOldBitmap ) ;
	}
	
}