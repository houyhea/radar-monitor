/*****************************************************************
*文件名：			TcpRadarComm.h
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
	激光雷达--通信解析层--劳易测雷达数据解析类，SOCKET，网口。相关协议格式请参考SPEC
******************************************************************/
// LeuzeSocketComm.h: interface for the CLeuzeSocketComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEUZESOCKETCOMM_H__58F35304_378B_4C07_BD9B_5E8BAEBEEF7F__INCLUDED_)
#define AFX_LEUZESOCKETCOMM_H__58F35304_378B_4C07_BD9B_5E8BAEBEEF7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RadarCommunicationBase.h"
#include <vector>
using std::vector;

class CLeuzeSocketComm : public CRadarCommunicationBase  
{
public:
	CLeuzeSocketComm();
	virtual ~CLeuzeSocketComm();
	virtual int  StartRadar(void);
	virtual int	 CloseRadar(void);
	virtual bool GetRawData(DataFrame * pData);
private:
	FILE * m_pFile;//文件指针
	SOCKET  m_socket;
	vector<unsigned char> m_rawDataBuff;
	
	int angluarResolution;

	bool findStartTag;	//是否找到起始标志
	bool findStopTag;	//是否找到结束标志
	
	unsigned char tagBuffer[3];
	int tagBufferNumber;

protected:
	void ClearRawData();
	bool ProcessData(char * recvBuf,int size,DataFrame * pData);
	void ReSetTagBuffer();
	void SetTagBuffer(unsigned char tag);
	bool CheckStartTag();
	bool CheckStopTag();
	bool LoadData(DataFrame *pData);
	int  GetDistance(unsigned char highByte,unsigned char lowByte);

	int GetDataOffset();

	bool CheckSum();
	bool CheckOperation();
	int GetOptionByteNum();
	int GetAngularResolution();


};

#endif // !defined(AFX_LEUZESOCKETCOMM_H__58F35304_378B_4C07_BD9B_5E8BAEBEEF7F__INCLUDED_)
