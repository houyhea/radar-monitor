/*****************************************************************
*文件名：			RadarParamSetDlg.h
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
	激光雷达--参数设置控制面板。
******************************************************************/
#if !defined(AFX_RADARPARAMSETDLG_H__3E3DC1BC_CF83_4729_86BF_B19F35F58B91__INCLUDED_)
#define AFX_RADARPARAMSETDLG_H__3E3DC1BC_CF83_4729_86BF_B19F35F58B91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarParamSetDlg.h : header file
//
#include "RadarBaseDlg.h"
#include "RadarButton.h"
/////////////////////////////////////////////////////////////////////////////
// CRadarParamSetDlg dialog

class CRadarParamSetDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarParamSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarParamSetDlg();
// Dialog Data
	//{{AFX_DATA(CRadarParamSetDlg)
	enum { IDD = IDD_DIALOG_PARAMSET };
	CRadarButton	m_sysBtn;
	CRadarButton	m_returnBtn;
	CRadarButton	m_radarBtn;
	CRadarButton	m_pwdBtn;
	CRadarButton	m_algBtn;
	//}}AFX_DATA

	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarParamSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadarParamSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReturn();
	afx_msg void OnButtonPwd();
	afx_msg void OnButtonRadar();
	afx_msg void OnButtonSys();
	afx_msg void OnButtonAlg();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARPARAMSETDLG_H__3E3DC1BC_CF83_4729_86BF_B19F35F58B91__INCLUDED_)
