// RadarCommDll.cpp: implementation of the CRadarCommDll class.
//
//////////////////////////////////////////////////////////////////////

#include "RadarCommDll.h"
#include "SCIPRadarComm.h"
#include "TcpRadarComm.h"
#include "LeuzeSocketComm.h"
#include "LeuzeSerialComm.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadarCommDll::CRadarCommDll()
{

	comm_rawdata_fifo = fifo_create(sizeof(DataFrame), 10);
	if(!comm_rawdata_fifo)
	{
		return;
	}
	m_radarComm=NULL;
	m_mutex.Init();

}

CRadarCommDll::~CRadarCommDll()
{
	if(JThread::IsRunning())
		JThread::Kill();

	if(m_radarComm!=NULL)
	{
		delete m_radarComm;
		m_radarComm=NULL;
	}
	if(comm_rawdata_fifo!=NULL)
	{
		fifo_delete(comm_rawdata_fifo);
		
		comm_rawdata_fifo=NULL;
	}
}

bool CRadarCommDll::SetRawDataToFIFO(DataFrame * pData)
{
	m_mutex.Lock();
	
	
	if(!fifo_set(comm_rawdata_fifo,(uint8 *)pData))
	{
		comm_rawdata_fifo->item_cnt=0;		//如果队满，则清掉队里的内容，重新存数据
		
		if(!fifo_set(comm_rawdata_fifo,(uint8 *)pData))
		{
			m_mutex.Unlock();
			return false;				//如果还是没有，则返回false
		}
		
	}
/**/
	m_mutex.Unlock();
	return true;

}


void * CRadarCommDll::Thread()
{
	JThread::ThreadStarted();
	DataFrame p;
	//int r;
	while(1)
	{
		Sleep(10);
	
		//取原始数据，如果有原始数据，则存入FIFO，否则不做任何事情。
		if(GetRawData(&p))		
		{
			
			SetRawDataToFIFO(&p);				
		}
	}
}

/*该函数具体从硬件获取数据*/
bool CRadarCommDll::GetRawData(DataFrame * pData)
{
	if(m_radarComm!=NULL)
		return m_radarComm->GetRawData(pData);
	return false;
}

/*该函数对上层提供获取数据接口*/
bool CRadarCommDll::Comm_GetRawDataFromFIFO(DataFrame * pData)
{
	
	m_mutex.Lock();
	
	
	if(!fifo_get(comm_rawdata_fifo,(uint8 *)pData))
	{
		m_mutex.Unlock();
		return false;
	}

	m_mutex.Unlock();

	
	return true;

}

bool CRadarCommDll::Comm_StartRadar()
{
	int ret;
	if(m_radarComm!=NULL)
	{
		ret=m_radarComm->StartRadar();
		if(ret<0)
			return false;
	}
	Start();//启动线程
	return true;
}
bool CRadarCommDll::Comm_StopRadar()
{
	int ret;
	if(JThread::IsRunning())
	{		
		JThread::Kill();
	}
	if(m_radarComm!=NULL)
	{
		ret=m_radarComm->CloseRadar();
		if(ret<0)
			return false;
	}
	return true;
}
//设置参数
bool CRadarCommDll::Comm_SetRadarConfig(HardConfigInfo &cfgInfo)
{
	/*
	if(!Comm_StopRadar())
	{
		return false;
	}
	*/

	if(m_radarComm!=NULL)
	{
		delete m_radarComm;
		m_radarComm=NULL;
	}

	switch(cfgInfo.radar)
	{
	case SCIP:
		m_radarComm=new CSCIPRadarComm();
		break;
	case CustomTcpRadar:
		m_radarComm=new CTcpRadarComm();
		break;
	case LeuzeSocket://to do
		m_radarComm=new CLeuzeSocketComm();
		break;
	case LeuzeCom://to do
		m_radarComm=new CLeuzeSerialComm();
		break;		
	default:
		m_radarComm=new CSCIPRadarComm();
		break;
	}	
	
	
	m_radarComm->m_startAngle=cfgInfo.startAngle;
	m_radarComm->m_stopAngle=cfgInfo.stopAngle;
	m_radarComm->m_bitRate=cfgInfo.BitRate;
	m_radarComm->m_radar=cfgInfo.radar;
	memcpy(m_radarComm->m_comDevice,cfgInfo.comDevice,50);
	memcpy(m_radarComm->m_ip,cfgInfo.ip,50);
	m_radarComm->m_port=cfgInfo.port;
	m_radarComm->m_motorRate=cfgInfo.motorRate;

	m_radarComm->m_saveRawData=cfgInfo.saveRawData;
	memcpy(m_radarComm->m_rawDataFile,cfgInfo.rawDataFile,500);

	m_radarComm->m_validDistance=cfgInfo.validDistance;
	
	return true;
}

