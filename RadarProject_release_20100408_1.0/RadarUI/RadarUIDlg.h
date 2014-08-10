/*****************************************************************
*文件名：			RadarUIDlg.h
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
	激光雷达主界面。
******************************************************************/

// RadarUIDlg.h : header file
//

#if !defined(AFX_RADARUIDLG_H__FE834DC9_55DC_4E2B_8476_693092FEDD2E__INCLUDED_)
#define AFX_RADARUIDLG_H__FE834DC9_55DC_4E2B_8476_693092FEDD2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRadarUIDlg dialog
#include "struct.h"
#include "radarmapCtrl.h"
#include "RadarBaseDlg.h"
#include "RadarFileOp.h"
#include "radarbutton.h"
#include "RadarStateButton.h"

class CRadarUIDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarUIDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CRadarUIDlg();
// Dialog Data
	//{{AFX_DATA(CRadarUIDlg)
	enum { IDD = IDD_RADARUI_DIALOG };
	CRadarButton	m_closeBtn;
	CRadarButton	m_paramBtn;
	CRadarButton	m_historyBtn;
	CRadarStateButton	m_soundBtn;
	CRadarStateButton	m_alarmBtn;
	CRadarButton	m_stopBtn;
	CRadarButton	m_startBtn;
	CRadarMapCtrl	m_mapCtrl;
	CListCtrl	m_alarmRecordList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
	bool m_enableAlarm;		//响应报警
	bool m_enableSound;		//开启声音
	int  m_alarmListShowMaxCnt;	//报警记录显示最大数量

	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;

	CPoint m_pos;
	bool ismove;


	CString m_xmlFileName;			//用于存历史记录的xml文件名
	CRadarFileOp m_fileOp;			//文件目录操作对象
	// Generated message map functions
	//{{AFX_MSG(CRadarUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStartRadar();
	afx_msg void OnButtonStopRadar();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonAlarm();
	afx_msg void OnButtonClosesound();
	afx_msg void OnButtonHistory();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseOut(WPARAM   wParam,   LPARAM   lParam);
	//}}AFX_MSG
	LRESULT OnGetData(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetMap(WPARAM wParam, LPARAM lParam);
	LRESULT OnDataTimeOut(WPARAM wParam, LPARAM lParam);
	LRESULT OnSysParamChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	void InitMapCtrl();
	void LoadSysParam();
	void CheckAlarmList();
	
	void SaveWarnigData(WarningResult * warningData);	
	void SaveMap(BkgrdMap * map);
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARUIDLG_H__FE834DC9_55DC_4E2B_8476_693092FEDD2E__INCLUDED_)
