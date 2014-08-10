/*****************************************************************
*文件名：			SCIPRadarComm.h
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
	激光雷达--通信解析层--通信模块日本SCIP激光产品通信类。串口。相关格式，请参考产品SPEC
******************************************************************/

// SCIPRadarComm.h: interface for the CSCIPRadarComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCIPRADARCOMM_H__43B215BF_B7FA_4643_A04D_CBC5293FA058__INCLUDED_)
#define AFX_SCIPRADARCOMM_H__43B215BF_B7FA_4643_A04D_CBC5293FA058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus		//使用这种方式包含，调用C语言库
extern "C" {
#endif

#include "urg_ctrl.h"

#ifdef __cplusplus
	}
#endif

#include "RadarCommunicationBase.h"

class CSCIPRadarComm : public CRadarCommunicationBase  
{
public:
	CSCIPRadarComm();
	virtual ~CSCIPRadarComm();

	virtual int  StartRadar(void);
	virtual int	 CloseRadar(void);
	virtual bool GetRawData(DataFrame * pData);
private:
	urg_t urg;
	double m_degreePerIndex;		//单位步数代表的度数
	double m_maxDegree;			//扫描的实际最大度数
protected:
	bool ResolveData(long data[],int dataLength,DataFrame * pData);
};

#endif // !defined(AFX_SCIPRADARCOMM_H__43B215BF_B7FA_4643_A04D_CBC5293FA058__INCLUDED_)
