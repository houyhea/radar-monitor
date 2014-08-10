// RadarUI.h : main header file for the RADARUI application
//

#if !defined(AFX_RADARUI_H__AC8A20E6_E3C3_4548_954F_5010ECC9E696__INCLUDED_)
#define AFX_RADARUI_H__AC8A20E6_E3C3_4548_954F_5010ECC9E696__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRadarUIApp:
// See RadarUI.cpp for the implementation of this class
//

class CRadarUIApp : public CWinApp
{
public:
	CRadarUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRadarUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARUI_H__AC8A20E6_E3C3_4548_954F_5010ECC9E696__INCLUDED_)
