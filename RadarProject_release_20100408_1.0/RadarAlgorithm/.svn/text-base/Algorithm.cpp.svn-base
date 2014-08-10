// Algorithm.cpp: implementation of the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#include "Algorithm.h"
#include <ctime>  //随机数部分
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlgorithm::CAlgorithm()
{
	m_TemporaryState=0;
}

CAlgorithm::~CAlgorithm()
{

}


BOOL CAlgorithm::Initial( AlgorithmConfigInfo &cfgInfo)
{
	memset(&m_FinalResult,0,sizeof(WarningResult));
	memset(&m_MidResult,0,sizeof(WarningResult));
	memset(&m_Map,0,sizeof(WarningResult));

	//内部变量初始化
	memcpy(&m_CfgInfo,&cfgInfo,sizeof(AlgorithmConfigInfo));
	memset(&m_DataFrameQueue,0,sizeof(DataFrameQueue));
	memset(&m_FogrdPntSet,0,sizeof(ForegroundPointSet));
	m_bHaveStdDataLength=FALSE;

	return TRUE;
}

DWORD CAlgorithm::GetResult(DataFrame &frm)
{
	switch(m_CfgInfo.radarType)
	{
	//日本HOKUYO雷达
	case SCIP:
		return GetHokuyoResult(frm);
		break;

	//劳易测socket
	case LeuzeSocket:
		return GetLeuzeResult(frm);
		break;

	//劳易测COM
	case LeuzeCom:
		return GetLeuzeResult(frm);
		break;

	//定制TCP简易雷达
	case CustomTcpRadar:
		return GetTCPResult(frm);
		break;

	default:
		return 0;
		break;
	
	}

}


DWORD CAlgorithm::GetHokuyoResult(DataFrame &frm)
{	
		DWORD result=0;
		
		//将原始数据帧输入到数据缓存队列中
		InputData(frm);
		
		//获取标准数据长度
		if( (!m_bHaveStdDataLength)&&(m_DataFrameQueue.curFrameNum<3) )
		{
			return result;
		}
		else if( (!m_bHaveStdDataLength)&&(m_DataFrameQueue.curFrameNum==3) )
		{
			m_nStdDataLength=( m_DataFrameQueue.frame[0].dataLength + 
				m_DataFrameQueue.frame[1].dataLength + 
				m_DataFrameQueue.frame[2].dataLength )/3;
			m_bHaveStdDataLength=TRUE;
			
			//确定起始角度和角度步进（单位：弧度）
			m_fStartAngle=0.2*((double)(m_pCurDataFrame->startAngle))*PI/180;
			m_fStopAngle=0.2*((double)(m_pCurDataFrame->stopAngle))*PI/180;
			m_fAngleStep=(m_fStopAngle-m_fStartAngle)/(m_nStdDataLength-1);
			
			//清除
			ClearQueue();
		}
		
		//预处理当前帧，预处理失败则等待下次
		if(!PreProcess())
			return result;
		
		//检查是否需要建立地图
		if(!m_Map.bReady||((GetMapPeriod()>=m_CfgInfo.bldmapPeriod)&&(m_CfgInfo.bldmapPeriod!=0)))
		{
			result+=BuildMap();
		}
		//否则执行检测算法
		else
		{
			result+=GetWarningResult();
		}
		
		return result;

}

