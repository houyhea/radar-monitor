/*****************************************************************
*文件名：			RadarSetAlgDlg.h
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
	激光雷达--算法设置界面。
******************************************************************/
#if !defined(AFX_RADARSETALGDLG_H__C7174670_4BBE_4A74_A393_1DD191430BD2__INCLUDED_)
#define AFX_RADARSETALGDLG_H__C7174670_4BBE_4A74_A393_1DD191430BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarSetAlgDlg.h : header file
//
#include "Radarbasedlg.h"
#include "RadarButton.h"

/////////////////////////////////////////////////////////////////////////////
// CRadarSetAlgDlg dialog

class CRadarSetAlgDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarSetAlgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarSetAlgDlg();
// Dialog Data
	//{{AFX_DATA(CRadarSetAlgDlg)
	enum { IDD = IDD_DIALOG_ALGSET };
	CRadarButton	m_returnBtn;
	CRadarButton	m_okBtn;
	CEdit	m_widthThreshold;
	CEdit	m_sameObLength;
	CEdit	m_fushionTime;
	CEdit	m_fushionStepNum;
	CEdit	m_buldMapPrd;
	CEdit	m_bkgrdOffset;
	//}}AFX_DATA
	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarSetAlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadarSetAlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonReturn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARSETALGDLG_H__C7174670_4BBE_4A74_A393_1DD191430BD2__INCLUDED_)
