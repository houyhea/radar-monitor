/*****************************************************************
*文件名：			RadarLoginDlg.h
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
	激光雷达--登陆界面。
******************************************************************/
#if !defined(AFX_RADARLOGINDLG_H__547E2B38_0A63_4297_BAD1_C899EA03EE41__INCLUDED_)
#define AFX_RADARLOGINDLG_H__547E2B38_0A63_4297_BAD1_C899EA03EE41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarLoginDlg.h : header file
//
#include "radarapp.h"
#include "struct.h"
#include "RadarBaseDlg.h"
#include "RadarButton.h"

#pragma comment (lib, "Version.lib")    

/////////////////////////////////////////////////////////////////////////////
// CRadarLoginDlg dialog

class CRadarLoginDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarLoginDlg();
// Dialog Data
	//{{AFX_DATA(CRadarLoginDlg)
	enum { IDD = IDD_DIALOG_LOGIN };
	CRadarButton	m_closeBtn;
	CRadarButton	m_loginBtn;
	CEdit	m_pwd;
	//}}AFX_DATA

	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;
	CFont		m_Font;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CRadarLoginDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLogin();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtnClose();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL GetMyProcessVer(CString& strver);   //用来取得自己的版本号    

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARLOGINDLG_H__547E2B38_0A63_4297_BAD1_C899EA03EE41__INCLUDED_)