//获取Leuze雷达结果
DWORD CAlgorithm::GetLeuzeResult(DataFrame &frm)
{	
		DWORD result=0;
		
		//将原始数据帧输入到数据缓存队列中
		InputData(frm);
		
		//获取标准数据长度
		if( (!m_bHaveStdDataLength)&&(m_DataFrameQueue.curFrameNum<3) )
		{
			return result;
		}
		else if( (!m_bHaveStdDataLength)&&(m_DataFrameQueue.curFrameNum==3) )
		{
			m_nStdDataLength=( m_DataFrameQueue.frame[0].dataLength + 
				m_DataFrameQueue.frame[1].dataLength + 
				m_DataFrameQueue.frame[2].dataLength )/3;
			m_bHaveStdDataLength=TRUE;
			
			//确定起始角度和角度步进（单位：弧度）
			m_fStartAngle=0.2*((double)(m_pCurDataFrame->startAngle))*PI/180;
			m_fStopAngle=0.2*((double)(m_pCurDataFrame->stopAngle))*PI/180;
			m_fAngleStep=(m_fStopAngle-m_fStartAngle)/(m_nStdDataLength-1);
			
			//清除
			ClearQueue();
		}
		
		//预处理当前帧，预处理失败则等待下次
		if(!PreProcess())
			return result;
		
		//检查是否需要建立地图
		if(!m_Map.bReady||((GetMapPeriod()>=m_CfgInfo.bldmapPeriod)&&(m_CfgInfo.bldmapPeriod!=0)))
		{
			result+=BuildMap();
		}
		//否则执行检测算法
		else
		{
			result+=GetWarningResult();
		}
		
		return result;

}

//获取自制TCP雷达结果
DWORD CAlgorithm::GetTCPResult(DataFrame &frm)
{	
		DWORD result=0;
		
		//将原始数据帧输入到数据缓存队列中
		InputData(frm);
		
		//获取标准数据长度
		if( (!m_bHaveStdDataLength)&&(m_DataFrameQueue.curFrameNum<5) )
		{
			return result;
		}
		else if( (!m_bHaveStdDataLength)&&(m_DataFrameQueue.curFrameNum==5) )
		{
			//取这若干帧中的dataLength最大值作为标准长度
			m_nStdDataLength = 0;
			for(int i=0;i<5;i++)
			{
				if(m_DataFrameQueue.frame[i].dataLength>m_nStdDataLength)
				{
					m_nStdDataLength = m_DataFrameQueue.frame[i].dataLength;
				}
			}
			m_bHaveStdDataLength = TRUE;
			
			//确定起始角度和角度步进（单位：弧度）
			m_fStartAngle=0.2*((double)(m_pCurDataFrame->startAngle))*PI/180;
			m_fStopAngle=0.2*((double)(m_pCurDataFrame->stopAngle))*PI/180;
			m_fAngleStep=(m_fStopAngle-m_fStartAngle)/(m_nStdDataLength-1);
			
			//清除
			ClearQueue();
		}
		
		//预处理当前帧，预处理失败则等待下次
		if(!PreProcessTCP())
			return result;
		
		//检查是否需要建立地图
		if(!m_Map.bReady||((GetMapPeriod()>=m_CfgInfo.bldmapPeriod)&&(m_CfgInfo.bldmapPeriod!=0)))
		{
			result+=BuildMap();
		}
		//否则执行检测算法
		else
		{
			result+=GetTCPWarningResult();
		}
		
		return result;

}

void  CAlgorithm::ResetState(BYTE state)
{
	//m_TemporaryState=0;
}

//将原始数据添加进数据帧队列中
void CAlgorithm::InputData(DataFrame frm)
{
	int length;

	//如果队列已满
	if(m_DataFrameQueue.curFrameNum>=MAX_FRAME_NUM)
	{
		//清出队列前若干帧
		OutQueue(10);
	}
	
	length=m_DataFrameQueue.curFrameNum;
	memcpy( &(m_DataFrameQueue.frame[length]),&frm,sizeof(DataFrame) );
	m_DataFrameQueue.curFrameNum++;

	m_pCurDataFrame=&(m_DataFrameQueue.frame[length]);
	
}

//清出数据帧队列中的前若干帧
void CAlgorithm::OutQueue(int num)
{
	int i;

	for(i=num;i<MAX_FRAME_NUM;i++)
	{
		memcpy( &(m_DataFrameQueue.frame[i-num]),&(m_DataFrameQueue.frame[i]),sizeof(DataFrame) );	
	}

	m_DataFrameQueue.curFrameNum-=num;
}

