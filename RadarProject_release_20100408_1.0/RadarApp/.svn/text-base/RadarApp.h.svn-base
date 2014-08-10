/*****************************************************************
*文件名：			RadarApp.h
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
	激光雷达--应用程序层--应用程序APP类，用于提供UI层功能调用封装。单例模式。使用
	CRADAR_APP宏获取实例，必须在程序启动时调用一次Init方法初始化。
******************************************************************/

// RadarApp.h: interface for the CRadarApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARAPP_H__1087BE09_964D_442A_8C16_727F725938B9__INCLUDED_)
#define AFX_RADARAPP_H__1087BE09_964D_442A_8C16_727F725938B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Jthread.h"
#include "jmutex.h"
#include <windows.h>
#include "struct.h"


//自定义消息
#define WM_GETDATA		WM_USER+100			//数据获取成功消息
#define WM_GETMAP		WM_USER+101			//地图准备成功消息
#define WM_GETDATATIMEOUT		WM_USER+102			//获取数据超时


//错误标志枚举，有不同的错误，请加入到此枚举中
enum META_ERROR
{
	META_ERR_SUCCESS		=	 0,			//成功
	META_ERR_UNKNOWN		=	 -1,		//其它未知错误	
	META_ERR_RADAR_NOT_INT	=-2,		//雷达没有初始化
	META_ERR_RADAR_START_LOSE =-3,		//雷达启动失败
	META_ERR_MDB_INI		=-4,		//数据库初始化出错
	META_ERR_INI_NOT_FOUND  =-5,		//ini文件未创建
	META_ERR_PWD			=-6,		//密码错误
	META_ERR_COMM_INT		=-7,		//通信模块初始化错误
	META_ERR_RADAR_CONFIG	=-8,		//从INI文件配置雷达失败
	META_ERR_ALG_INI		=-9,		//初始化算法失败
};

class CRadarCommDll;
class CAlgorithm;
class CIniHelper;
class CDBHelper;

#ifdef RADARAPP_EXPORTS
class _declspec(dllexport) CRadarApp : public JThread    //导出类circle
#else
class _declspec(dllimport) CRadarApp : public JThread    //导入类circle
#endif
{
private:
	CRadarApp();
	CIniHelper * m_iniHelper;			//ini文件操作类	
	CDBHelper  * m_dbHelper;			//数据库操作类 
public:
	static CRadarApp* Instance();
	virtual ~CRadarApp();
	

	/**********************************************************************
		上位机一般功能操作接口
	
	**********************************************************************/

	/**	描述:检查口令
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	META_ERROR CheckPwd(char * pwd,int size);

	/**	描述:设置口令
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	META_ERROR ChangePwd(char * pwd,int size);

	/**	描述:设置响应报警
	 *	参数:
	 *		enableAlarm 是否响应报警，TRUE表示响应
	 *	返回值:
	 *		
	**/
	META_ERROR	SetAnswerAlarm(bool enableAlarm);
	/**	描述:获取响应报警
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	bool	GetAnswerAlarm(); 
	/**	描述:设置声音开关
	 *	参数:
	 *		enableSoundAlarm	是否开启声音，TRUE表示：开启
	 *	返回值:
	 *		
	**/
	META_ERROR	SetSoundAlarm(bool enableSoundAlarm);
	/**	描述:获取响应报警
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	bool	GetSoundAlarm(); 

	/**	描述:设置报警记录列表显示个数
	 *	参数:
	 *		cnt	报警记录显示个数
	 *	返回值:
	 *		
	**/
	META_ERROR	SetAlarmShwoCnt(int cnt);
	/**	描述:获取报警记录列表显示个数
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	int	GetAlarmShwoCnt(); 

	/**********************************************************************
		雷达控制部分接口
	
	**********************************************************************/

	/**	描述:初始化
	 *	参数:
	 *		hwnd:窗口句柄
	 *	返回值:
	 *		
	**/
	META_ERROR Init(HWND hwnd);

	/**	描述:开启雷达
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	META_ERROR StartRadar();

	/**	描述:停止雷达
	 *	参数:
	 *	
	 *	返回值:
	 *		
	**/
	META_ERROR StopRadar();

	/**********************************************************************
		雷达部分
	
	**********************************************************************/

	/**	描述:设置算法配置信息到INI文件
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	META_ERROR SetRadarConfig(HardConfigInfo* cfg);
	/**	描述:从INI读取算法配置信息
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	BOOL GetRadarConfig(HardConfigInfo * cfg);

	/**	描述:更新算法配置信息，从INI读取，然后设置算法对象的参数
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	BOOL UpdateRadarConfig();


	/**********************************************************************
		算法部分
	
	**********************************************************************/

	/**	描述:设置算法配置信息到INI文件
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	META_ERROR SetAlgConfig(AlgorithmConfigInfo* cfg);
	/**	描述:从INI读取算法配置信息
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	BOOL GetAlgConfig(AlgorithmConfigInfo * cfg);

	/**	描述:更新算法配置信息，从INI读取，然后设置算法对象的参数
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	BOOL UpdateAlgConfig();


	/**********************************************************************
		INI文件部分接口
	
	**********************************************************************/
	/**	描述:读取INI文件键值
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	BOOL ReadIniFile(
			LPCSTR lpAppName,				/*节点名称*/
			LPCSTR lpKeyName,				/*键*/
			LPCSTR lpDefault,				/*默认值。=NULL*/
			LPSTR lpReturnedString,		/*返回键值*/
			DWORD nSize					/*返回键值尺寸*/
		);
	/**	描述:写入INI文件
	 *	参数:
	 *		
	 *	返回值:
	 *		
	**/
	BOOL WriteIniFile(
			LPCSTR lpAppName,				/*节点名称*/
			LPCSTR lpKeyName,				/*键*/
			LPCSTR lpString				/*键值*/
    );


public:
	HWND		m_hwnd;
	int			m_delayTime;		//设置获取数据的超时时间，因为底层或许一直得不到数据，必须设置一个超时，单位ms
private:
	static CRadarApp*	_instance;
	JMutex				m_mutex;
	CRadarCommDll*		m_radarComm;	//通信模块对象
	CAlgorithm*			m_algorithm;	//算法模块对象

	void*	Thread(); 
};
#define CRADAR_APP CRadarApp::Instance()

#endif // !defined(AFX_RADARAPP_H__1087BE09_964D_442A_8C16_727F725938B9__INCLUDED_)
