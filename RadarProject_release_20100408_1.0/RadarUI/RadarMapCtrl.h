/*****************************************************************
*文件名：			RadarMapCtrl.h
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
	激光雷达UI模块地图显示控件。
******************************************************************/

#if !defined(AFX_RADARMAPCTRL_H__2428EBAB_2554_4188_ADDA_0F7DDE49A40D__INCLUDED_)
#define AFX_RADARMAPCTRL_H__2428EBAB_2554_4188_ADDA_0F7DDE49A40D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarMapCtrl.h : header file
//
#include "radarzoombtn.h"
#include "struct.h"
#include <vector>
using std::vector;

/////////////////////////////////////////////////////////////////////////////
// CRadarMapCtrl window

class CRadarMapCtrl : public CStatic
{
// Construction
public:
	CRadarMapCtrl();

// Attributes
public:
	int			m_width;						//控件宽度
	int			m_height;						//控件高度
	
	int			m_zoomInLeftPadding;			//ZOOMIN按钮左边距
	int			m_zoomInTopPadding;				//ZOOMIN按钮顶边距
	int			m_zoomInBtnWidth;				//ZOOMIN按钮宽度
	int			m_zoomInBtnHeight;				//ZOOMIN按钮高度

	int			m_zoomOutLeftPadding;			
	int			m_zoomOutTopPadding;		
	int			m_zoomOutBtnWidth;
	int			m_zoomOutBtnHeight;

	int			m_stateLeftPadding;				//状态灯左边距
	int			m_stateTopPadding;
	int			m_stateWidth;
	int			m_stateHeight;



//以下的成员变量一些与地图数据有关
	BkgrdMap		m_map_bkgrdMap;						//背景地图结构体（来自算法模块）
	WarningResult	m_map_warningResult;					//报警结果结构体

	vector<WaringObject>	m_map_warningObjects;		//报警节点，用于回放	

	//int				m_map_maxRange;						//检测的最大距离,单位：m
	//int				m_map_minRange;						//检测的最小距离，单位：m

	int				m_map_graduation;					//单位刻度，表示一个刻度是多少像素。单位：px
	double			m_map_scale;						//比例尺，表示一米是多少像素。单位：px/m (像素每米)
	double			m_map_scaleMax;						//最大比例尺
	double			m_map_scaleMin;						//最小比例尺
	double			m_map_zoomValue;					//单位缩放值

	int				m_map_totalPx;						//地图上的总长，用于设定地图的表示范围。单位：px
	int				m_map_angleDelta;					//画地图背景轮廓的角度增量。（不可能0.2度一画，需要抽样画，不然太多。）
	
	int				m_state;							//控件状态，1：待扫描；2：学习中，3：学习完毕，扫描中

protected:
	CBitmap		m_bmpStateing;
	CBitmap		m_bmpStated;
	CBitmap		m_bmpStateStart;
	CBitmap		m_bmpStatePlayBack;
	CBitmap		m_bmpBg;

	HBITMAP		m_hbmpStateing;
	HBITMAP		m_hbmpStated;
	HBITMAP		m_hbmpStateStart;
	HBITMAP		m_hbmpStatePlayBack;
	HBITMAP		m_hbmpBg;

	CRect				m_rSize;
	CRadarZoomBtn*		m_zoomInBtn;
	CRadarZoomBtn*		m_zoomOutBtn;

	CFont			m_Font;

	bool		m_bMeasure;	//测量标记
	CPoint		m_pos;		//记录测量起始点

	//以下是双缓冲用
	CDC			m_dcMemory;
	CBitmap		m_Bmp;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarMapCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRadarMapCtrl();

	void InitData(CString bmpZoomIn
						   ,CString bmpZoomInD
						   ,CString bmpZoomOut
						   ,CString bmpZoomOutD
						   ,CString bmpBg
						   ,CString bmpStateing
						   ,CString bmpStated
						   ,CString bmpStateStart
						   ,CString bmpStatePlayBack);

	void InitSizes(int width
					,int height
					,CRect	zoomInBtnRect
					,CRect  zoomOutBtnRect
					,CRect  stateRect);

	void SetSize(const CRect& rect);

	/**	描述:把距离和角度数据转换成CPOINT。angle:dan
	 *	参数:
	 *		angle:			点在当前地图坐标中与X轴的夹角，按照1=0.2度来表示
	 *		didtance:		距离值，单位：mm	
	 *	返回值:转换后的CPOINT
	 *	*/
	CPoint ToCpoint(int angle,int distance);

	void ClearWarningObjectsForPlayBack();
	// Generated message map functions
protected:
	//{{AFX_MSG(CRadarMapCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	LRESULT OnZoomClick(WPARAM wParam, LPARAM lParam);
	

	DECLARE_MESSAGE_MAP()

		
	/**	描述:画坐标
	 *	参数:
	 *	返回值:
	 *	*/
	void		DrawCoordinate();
	void		DrawMap();
	void		DrawWarningResult();

	
	void		DrawLine(CPoint startPoint,CPoint endPoint);
	void		DrawCircle(int x1,int y1,int x2,int y2);
	void		DrawObj(int angle,int distance,int objWidth);
	/**	描述:画点
	 *	参数:
	 *		angle:			点在当前地图坐标中与X轴的夹角，按照1=0.2度来表示
	 *		didtance:		距离值，单位：mm	
	 *	返回值:
	 *	*/
	void		DrawPoint(int angle,int distance);
	/**	描述:回放报警节点
	 *	参数:
	 *	返回值:转换后的CPOINT
	 *	*/
	void PlayBackWaringObject();

	void		DrawState(CDC *pDC);
	void		DrawBg();
	void		OnCustomDraw(CDC *pDC);
	void		ReSize();
	void		CheckZoomBtnEnable();	//检查缩放按钮是否有效

	void		InitialDBB();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARMAPCTRL_H__2428EBAB_2554_4188_ADDA_0F7DDE49A40D__INCLUDED_)