//预处理数据帧队列中的当前帧，result的bit0为1代表处理成功
DWORD CAlgorithm::PreProcess()
{
	DWORD result=0;
	int len,temp;
	int buf[MAX_DATA_LENGTH];

	//如原始帧队列为空，则返回
	if(m_DataFrameQueue.curFrameNum==0)
		return result;

	//检查当前帧长度，如相差太远，则丢弃当前帧
	if(m_pCurDataFrame->dataLength != m_nStdDataLength)
	{
		len = m_pCurDataFrame->dataLength;
		//相差太远，丢弃
		temp=len-m_nStdDataLength;
		temp = temp>=0?temp:-temp;
		if( ((double)temp/m_nStdDataLength)>0.05 )
		{
			m_DataFrameQueue.curFrameNum--;
			m_pCurDataFrame=&(m_DataFrameQueue.frame[m_DataFrameQueue.curFrameNum-1]);
			return result;
		}
		  //相差可容忍，进行数据变换
		else
		{
			memcpy(buf,m_pCurDataFrame->data,len*sizeof(int));
			TransformData(m_pCurDataFrame->data,m_nStdDataLength,buf,len);
			m_pCurDataFrame->dataLength=m_nStdDataLength;
		}
	}

	result = 1;

	return result;
}

//预处理数据帧队列中的当前帧，result的bit0为1代表处理成功，针对定制TCP雷达
DWORD CAlgorithm::PreProcessTCP()
{
	DWORD result=0;
	int len,temp,i;
	int buf[MAX_DATA_LENGTH];

	//如原始帧队列为空，则返回
	if(m_DataFrameQueue.curFrameNum==0)
		return result;

	//检查当前帧长度，如相差太远，则丢弃当前帧
	if(m_pCurDataFrame->dataLength != m_nStdDataLength)
	{
		len = m_pCurDataFrame->dataLength;
		//相差太远，丢弃
		temp=len-m_nStdDataLength;
		temp = temp>=0?temp:-temp;
		if( ((double)temp/m_nStdDataLength)>0.3 )
		{
			m_DataFrameQueue.curFrameNum--;
			m_pCurDataFrame=&(m_DataFrameQueue.frame[m_DataFrameQueue.curFrameNum-1]);
			return result;
		}
		  //相差可容忍，进行数据变换
		else
		{
			//如果比标准的短，补齐
			/*if(m_pCurDataFrame->dataLength<m_nStdDataLength)
			{
				memset( &(m_pCurDataFrame->data[m_pCurDataFrame->dataLength]),0,sizeof(int)*temp );
			}*/

			//归一化为标准长度
			m_pCurDataFrame->dataLength=m_nStdDataLength;
		}
	}

	//进行3250转换
	int endIndex = m_nStdDataLength-OMIT_POINT_NUM_TCP;
	for(i=OMIT_POINT_NUM_TCP;i<endIndex;i++)
	{
		if(m_pCurDataFrame->data[i]==3250)
			m_pCurDataFrame->data[i]==22000;
	}

	result = 1;

	return result;
}

