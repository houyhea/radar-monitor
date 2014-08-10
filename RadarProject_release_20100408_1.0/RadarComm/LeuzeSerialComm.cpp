// LeuzeSerialComm.cpp: implementation of the CLeuzeSerialComm class.
//
//////////////////////////////////////////////////////////////////////

#include "LeuzeSerialComm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLeuzeSerialComm::CLeuzeSerialComm()
{
	findStartTag=false;
	findStopTag=false;
	ReSetTagBuffer();
	m_pFile=NULL;
}

CLeuzeSerialComm::~CLeuzeSerialComm()
{

}


void CLeuzeSerialComm::SetTagBuffer(unsigned char tag)
{
	if(tagBufferNumber==3)
	{
		tagBuffer[0]=tagBuffer[1];
		tagBuffer[1]=tagBuffer[2];
		tagBufferNumber=2;
	}
	tagBuffer[tagBufferNumber]=tag;
	tagBufferNumber++;
}
void CLeuzeSerialComm::ReSetTagBuffer()
{
	tagBuffer[0]=0xff;
	tagBuffer[1]=0xff;
	tagBuffer[2]=0xff;

	tagBufferNumber=0;
}

int  CLeuzeSerialComm::StartRadar(void)
{
	
	hCom=CreateFile(m_comDevice,//COM口
		GENERIC_READ|GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);
	if(hCom==(HANDLE)-1)
	{
		return -1;
	}

	SetupComm(hCom,1000,1000); //输入缓冲区和输出缓冲区的大小都是1000

	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=100;
	TimeOuts.ReadTotalTimeoutConstant=500;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。


	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts); //设置超时

	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate=m_bitRate; //波特率
	dcb.ByteSize=8; //每个字节有8位
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=TWOSTOPBITS; //两个停止位
	SetCommState(hCom,&dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

	
	//发送命令
	char buf[5];
	buf[0]=0x02;
	buf[1]='S';
	buf[2]='B';
	buf[3]='+';
	buf[4]=0x03;

	DWORD dwBytesWrite=5;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,buf,dwBytesWrite,& dwBytesWrite,NULL);

	return 1;
	
	
}
int	 CLeuzeSerialComm::CloseRadar(void)
{
	//发送命令
	char buf[5];
	buf[0]=0x02;
	buf[1]='S';
	buf[2]='B';
	buf[3]='-';
	buf[4]=0x03;

	DWORD dwBytesWrite=5;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,buf,dwBytesWrite,& dwBytesWrite,NULL);

	return CloseHandle(hCom)?1:-1;
}

