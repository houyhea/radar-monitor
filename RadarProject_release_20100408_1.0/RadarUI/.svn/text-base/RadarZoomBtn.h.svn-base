/*****************************************************************
*文件名：			RadarRoomBtn.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2009-12-29			
*
*说明
	激光雷达UI模块地图显示控件的缩放按钮类。
******************************************************************/

// RadarRoomBtn.h: interface for the CRadarZoomBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARROOMBTN_H__6845208E_7CB8_4CCC_89A1_2CB2486D6486__INCLUDED_)
#define AFX_RADARROOMBTN_H__6845208E_7CB8_4CCC_89A1_2CB2486D6486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIBtn.h"

//自定义消息
#define WM_ZOOMLICK		WM_USER+110			//缩放按钮消息



class CRadarZoomBtn : public CUIBtn  
{
public:
	
	CRadarZoomBtn(CWnd* pWnd,int zoom);

	virtual						~CRadarZoomBtn();
	virtual void				Draw(CDC *pDC);
	virtual void				Click();
	void						LoadBkBitmap(CString bitmapbgEnable,CString bitmapbgDisable);

	void						SetZoomTag( int zoom) 	   {  m_zoomTag=zoom;					}
	bool						m_enable;

protected:
	int						m_zoomTag;	//1,zoomIn,2,zoomOut
	
	CWnd*					m_pWnd;
	CBitmap					m_bitmapBgEnable;
	CBitmap					m_bitmapBgDisable;
	HBITMAP					m_hbmpbgEnable;
	HBITMAP					m_hbmpbgDisable;
};

#endif // !defined(AFX_RADARROOMBTN_H__6845208E_7CB8_4CCC_89A1_2CB2486D6486__INCLUDED_)
