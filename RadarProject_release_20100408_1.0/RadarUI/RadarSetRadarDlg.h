/*****************************************************************
*文件名：			CRadarSetRadarDlg.h
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
	激光雷达雷达参数设置界面。
******************************************************************/
#if !defined(AFX_RADARSETRADARDLG_H__DD8C20ED_250C_4FB6_8AEF_82E5DBF4B16D__INCLUDED_)
#define AFX_RADARSETRADARDLG_H__DD8C20ED_250C_4FB6_8AEF_82E5DBF4B16D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarSetRadarDlg.h : header file
//
#include "RadarBaseDlg.h"
#include "RadarButton.h"
#include "RadarStateButton.h"
/////////////////////////////////////////////////////////////////////////////
// CRadarSetRadarDlg dialog

class CRadarSetRadarDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarSetRadarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarSetRadarDlg();

// Dialog Data
	//{{AFX_DATA(CRadarSetRadarDlg)
	enum { IDD = IDD_DIALOG_RADARSET };
	CRadarStateButton	m_radio_saveData;
	CRadarButton	m_returnBtn;
	CRadarButton	m_okBtn;
	CEdit	m_validDistance;
	CEdit	m_rawDataFile;
	CButton	m_fileBtn;
	CEdit	m_motorRate;
	CEdit	m_stopAngle;
	CEdit	m_startAngle;
	CEdit	m_ipPort;
	CEdit	m_ipAddr;
	CEdit	m_comPort;
	CEdit	m_bitRate;
	CComboBox	m_radarList;
	//}}AFX_DATA
	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarSetRadarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadarSetRadarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReturn();
	afx_msg void OnButtonOk();
	afx_msg void OnSelchangeComboRadar();
	afx_msg void OnButtonFile();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnButtonRadioSavefile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARSETRADARDLG_H__DD8C20ED_250C_4FB6_8AEF_82E5DBF4B16D__INCLUDED_)