bool CLeuzeSerialComm::GetRawData(DataFrame * pData)
{
	char recvBuf[60];
	
	DWORD wCount;//读取的字节数
	BOOL bReadStat;
	bReadStat=ReadFile(hCom,recvBuf,60,&wCount,NULL);
	if(!bReadStat)
	{
		return false;
	}
	if(wCount<=0)
		return false;
	return ProcessData(recvBuf,wCount, pData);
}
bool CLeuzeSerialComm::CheckStartTag()
{
	if(tagBufferNumber!=3)
		return false;

	if(tagBuffer[0]==0x00
		&& tagBuffer[1]==0x00
		&& tagBuffer[2]!=0xff
		&& tagBuffer[2]!=0x00)
	{
		return true;
	}
	else
		return false;
	
	
}
bool CLeuzeSerialComm::CheckStopTag()
{
	if(tagBufferNumber!=3)
		return false;

	if(tagBuffer[0]==0x00
		&& tagBuffer[1]==0x00
		&& tagBuffer[2]==0x00)
	{
		return true;
	}
	else
		return false;
}
bool CLeuzeSerialComm::ProcessData(char * recvBuf,int size,DataFrame * pData)
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
		if(CheckStartTag())
		{
			findStartTag=true;
			m_rawDataBuff.push_back(byte);//注意，这里保存下来的rawdatabuff始终没有起始标志（两个字节，0x00,0x00）
			ReSetTagBuffer();
			continue;
		}
		if(findStartTag)
		{
			m_rawDataBuff.push_back(byte);
			if(CheckStopTag())
			{
				findStopTag=true;					
				rettag=LoadData(pData);				//处理数据，填充原始数据
				//存入文件,结束标志
				if(m_saveRawData)
				{
					fprintf(m_pFile,"-1\n");
				}

				findStartTag=false;					//找到结束标志后，又需要找起始标志了
				ReSetTagBuffer();
				continue;
			}
			
		}
	}
	return rettag;
}
bool CLeuzeSerialComm::LoadData(DataFrame *pData)
{
	if(m_rawDataBuff.size()==0)
	{
		ClearRawData();//装载一次，就必须清空原始数据缓存
		return false;
	}
	if(m_rawDataBuff.size()>2000)
	{
		ClearRawData();//装载一次，就必须清空原始数据缓存
		return false;
		
	}
	/////////////////测试
	/*
	int sizes=m_rawDataBuff.size();
	unsigned char zydata[2000];
	for(int zy=0;zy<sizes;zy++)
	{
		zydata[zy]=m_rawDataBuff[zy];
	}
	*/
	/////////////////测试

	//检查校验和
	if(!CheckSum())
	{
		ClearRawData();//装载一次，就必须清空原始数据缓存
		return false;
	}
	//检查operation字节
	if(!CheckOperation())
	{
		ClearRawData();//装载一次，就必须清空原始数据缓存
		return false;		
	}
	int distance;
	int index=GetDataOffset();//获取距离数据在buffer中的偏移量
	int i=0;
	int dataCnt=0;

	int data[600],okData[600];//由于劳易测的角度是顺时针旋转的，跟我们定义的相反，所以需要调过来

	while(i<m_rawDataBuff.size()-4)//要去掉最后一个字节checksum和三个字节结束标志
	{
		if(i<index)
		{
			i++;
			continue;		//直接移动到数据段取数据
		}
		distance=GetDistance(m_rawDataBuff[i],m_rawDataBuff[i+1]);
		
		if(m_rawDataBuff[i]==0x00
			&& m_rawDataBuff[i+1]==0x00)
		{
			i+=3;		//去掉多加进来的0XFF
		}
		else
		{
			i+=2;
		}
		if(dataCnt>=600)//根据劳易测的协议，不可能大于600个距离数据。
		{
			ClearRawData();//装载一次，就必须清空原始数据缓存
			return false;
		}
		data[dataCnt]=distance;
		dataCnt++;
	}
	for(i=0;i<dataCnt;i++)
	{
		okData[i]=data[dataCnt-1-i];
	}
	pData->dataLength=dataCnt;
	
	//最大从-5.04，185.04度,即(-25,925),0.2表示
	if(m_startAngle<-25)
		m_startAngle=-25;
	if(m_stopAngle>925)
		m_stopAngle=925;
	if(m_stopAngle<=m_startAngle)
	{
		m_startAngle=-25;
		m_stopAngle=925;
	}	
	
	double angleResolution=GetAngularResolution()*0.36;//解析度单位是度，0.36是劳易测的单位解析度，解析度都是它的倍数

	int startDataNumber=(1+m_startAngle-(-25))*0.2/angleResolution;//获取起始角在data数组中的距离值序号,加1的原因是：劳易测的-25，即-5.04，是1，而不是0
	int stopDataNumber=(m_stopAngle-(-25))*0.2/angleResolution;//获取结束角在data数组中的距离值序号


	pData->dataLength=stopDataNumber-startDataNumber+1;
	pData->startAngle=m_startAngle;
	pData->stopAngle=m_stopAngle;
	SYSTEMTIME time;
	GetLocalTime(&time);

	pData->time=time;

	int k=0;
	for(i=0;i<dataCnt;i++)
	{
		if(i<startDataNumber)
			continue;
		if(i>=stopDataNumber)
			break;

		pData->data[k]=okData[i];
		//存入文件
		if(m_saveRawData)
		{
			fprintf(m_pFile,"%d\n",okData[i]);
		}
		
		k++;
	}
	ClearRawData();//装载一次，就必须清空原始数据缓存
	return true;
}
bool CLeuzeSerialComm::CheckOperation()
{
	return m_rawDataBuff[0]==0x23;
}
//检查校验和，从operation字节到checksum的前一个字节，进行异或操作
bool CLeuzeSerialComm::CheckSum()
{
	unsigned char tag=m_rawDataBuff[0];
	int sizes=m_rawDataBuff.size();
	for(int i=1;i<(sizes-4);i++)
	{
		tag^=m_rawDataBuff[i];
	}
	if(tag==0x00)tag=0xff;
	unsigned char checkSum=m_rawDataBuff[sizes-4];
	return tag==checkSum;
}
//获取angular resolution
int CLeuzeSerialComm::GetAngularResolution()
{
	int optionBytes=GetOptionByteNum();
	return m_rawDataBuff[1+optionBytes+8];
}
//解析一个协议包数据的时候，获取协议中距离数据从start字节到距离数据的偏移量
int CLeuzeSerialComm::GetDataOffset()
{
	//m_rawDataBuff里没有存起始两个字节标志
	int offset=0;
	if(m_rawDataBuff.size()<19)//距离数据前面的字节数最多是19个
		return offset;
	
	int startAngleIndex,stopAngleIndex;
	int optionByteNum=GetOptionByteNum();//option字节数
	
	startAngleIndex=1+optionByteNum+8+1;
	offset=startAngleIndex;
	if(m_rawDataBuff[startAngleIndex]==0x00		//15是起始角高位字节的偏移位置
	&& m_rawDataBuff[startAngleIndex+1]==0x00)		
	{
		offset+=3;
		stopAngleIndex=startAngleIndex+3;
	}
	else
	{
		offset+=2;
		stopAngleIndex=startAngleIndex=2;
	}
	if(m_rawDataBuff[stopAngleIndex]==0x00		//17是结束角高位字节的偏移位置
	&& m_rawDataBuff[stopAngleIndex=1]==0x00)		
	{
		offset+=3;
	}
	else
	{
		offset+=2;
	}
	return offset;

}
//计算option字节数，包括option1，2，3
int CLeuzeSerialComm::GetOptionByteNum()
{
	//option 1+2+3
	if((m_rawDataBuff[1] & 3) > 0)
	{
		return 3;
	}
	//option 1+2
	else if((m_rawDataBuff[1] & 2) > 0)
	{
		return 2;
	}
	//option 1
	else if((m_rawDataBuff[1] & 1) > 0)
	{
		return 1;
	}
	return 3;
}
int CLeuzeSerialComm::GetDistance(unsigned char highByte,unsigned char lowByte)
{
	int distance=0;
	distance=(highByte<<8) | (lowByte & 0xFE);//屏蔽掉低字节的bit0位。
	return distance;
}

void CLeuzeSerialComm::ClearRawData()
{
	std::vector<unsigned char>::iterator theIt;
	for(theIt = m_rawDataBuff.begin(); theIt != m_rawDataBuff.end(); ++theIt)
	{
		m_rawDataBuff.erase(theIt);
		theIt--; 
	}
	
}
