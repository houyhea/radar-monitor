/*****************************************************************
*文件名：			RadarHistoryDlg.h
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
	激光雷达--历史数据显示界面
******************************************************************/
#if !defined(AFX_RADARHISTORYDLG_H__C7B77EFA_4210_43E4_BB41_3152559A25CC__INCLUDED_)
#define AFX_RADARHISTORYDLG_H__C7B77EFA_4210_43E4_BB41_3152559A25CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarHistoryDlg.h : header file
//
#include "RadarBaseDlg.h"
#include "RadarMapCtrl.h"
#include "RadarFileOp.h"
#include "RadarButton.h"

#import "msxml3.dll"
using namespace MSXML2;
/////////////////////////////////////////////////////////////////////////////
// CRadarHistoryDlg dialog

class CRadarHistoryDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarHistoryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarHistoryDlg();
// Dialog Data
	//{{AFX_DATA(CRadarHistoryDlg)
	enum { IDD = IDD_DIALOG_HISTORY };
	CRadarButton	m_returnBtn;
	CRadarButton	m_refreshBtn;
	CTreeCtrl	m_treeTime;
	CRadarMapCtrl	m_mapCtrl;
	CListCtrl	m_listAlarmRecord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarHistoryDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HTREEITEM strRoot;
	HTREEITEM strHTFir;
	HTREEITEM strHTSec;
	HTREEITEM strHtThi;
	HTREEITEM strHtFor;
	HTREEITEM strHtFif;
	HTREEITEM strHtEnd;

	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;

	CRadarFileOp m_fileOp;			//文件目录操作对象
	
	void BrowseFile(int CallNum, CString strFile);

	// Generated message map functions
	//{{AFX_MSG(CRadarHistoryDlg)
	afx_msg void OnButtonReturn();
	afx_msg void OnSelchangedTreeTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRefresh();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
		void InitMapCtrl();
		bool  GetMap(CString xmlFile,BkgrdMap* map);
		CString GetNodeAttributeValue(CString strAttrName, IXMLDOMNode *pNode);
		SYSTEMTIME GetTime(CString time);	
		bool GetWarningResult(CString xmlFile);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARHISTORYDLG_H__C7B77EFA_4210_43E4_BB41_3152559A25CC__INCLUDED_)