//建立地图
DWORD CAlgorithm::BuildMap()
{
	DWORD result=0;
	int i,j,nFrameNum,temp,distance,err;

	//如果数据帧量不够，返回
	if(m_DataFrameQueue.curFrameNum<BLDMAP_FRAME_NUM)
		return result;

	nFrameNum=m_DataFrameQueue.curFrameNum;

	//建地图
	for(i=0;i<m_nStdDataLength;i++)
	{
		temp=0;
		for(j=nFrameNum-BLDMAP_FRAME_NUM;j<nFrameNum;j++)
		{
			temp+=m_DataFrameQueue.frame[j].data[i];
		}

		//求得背景值
		m_Map.data[i]=temp/nFrameNum;  

	}

	m_Map.mapDataLength=m_nStdDataLength;
	m_Map.startAngle=m_DataFrameQueue.frame[nFrameNum-1].startAngle;
	m_Map.stopAngle=m_DataFrameQueue.frame[nFrameNum-1].stopAngle;
	memcpy( &m_Map.time,&(m_DataFrameQueue.frame[nFrameNum-1].time),sizeof(SYSTEMTIME) );

	m_Map.bReady=TRUE;

	//将背景偏移量数组清0
	memset(m_BackOffset,0,sizeof(int)*MAX_DATA_LENGTH);
	//填充背景偏移量数组
	for(i=0;i<m_nStdDataLength;i++)
	{
		for(j=nFrameNum-BLDMAP_FRAME_NUM;j<nFrameNum;j++)
		{
			err=m_DataFrameQueue.frame[j].data[i]-m_Map.data[i];
			err=(err>=0?err:-err);
			if(err>m_BackOffset[i])
			{
				m_BackOffset[i] = err;
			}
		}
	}
	//进一步处理
	for(i=0;i<m_nStdDataLength;i++)
	{
		m_BackOffset[i]=m_BackOffset[i]*2;
	}

	result=1;

	return result;
}

//获取当前地图以存在了多久（单位为ms）
int CAlgorithm::GetMapPeriod()
{
	return 3;
}

//获取报警结果
DWORD CAlgorithm::GetWarningResult()
{
	DWORD result=0;

	//获取前景点
	GetPointSet2();

	//如未获得前景点，则可直接返回
	if(m_FogrdPntSet.pointNum==0)
		return result;

	//分割成多个目标
	SplitObject();

	//提取目标特征
	ExtractFeature();

	//根据特征分析判别报警与否
	AnalyzeJudge();

	//填充报警结果
	result+=GenerateResult();

	return result;
}

//获取报警结果，针对定制TCP雷达
DWORD CAlgorithm::GetTCPWarningResult()
{
	DWORD result=0;

	//获取前景点
	GetPointSetTCP();

	//如未获得前景点，则可直接返回
	if(m_FogrdPntSet.pointNum==0)
		return result;

	//分割成多个目标
	SplitObject();

	//提取目标特征
	ExtractFeature();

	//根据特征分析判别报警与否
	AnalyzeJudge();

	//填充报警结果
	result+=GenerateResult();

	return result;
}

//获取报警结果，方法2
/*DWORD CAlgorithm::GetWarningResult2()
{
	DWORD result=0;

	//获取前景点
	GetPointSet();

	//如未获得前景点，则可直接返回
	if(m_FogrdPntSet.pointNum==0)
		return result;

	//分割成多个目标
	SplitObject();

	//提取目标特征
	ExtractFeature();

	//根据特征分析判别报警与否
	AnalyzeJudge();

	//填充报警结果
	result+=GenerateResult();

	return result;
}*/

//获取前景点
void CAlgorithm::GetPointSet()
{
	int i,distance;
	int foredistance,bkdistance;
	double angle;

	//清空前景点空间
	m_FogrdPntSet.pointNum=0;

	for(i=OMIT_POINT_NUM;i<m_nStdDataLength-OMIT_POINT_NUM;i++)
	{

		foredistance=m_pCurDataFrame->data[i];
		//比较本点
		bkdistance=m_Map.data[i];
		distance=bkdistance-foredistance;

		//产生前景点
		if(distance>m_CfgInfo.bkgrdOffset)
		{
			//比较前点
			bkdistance=m_Map.data[i-1];
			distance=bkdistance-foredistance;

			if(distance>m_CfgInfo.bkgrdOffset)
			{
				//比较后点
				bkdistance=m_Map.data[i+1];
				distance=bkdistance-foredistance;

				if(distance>m_CfgInfo.bkgrdOffset)
				{
					//获取角度
					angle=m_fStartAngle+m_fAngleStep*i;

					//填充前景点
					m_FogrdPntSet.point[m_FogrdPntSet.pointNum].x=(double)foredistance*cos(angle);
					m_FogrdPntSet.point[m_FogrdPntSet.pointNum].y=(double)foredistance*sin(angle);
					m_FogrdPntSet.pointNum++;
				}
			}
		}
	}
}

