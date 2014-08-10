// TcpRadarComm.cpp: implementation of the CTcpRadarComm class.
//
//////////////////////////////////////////////////////////////////////

#include "TcpRadarComm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpRadarComm::CTcpRadarComm()
{
	m_pFile=NULL;
	reciveBytes=0;
	m_discardFrameCnt=0;//丢弃前3帧
	m_discardCurrentFrameCnt=0;
	findSeperateTag=false;
	ReSetTagBuffer();

	discardFirstByte=false;
}

CTcpRadarComm::~CTcpRadarComm()
{
	closesocket(m_socket);
	WSACleanup();
	ClearRawData();
	
}
//公共标识buf操作方法
void CTcpRadarComm::SetTagBuffer(unsigned char tag)
{
	if(tagBufferNumber==2)
	{
		tagBuffer[0]=tagBuffer[1];
		tagBufferNumber=1;
	}
	tagBuffer[tagBufferNumber]=tag;
	tagBufferNumber++;
}
void CTcpRadarComm::ReSetTagBuffer()
{
	tagBuffer[0]=0x00;
	tagBuffer[1]=0x00;

	tagBufferNumber=0;
}

int  CTcpRadarComm::StartRadar(void)
{
	if(m_saveRawData)
	{
		m_pFile=fopen(m_rawDataFile,"w");
		if(!m_pFile)
			return false;
	}

	//检查SOCKET版本
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return -1;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return -1; 
	}
	
	//连接
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	
	
	int TimeOut=1000;//设置接收超时 
	
	if(::setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&TimeOut,sizeof(int))==SOCKET_ERROR){
		
		return -1;
		
	}
	
	SOCKADDR_IN addrSrv;
	//addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//addrSrv.sin_addr.S_un.S_addr=inet_addr("10.13.15.60");
	addrSrv.sin_addr.S_un.S_addr=inet_addr(m_ip);
	
	
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(m_port);
	int ret=connect(m_socket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	if(ret == SOCKET_ERROR )
		return -1;
	else
		return 1;
	
}
int	 CTcpRadarComm::CloseRadar(void)
{
	if(m_saveRawData)
	{
		if(m_pFile!=NULL)
		{
			//关闭文件
			fclose(m_pFile);
			m_pFile=NULL;
		}
	}
	closesocket(m_socket);
	WSACleanup();
	ClearRawData();
	m_discardCurrentFrameCnt=0;
	return 1;
}
bool CTcpRadarComm::GetRawData(DataFrame * pData)
{
	char recvBuf[250];
	int recvCnt=recv(m_socket,recvBuf,250,0);
	if(recvCnt<=0)
		return false;
	reciveBytes+=recvCnt;
	return ProcessData(recvBuf,recvCnt,pData);
	
}

//判断隔断标识
bool CTcpRadarComm::CheckSeperateTag()
{
	if(tagBufferNumber!=2)
		return false;

	if(tagBuffer[0]==0xff
		&& tagBuffer[1]==0xff)
	{
		return true;
	}
	else
		return false;	
}
//处理接收的数据
bool CTcpRadarComm::ProcessData(char * recvBuf,int size,DataFrame * pData)
{
	char * ptr=recvBuf;
	bool rettag=false;
	char * p;
	unsigned char byte;

	for(int i=0;i<size;i+=1,ptr+=1)
	{
		p=ptr;
		byte=*p;
		SetTagBuffer(byte);
		m_rawDataBuff.push_back(byte);

		if(CheckSeperateTag())
		{
			findSeperateTag=true;
			ReSetTagBuffer();
			rettag=LoadData(pData);				//处理数据，填充原始数据
			//存入文件,结束标志
			if(m_saveRawData)
			{
				fprintf(m_pFile,"-1\n");
			}
			continue;
		}		
	}	
	return rettag;
}
bool CTcpRadarComm::LoadData(DataFrame * pData)
{
	if(m_rawDataBuff.size()==0)
	{
		ClearRawData();//装载一次，就必须清空原始数据缓存
		return false;
	}
	if(m_discardCurrentFrameCnt<m_discardFrameCnt)
	{
		m_discardCurrentFrameCnt++;
		ClearRawData();//装载一次，就必须清空原始数据缓存
		return false;		
	}

	//0x80是 10000,0000.这里为了得到BIT7位值,如果bit7位为1，表示第一个获取的字节是高位的字节，不用丢弃；
	//如果是0，表示第一个字节获取到了低位的，需要移位，丢弃第一个字节。
	discardFirstByte= (m_rawDataBuff[0]>>7)==0 ;

	int distance;
	int index=discardFirstByte?1:0;//获取偏移量，如果需要丢掉第一个字节，则偏移量为1。
	int i=0;
	int dataCnt=0;
	int data[1440];
	int buffSize=m_rawDataBuff.size();

	while(i<(buffSize-2))//要去掉最后两个字节结束标志
	{
		if(i<index)
		{
			i++;
			continue;		//直接移动到数据段取数据
		}
		if( (m_rawDataBuff[i+1] >> 7 ) == 1 )//如果低字节的bit7为1，表示是获取到了阶段标志的255，这个时候跳出循环即可
			break;

		distance=GetDistance(m_rawDataBuff[i],m_rawDataBuff[i+1]);
		data[dataCnt]=distance;
		//存入文件
		if(m_saveRawData)
		{
			fprintf(m_pFile,"%d\n",distance);
		}
		i+=2;
		dataCnt++;
	}
	//最大从0，180度
	if(m_startAngle<0)
		m_startAngle=0;
	if(m_stopAngle>900)
		m_stopAngle=900;
	if(m_stopAngle<=m_startAngle)
	{
		m_startAngle=0;
		m_stopAngle=900;
	}
	
	int length=dataCnt;
	double angleResolution=180/((double)length);

	int startDataNumber=(m_startAngle-0)*0.2/angleResolution;//获取起始角在data数组中的距离值序号
	int stopDataNumber=(m_stopAngle-0)*0.2/angleResolution;//获取结束角在data数组中的距离值序号

	
	pData->dataLength=stopDataNumber-startDataNumber;
	pData->startAngle=m_startAngle;
	pData->stopAngle=m_stopAngle;
	
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	pData->time=stime;
	
	int k=0;
	for(i=0;i<length;i++)
	{
		if(i<startDataNumber)
			continue;
		if(i>=stopDataNumber)
			break;

		pData->data[k]=data[i];
		k++;
	}
	
	ClearRawData();//装载一次，就必须清空原始数据缓存
	return true;
}
int CTcpRadarComm::GetDistance(unsigned char highByte,unsigned char lowByte)
{

	int distance=0;
	distance=((highByte & 0x3f ) << 7 ) | (lowByte & 0x7f);
	distance=distance*10;
	//if(distance==3250||distance>m_validDistance)
	//	distance=m_validDistance;
	return distance;
}
void CTcpRadarComm::ClearRawData()
{
	std::vector<unsigned char>::iterator theIt;
	for(theIt = m_rawDataBuff.begin(); theIt != m_rawDataBuff.end(); ++theIt)
	{
		m_rawDataBuff.erase(theIt);
		theIt--; 
	}
	
}



