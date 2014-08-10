// SCIPRadarComm.cpp: implementation of the CSCIPRadarComm class.
//
//////////////////////////////////////////////////////////////////////

#include "SCIPRadarComm.h"
#include <ctime>  //随机数部分

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSCIPRadarComm::CSCIPRadarComm()
{
	m_degreePerIndex=0.25;
	m_maxDegree=270.25;
	
}

CSCIPRadarComm::~CSCIPRadarComm()
{
	
}

int  CSCIPRadarComm::StartRadar(void)
{	
	int ret;	
	ret = urg_connect(&urg, m_comDevice, m_bitRate);	
	if (ret < 0) 
	{		
		return -1;
	}
		
	return 1;
	
}
int	 CSCIPRadarComm::CloseRadar(void)
{
	if(urg.is_laser_on_==UrgLaserOn)
	{
		//具体发送命令去控制雷达停止
		urg_disconnect(&urg);
	}
	return 1;
}

//获取原始数据，这里去调用SCIP lib的库函数，填充DataFrame实体
bool CSCIPRadarComm::GetRawData(DataFrame * pData)
{
	int data_max;
	long *data;
	int ret;
	int n;
	
	data_max = urg_dataMax(&urg);
	data = new long[data_max];
	if (data == NULL) {
		//perror("malloc");
		return false;
	}
	memset(data,0,sizeof(long)*data_max);	
	
	ret = urg_requestData(&urg, URG_GD, URG_FIRST, URG_LAST);	
	if (ret < 0) {
		delete data;
		return false;
	}
	
	n = urg_receiveData(&urg, data, data_max);//n 表示返回的距离个数，最大1081
	if (n < 0) {
		delete data;
		return false;
	}
				
	if( ResolveData(data,n,pData))	//解析原始数据，存入自己定义的原始数据
	{
		delete data;
		return true;
	}
	else
	{
		delete data;
		return false;
	}
	
}
bool CSCIPRadarComm::ResolveData(long data[],int dataLength,DataFrame * pData)
{
	if(m_startAngle<-225)
		m_startAngle=-225;
	if(m_stopAngle>1125)
		m_stopAngle=1125;
	if(m_stopAngle<=m_startAngle)
	{
		m_startAngle=-225;
		m_stopAngle=1125;
	}

	int startDataNumber=(int)((m_startAngle-(-225))*0.2/0.25);//获取起始角在data数组中的距离值序号
	int stopDataNumber=(int)((m_stopAngle-(-225))*0.2/0.25);//获取结束角在data数组中的距离值序号

	pData->dataLength=stopDataNumber-startDataNumber+1;//需要在实际长度上再加1
	pData->startAngle=m_startAngle;											//起始角度
	pData->stopAngle=m_stopAngle;											//结束角度
	
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	pData->time=stime;
	
	
	int index=0;
	for(int i=0;i<dataLength;i++)
	{
		if(i<startDataNumber)
			continue;
		if(i>=stopDataNumber)
			break;

		if(data[i]==1 || data[i]>m_validDistance)
			pData->data[index]=m_validDistance;//如果原始距离数据为1，表示是光线未返回，需要设置成有效距离
		else	
			pData->data[index]=data[i];
		
		index++;
	}
	return true;
}