//获取前景点，采用自适应的背景偏移量方法
void CAlgorithm::GetPointSet2()
{
	int i,distance;
	int foredistance,bkdistance;
	double angle;

	//清空前景点空间
	m_FogrdPntSet.pointNum=0;

	for(i=OMIT_POINT_NUM;i<m_nStdDataLength-OMIT_POINT_NUM;i++)
	{

		foredistance=m_pCurDataFrame->data[i];
		//比较本点
		bkdistance=m_Map.data[i];
		distance=bkdistance-foredistance;

		//产生前景点
		if(distance>m_BackOffset[i] && distance>m_CfgInfo.bkgrdOffset)
		{
			//获取角度
			angle=m_fStartAngle+m_fAngleStep*i;

			//填充前景点
			m_FogrdPntSet.point[m_FogrdPntSet.pointNum].x=(double)foredistance*cos(angle);
			m_FogrdPntSet.point[m_FogrdPntSet.pointNum].y=(double)foredistance*sin(angle);
			m_FogrdPntSet.pointNum++;
		}
	}
}

//获取前景点，采用自适应的背景偏移量方法，针对定制TCP雷达
void CAlgorithm::GetPointSetTCP()
{
	int i,distance;
	int foredistance,bkdistance;
	double angle;

	//清空前景点空间
	m_FogrdPntSet.pointNum=0;

	//背景阈值
	int bkOff = m_CfgInfo.bkgrdOffset;

	//int endIndex = m_nStdDataLength-OMIT_POINT_NUM_TCP;
	int endIndex = m_nStdDataLength;
	for(i=OMIT_POINT_NUM_TCP;i<endIndex;i++)
	{

		foredistance=m_pCurDataFrame->data[i];
		//比较本点
		bkdistance=m_Map.data[i];
		distance=bkdistance-foredistance;

		//产生前景点
		if(distance>m_BackOffset[i] && distance>bkOff)
		{
			//获取角度
			angle=m_fStartAngle+m_fAngleStep*i;

			//填充前景点
			m_FogrdPntSet.point[m_FogrdPntSet.pointNum].x=(double)foredistance*cos(angle);
			m_FogrdPntSet.point[m_FogrdPntSet.pointNum].y=(double)foredistance*sin(angle);
			m_FogrdPntSet.pointNum++;
		}
	}
}

//清空数据帧队列
void CAlgorithm::ClearQueue()
{
	m_DataFrameQueue.curFrameNum=0;
}

//从前景点分割出目标
void CAlgorithm::SplitObject()
{
	//如无前景点，则直接返回
	if(m_FogrdPntSet.pointNum==0)
		return;

	int i,distance,temp1,temp2;
	int pntNum=m_FogrdPntSet.pointNum;
	m_nSplitNum=0;

	for(i=1;i<pntNum;i++)
	{
		temp1=m_FogrdPntSet.point[i].x-m_FogrdPntSet.point[i-1].x; 
		temp1=temp1*temp1;
		temp2=m_FogrdPntSet.point[i].y-m_FogrdPntSet.point[i-1].y; 
		temp2=temp2*temp2;

		distance=sqrt(temp1+temp2);

		//生成分割
		if(distance>m_CfgInfo.sameobLength)
		{
			m_nSplitIndex[m_nSplitNum]=i-1;
			m_nSplitNum++;
		}

		//最后一点一定为分割索引
		if(i==pntNum-1)
		{
			m_nSplitIndex[m_nSplitNum]=i;
			m_nSplitNum++;
		}
	}
}

//检测目标 
void CAlgorithm::DetectObject()
{
	int i;

	for(i=0;i<m_nSplitNum;i++)
	{
	}
}

