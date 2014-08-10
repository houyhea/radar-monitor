/*****************************************************************
*文件名：			struct.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2009-12-29			
*
*说明
	激光雷达整个工程的公共数据结构头文件。有多个工程包含该文件。把所有
	结构体放在统一一个头文件里的原因是防止重复定义错误发生。
******************************************************************/


#include "windows.h"
#ifndef _RADARSTRUCT_H_
#define _RADARSTRUCT_H_

//原始数据结构体
typedef struct _DataFrame
{
    SYSTEMTIME time;					//获取到本数据帧的时间
    long startAngle,stopAngle;			//开始角度和停止角度,单位长度是0.2度，比如startAngle=22,表示22*0.2=4.4度
    int dataLength;						//数据实际长度
    int data[1440];						//存放数据,单位毫米（mm）
}DataFrame;

//算法配置信息结构体
struct AlgorithmConfigInfo
{
    int bkgrdOffset;					//背景偏移量（单位：毫米）
    int sameobLength;					//判断为同一目标的长度阈值（单位：毫米）
    int chkWidthThreshold;				//目标过滤宽度阈值（单位：毫米）
    int fushionStepNum;					//融合步数
    int fushionTime;					//融合时间间隔（单位：毫秒）
    int bldmapPeriod;					//背景地图的建立周期
	int radarType;						//雷达类型
};

//地图结构体
struct BkgrdMap
{
    BOOL bReady;						//表征地图是否准备好了，最初置为FALSE
    SYSTEMTIME time;					//当前地图的建立时间
    long startAngle,stopAngle;			//开始角度和结束角度(1表示0.2度)
    int mapDataLength;					//地图数据的实际长度
    int data[1440];						//存储地图数据，单位为毫米
};

//报警目标结构体
struct WaringObject
{
    int angle,distance;					//目标中心点的直角坐标（单位：毫米）
    int objWidth;						//目标宽度（单位：毫米）
};

//报警结果结构体
struct WarningResult
{
    SYSTEMTIME time;					//本次结果的时间
	int objNum;							//检测到的目标数
    WaringObject obj[1000];				//存储报警目标
};


//雷达产品类型枚举
typedef enum _EnumRadar
{
    SCIP=0,				
	LeuzeSocket,				//劳易测socket
	LeuzeCom,					//劳易测COM
	CustomTcpRadar,				//定制的TCP的雷达
}EnumRadar;

//雷达配置信息结构体
typedef struct _HardConfigInfo			//雷达硬件设备配置信息结构体
{
	EnumRadar radar;					//雷达产品	
    int BitRate;						//数据传送比特率
    int motorRate;						//马达转速，单位为Hz
    long startAngle,stopAngle;			//扫描的开始角度和终止角度，单位为度
	char comDevice[50];					//雷达COM口
	char ip[50];						//雷达IP
	int  port;							//雷达端口
	bool saveRawData;					//是否保存原始数据
	char rawDataFile[500];				//原始数据存放路径
	int	 validDistance;					//有效距离
}HardConfigInfo;

//雷达相关信息结构体
typedef struct _RadarInfo				//雷达信息结构体
{
    BYTE radarType;						//雷达类型
    BYTE radarID;						//雷达编号
}RadarInfo;

//雷达地图显示控件状态
typedef enum _RadarMapState
{
	RDReadyScan=0,						//待扫描
	RDStudying,							//学习中
	RDScanning,							//学习完毕，扫描中
	RDPlayBack,							//数据回放
}RadarMapState;
#endif