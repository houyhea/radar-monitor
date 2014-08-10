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
	激光雷达--通信解析层--自制简易雷达TCP SOCKET数据解析类。
	自制雷达的原始数据格式描述如下：
	雷达接收socket连接后，不断发出距离数据，距离数据用两字节表示，先发高位字节，再发低位字节。
	每一帧之间用0xff 0xff两个字节隔开。
	距离数据的格式细节：高位字节的bit0-bit5 作为距离数据的高6位，低位字节的bit0-bit6作为距离数据的低7位，总共13位。
	高位字节的bit7始终为1，低位字节的bit7始终为0.

  请留意0xff 0xff把距离数据的两个字节隔开的情况，这种情况需要丢弃该距离数据。
******************************************************************/
// TcpRadarComm.h: interface for the CTcpRadarComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPRADARCOMM_H__40B84CE6_8603_4BBF_BF0F_4499FBBE72A1__INCLUDED_)
#define AFX_TCPRADARCOMM_H__40B84CE6_8603_4BBF_BF0F_4499FBBE72A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RadarCommunicationBase.h"
#include <vector>
using std::vector;

//#include <winsock2.h>

class CTcpRadarComm : public CRadarCommunicationBase  
{
public:
	CTcpRadarComm();
	virtual ~CTcpRadarComm();

	virtual int  StartRadar(void);
	virtual int	 CloseRadar(void);
	virtual bool GetRawData(DataFrame * pData);
	

private:
	FILE * m_pFile;//文件指针
	int reciveBytes;
	int m_discardFrameCnt;//设置丢弃的帧数，前几帧不稳定，需要丢弃
	int m_discardCurrentFrameCnt;//当前丢弃的帧数
	
	vector<unsigned char> m_rawDataBuff;
	bool findSeperateTag;	//是否找到隔断标志
	unsigned char tagBuffer[2];
	int tagBufferNumber;

	bool discardFirstByte;		//是否丢掉头一个字节。由于两个字节的距离数据中间可能插入结束FFFF标志，所以有时候需要丢掉头一个字节

private:
	SOCKET  m_socket;
	bool ProcessData(char * recvBuf,int size,DataFrame * pData);
	bool LoadData(DataFrame * pData);


	void ClearRawData();

	void ReSetTagBuffer();
	void SetTagBuffer(unsigned char tag);
	bool CheckSeperateTag();
	int GetDistance(unsigned char highByte,unsigned char lowByte);


};

#endif // !defined(AFX_TCPRADARCOMM_H__40B84CE6_8603_4BBF_BF0F_4499FBBE72A1__INCLUDED_)
