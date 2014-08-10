/*****************************************************************
*文件名：			inisec.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2010-1-19			
*
*说明
	INI文件中各字段，各参数名称
******************************************************************/

#ifndef _RADARAPPINISEC_H_
#define _RADARAPPINISEC_H_

/*****************INI段名定义*************************/

#define INI_SEC_SYS						"system"							//系统段
#define INI_SEC_RADAR					"radar"								//雷达配置段
#define INI_SEC_ALG						"algorithm"							//算法配置段


/*****************INI参数名定义*************************/

//系统部分
#define INI_P_SYS_PWD							"pwd"						//密码
#define INI_P_SYS_ANSWERALARM					"answerAlarm"				//是否响应报警
#define INI_P_SYS_SOUNDALARM					"soundAlarm"				//是否开启声音报警
#define INI_P_SYS_ALARMSHOWCNT					"alarmshowcnt"				//报警记录显示个数


//雷达部分
#define INI_P_RADAR_PRODUCT						"product"					//雷达产品
#define INI_P_RADAR_BITRATE						"bitrate"					//波特率
#define INI_P_RADAR_COMPORT						"comport"					//com口
#define INI_P_RADAR_STARTANGLE					"startangle"				//起始角（0.2单位）
#define INI_P_RADAR_STOPANGLE					"stopangle"					//结束角
#define INI_P_RADAR_IPADDR						"ipaddr"					//ip地址
#define INI_P_RADAR_IPPORT						"ipport"					//ip端口
#define INI_P_RADAR_MOTORRATE					"motorRate"					//马达转速
#define INI_P_RADAR_SAVERAWDATA					"saveRawData"				//是否保存原始数据
#define INI_P_RADAR_RAWDATAFILE					"rawDataFile"				//原始数据存放路径
#define INI_P_RADAR_VALIDDISTANCE				"validDistance"				//有效距离

//算法部分
#define INI_P_ALG_BKGRDOFFSET					"bkgrdOffset"				//算法设置--背景偏移量（单位：毫米）
#define INI_P_ALG_BLDMAPPERIOD					"bldmapPeriod"				//算法设置--背景地图的建立周期
#define INI_P_ALG_CHKWIDTHTHRESHOLD				"chkWidthThreshold"			//算法设置--目标过滤宽度阈值（单位：毫米）
#define INI_P_ALG_FUSHIONSTEPNUM				"fushionStepNum"			//算法设置--融合步数
#define INI_P_ALG_SAMEOBLENGTH					"sameobLength"				//算法设置--判断为同一目标的长度阈值（单位：毫米）
#define INI_P_ALG_FUSHIONTIME					"fushionTime"				//算法设置--融合时间间隔（单位：毫秒）
#define INI_P_ALG_RADARTYPE						"radarType"					//算法设置--雷达类型



#endif