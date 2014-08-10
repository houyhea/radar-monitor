/*****************************************************************
*文件名：			RadarCommDll.h
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
	激光雷达通信模块对外接口类。它负责维护底层通信模块的数据通信，
	产品协议的更换。
******************************************************************/

// RadarCommDll.h: interface for the CRadarCommDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARCOMMDLL_H__644DF948_F73C_4AB8_A2FB_77C4A9999E6B__INCLUDED_)
#define AFX_RADARCOMMDLL_H__644DF948_F73C_4AB8_A2FB_77C4A9999E6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Jthread.h"
#include "jmutex.h"
#include "fifo.h"

#include "struct.h"
#include "RadarCommunicationBase.h"


#ifdef RADARCOMM_EXPORTS
class _declspec(dllexport) CRadarCommDll : public JThread    //导出类circle
#else
class _declspec(dllimport) CRadarCommDll : public JThread    //导入类circle
#endif
{
public:
	CRadarCommDll();
	virtual ~CRadarCommDll();

	/**	描述:对外接口，从FIFO获取原始数据，返回false表示没有原始数据
	 *	参数:
	 *		
	 *	返回值:
	 *	*/
	bool Comm_GetRawDataFromFIFO(DataFrame * pData);			
	
	
	/**	描述:启动雷达
	 *	参数:
	 *		
	 *	返回值:
	 *	*/
	bool Comm_StartRadar();

	/**	描述:停止雷达
	 *	参数:
	 *		
	 *	返回值:
	 *	*/
	bool Comm_StopRadar();

	/**	描述:初始化雷达
	 *	参数:
	 *		
	 *	返回值:
	 *	*/
	bool Comm_SetRadarConfig(HardConfigInfo &cfgInfo);
	
	

private:
	JMutex				m_mutex;										//互斥锁
	FIFO_LIST*			comm_rawdata_fifo;								//原始数据缓存队列
	void*				Thread(); 
	bool				SetRawDataToFIFO(DataFrame * pData);			//把原始数据存入FIFO
	bool				GetRawData(DataFrame * pData);					//从激光雷达获取原始数据
	
	CRadarCommunicationBase	*	m_radarComm;		//雷达通信实例指针，根据产品获取不同产品对应的通信类
};

#endif // !defined(AFX_RADARCOMMDLL_H__644DF948_F73C_4AB8_A2FB_77C4A9999E6B__INCLUDED_)
