/*****************************************************************
*文件名：			RadarButton.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2010-2-1			
*
*说明
	激光雷达--UI美化切换状态按钮类
******************************************************************/
#if !defined(AFX_RADARSTATEBUTTON_H__2A9885DB_9CCC_453A_A085_5FDE6A38FBC8__INCLUDED_)
#define AFX_RADARSTATEBUTTON_H__2A9885DB_9CCC_453A_A085_5FDE6A38FBC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarStateButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadarStateButton window

class CRadarStateButton : public CButton
{
// Construction
public:
	CRadarStateButton();

// Attributes
public:
	bool		m_bOn;		//是否On状态
protected:
	CBitmap		m_bmpOn;
	HBITMAP		m_hbmpOn;

	CBitmap		m_bmpOff;
	HBITMAP		m_hbmpOff;

	CBitmap		m_bmpDisable;
	HBITMAP		m_hbmpDisable;
// Operations
public:
	void LoadBmp(CString bmpOn,CString bmpOff,CString bmpDisable);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRadarStateButton();
	void SetState(bool state);
	// Generated message map functions
protected:
	//{{AFX_MSG(CRadarButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARSTATEBUTTON_H__2A9885DB_9CCC_453A_A085_5FDE6A38FBC8__INCLUDED_)