//提取目标特征
void CAlgorithm::ExtractFeature()
{
	int index1,index2;

	for(int i=0;i<m_nSplitNum;i++)
	{
		if(i==0)
		{
			index1=0;
			index2=m_nSplitIndex[0];
		}
		else
		{
			index1=m_nSplitIndex[i-1]+1;
			index2=m_nSplitIndex[i];
		}

		m_FeatureSet.segFeature[i].width=CmptDistance(
			m_FogrdPntSet.point[index1],m_FogrdPntSet.point[index2]);
	}

	m_FeatureSet.segNumber=m_nSplitNum;
}

//计算两点间距离的全局函数
double CmptDistance(POINT pt1, POINT pt2)
{
	long temp1,temp2;
	double distance;

	temp1=pt1.x-pt2.x; 
	temp1=temp1*temp1;
	temp2=pt1.y-pt2.y; 
	temp2=temp2*temp2;

	distance=sqrt(temp1+temp2);

	return distance;
}

//进行数据插值转换的全局函数
void TransformData(int *pDest,int nDestLength,int *pSource,int nSourceLength)
{
	int way=0;
	int i;

	switch(way)
	{
	//方法0，简单的处理
	case 0:
		memcpy(pDest,pSource,sizeof(int)*nDestLength);

		if(nSourceLength < nDestLength)
		{
			for(i=nSourceLength;i<nDestLength;i++)
			{
				pDest[i] = pSource[nSourceLength-1];
			}
		}

		break;
	}
}

//根据特征判别是否报警
void CAlgorithm::AnalyzeJudge()
{
	for(int i=0;i<m_nSplitNum;i++)
	{
		m_FeatureSet.segFeature[i].bWarning=FALSE;

		if(m_FeatureSet.segFeature[i].width>=m_CfgInfo.chkWidthThreshold)
		{
			m_FeatureSet.segFeature[i].bWarning=TRUE;
		}
	}
}
  
//产生报警结果   
DWORD CAlgorithm::GenerateResult()
{
	DWORD result=0;
	POINT pt,temp;
	int index1,index2;

	temp.x=0;temp.y=0;
	
	memcpy( &(m_FinalResult.time),&(m_pCurDataFrame->time),sizeof(SYSTEMTIME) );
	m_FinalResult.objNum=0;

	for(int i=0;(i<m_nSplitNum)&&(i<MAX_OBJECT_NUM);i++)
	{
		if(m_FeatureSet.segFeature[i].bWarning==TRUE)
		{
			result=4;

			if(i==0)
			{
				index1=0;
				index2=m_nSplitIndex[0];
			}
			else
			{
				index1=m_nSplitIndex[i-1]+1;
				index2=m_nSplitIndex[i];
			}

			//求取中值点坐标
			pt.x=( m_FogrdPntSet.point[index1].x+m_FogrdPntSet.point[index2].x )/2;
			pt.y=( m_FogrdPntSet.point[index1].y+m_FogrdPntSet.point[index2].y )/2;

			if(pt.x==0&&pt.y>=0)
			{
				m_FinalResult.obj[m_FinalResult.objNum].angle = 450;
			}
			else if(pt.x==0&&pt.y<0)
			{
				m_FinalResult.obj[m_FinalResult.objNum].angle = -450;
			}
			else if(pt.x>0)
			{
				m_FinalResult.obj[m_FinalResult.objNum].angle = atan((double)pt.y/(double)pt.x)*900/PI ;
			}
			else if(pt.x<0)
			{
				m_FinalResult.obj[m_FinalResult.objNum].angle = atan((double)pt.y/(double)pt.x)*900/PI+900 ;
			}

			//求取距离
			m_FinalResult.obj[m_FinalResult.objNum].distance=CmptDistance(temp,pt);

			//求取宽度
			m_FinalResult.obj[m_FinalResult.objNum].objWidth=m_FeatureSet.segFeature[i].width;

			m_FinalResult.objNum++;
		}
	}

	return result;
}