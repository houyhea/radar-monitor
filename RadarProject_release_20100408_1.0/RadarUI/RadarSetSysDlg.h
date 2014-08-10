/*****************************************************************
*文件名：			RadarSetSysDlg.h
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
	激光雷达系统参数设置界面。
******************************************************************/
#if !defined(AFX_RADARSETSYSDLG_H__310C8999_C3DF_4F71_AF4E_F0A527AEB7EA__INCLUDED_)
#define AFX_RADARSETSYSDLG_H__310C8999_C3DF_4F71_AF4E_F0A527AEB7EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarSetSysDlg.h : header file
//
#include "RadarBaseDlg.h"
#include "RadarButton.h"
#include "RadarStateButton.h"
/////////////////////////////////////////////////////////////////////////////
// CRadarSetSysDlg dialog

class CRadarSetSysDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarSetSysDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarSetSysDlg();
// Dialog Data
	//{{AFX_DATA(CRadarSetSysDlg)
	enum { IDD = IDD_DIALOG_SYSSET };
	CRadarStateButton	m_radio_sound;
	CRadarStateButton	m_radio_alarm;
	CRadarButton	m_returnBtn;
	CRadarButton	m_okBtn;
	CEdit	m_alarmRecordCnt;
	//}}AFX_DATA
	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarSetSysDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadarSetSysDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonReturn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnButtonRadioAlarm();
	afx_msg void OnButtonRadioSound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARSETSYSDLG_H__310C8999_C3DF_4F71_AF4E_F0A527AEB7EA__INCLUDED_)
