/*****************************************************************
*文件名：			UIBtn.h
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
	激光雷达UI模块地图显示控件的缩放按钮类的抽象按钮类。所有自定义控件按钮都由
	该类派生。

******************************************************************/

// UIBtn.h: interface for the CUIBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIBTN_H__232728E1_B55E_4E42_919C_366068514C85__INCLUDED_)
#define AFX_UIBTN_H__232728E1_B55E_4E42_919C_366068514C85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUIBtn  
{
public:
	CUIBtn();
	virtual				~CUIBtn();

	void				SetSize(const CRect& rect)				{ m_rSize = rect;						}	
	BOOL				TestInArea(const CPoint& point) const	{ return m_rSize.PtInRect(point);		}

	virtual void		Draw(CDC *pDC)  = 0;
	virtual void		Click() = 0;

protected:
	CRect				m_rSize;

};

#endif // !defined(AFX_UIBTN_H__232728E1_B55E_4E42_919C_366068514C85__INCLUDED_)
