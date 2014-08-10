/*****************************************************************
*文件名：			RadarCommunicationBase.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2009-12-28			
*
*说明
	激光雷达通信模块通信产品基类。抽象类。定义数据通信的抽象接口，
	具体的产品的通信类必须从该类继承。
******************************************************************/

// RadarCommunicationBase.h: interface for the CRadarCommunicationBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARCOMMUNICATIONBASE_H__04E7987A_6DB4_4E78_8BD6_C4EE3E525421__INCLUDED_)
#define AFX_RADARCOMMUNICATIONBASE_H__04E7987A_6DB4_4E78_8BD6_C4EE3E525421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "struct.h"

class CRadarCommunicationBase  
{
public:
	CRadarCommunicationBase();
	virtual ~CRadarCommunicationBase();
	int		m_startAngle;		//起始角度，按照1表示0.2度的格式存储
	int		m_stopAngle;		//结束角度，同上
	int		m_bitRate;			
	char	m_comDevice[50];	//com口
	char	m_ip[50];			//IP地址
	int		m_port;				//端口号
	EnumRadar m_radar;			//雷达产品
	int		m_motorRate;		//马达转速
	bool	m_saveRawData;		//保存原始数据
	char	m_rawDataFile[500];	//原始数据文件存放路径
	int		m_validDistance;	//有效距离

	virtual int  StartRadar(void)				=	0;
	virtual int	 CloseRadar(void)				=	0;
	virtual bool GetRawData(DataFrame * pData)	=	0;
};

#endif // !defined(AFX_RADARCOMMUNICATIONBASE_H__04E7987A_6DB4_4E78_8BD6_C4EE3E525421__INCLUDED_)
