// RadarApp.cpp: implementation of the CRadarApp class.
//
//////////////////////////////////////////////////////////////////////
//#include <windows.h>

#include "RadarApp.h"
#include "RadarCommDll.h"
#include "Algorithm.h"
#include "IniHelper.h"
#include "dbhelper.h"
#include "inisec.h"

//配置INI文件宏
#define		INI_FILE_DIRECTORY				".\\ini"
#define		INI_FILE						".\\ini\\radar.ini"

//MDB数据库文件
#define		DB_MDB_FILE						".\\data\\data.mdb"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRadarApp* CRadarApp::_instance = NULL;

CRadarApp* CRadarApp::Instance()
{
	if(_instance==NULL)
	{
		_instance=new CRadarApp();
	}

	return _instance;
}
CRadarApp::CRadarApp()
{
	m_radarComm=NULL;
	m_algorithm=NULL;
	//初始化INI文件操作类
	m_iniHelper=new CIniHelper(INI_FILE_DIRECTORY,INI_FILE);

	
	//初始化数据库操作类
	m_dbHelper=new CDBHelper(DB_MDB_FILE);

	//构造函数	
	m_mutex.Init();

	m_delayTime=1000*5;//设置获取数据超时时间
}

//公共方法部分
META_ERROR CRadarApp::Init(HWND hwnd)
{
	
	m_hwnd=hwnd;

	//初始化通信模块
	m_radarComm=new CRadarCommDll();
	if(m_radarComm==NULL)
	{
		return META_ERR_COMM_INT;
	}
	//初始化雷达配置信息（整合后的调用方式）
	UpdateRadarConfig();
	
	//初始化算法模块
	m_algorithm=new CAlgorithm();
	if(m_algorithm==NULL)
	{
		return META_ERR_ALG_INI;
	}
	//初始化算法模块参数	
	UpdateAlgConfig();	

	
	return META_ERR_SUCCESS;
}



CRadarApp::~CRadarApp()
{
	if(JThread::IsRunning())
		JThread::Kill();

	
	//析构一些指针变量，释放空间
	if(m_radarComm!=NULL)
	{
		delete m_radarComm;
		m_radarComm=NULL;
	}
	if(m_algorithm!=NULL)
	{
		delete m_algorithm;
		m_algorithm=NULL;
	}
	if(m_iniHelper!=NULL)
	{
		delete m_iniHelper;
		m_iniHelper=NULL;
	}
	if(m_dbHelper!=NULL)
	{
		delete m_dbHelper;
		m_dbHelper=NULL;
	}
}

META_ERROR CRadarApp::StartRadar()
{
	if(m_radarComm!=NULL)
	{
		//调用雷达通信模块的启动雷达接口函数
		bool b=m_radarComm->Comm_StartRadar();
		if(!b)
			return META_ERR_RADAR_START_LOSE;
	}
	else
	{
		return META_ERR_RADAR_NOT_INT;
	}
	//启动接收线程
	Start();
	return META_ERR_SUCCESS;	
}
META_ERROR CRadarApp::StopRadar()
{
	if(JThread::IsRunning())
		JThread::Kill();
	
	//设置算法部分，重新绘制地图
	m_algorithm->ResetState(0);

	if(m_radarComm->Comm_StopRadar())
		return META_ERR_SUCCESS;
	
	return META_ERR_UNKNOWN;
}

META_ERROR CRadarApp::CheckPwd(char * pwd,int size)
{
	if(m_iniHelper==NULL)
		return META_ERR_PWD;
	char sysPwd[50];
	if(m_iniHelper->ReadIniFile(INI_SEC_SYS,INI_P_SYS_PWD,NULL,sysPwd,50))
	{
		int ret=strcmp(pwd,sysPwd);
		return ret==0?META_ERR_SUCCESS:META_ERR_PWD;
	}
	else
	{
		return META_ERR_INI_NOT_FOUND;
	}

}

META_ERROR CRadarApp::ChangePwd(char * pwd,int size)
{
	if(m_iniHelper==NULL)
		return META_ERR_UNKNOWN;
	
	if(m_iniHelper->WriteIniFile(INI_SEC_SYS,INI_P_SYS_PWD,pwd))
		return META_ERR_SUCCESS;
	else
		return META_ERR_UNKNOWN;
	
}
META_ERROR	CRadarApp::SetAnswerAlarm(bool enableAlarm)
{
	if(m_iniHelper==NULL)
		return META_ERR_UNKNOWN;
	
	if(m_iniHelper->WriteIniFile(INI_SEC_SYS,INI_P_SYS_ANSWERALARM,enableAlarm?"1":"0"))
		return META_ERR_SUCCESS;
	else
		return META_ERR_UNKNOWN;
}

bool	CRadarApp::GetAnswerAlarm()
{
	if(m_iniHelper==NULL)
		return true;//默认开启
	char c_value[50];

	m_iniHelper->ReadIniFile(INI_SEC_SYS,INI_P_SYS_ANSWERALARM,"1",c_value,50);
	int tag=atoi(c_value);
	return tag==1;
}
META_ERROR	CRadarApp::SetSoundAlarm(bool enableSoundAlarm)
{
	if(m_iniHelper==NULL)
		return META_ERR_UNKNOWN;
	
	if(m_iniHelper->WriteIniFile(INI_SEC_SYS,INI_P_SYS_SOUNDALARM,enableSoundAlarm?"1":"0"))
		return META_ERR_SUCCESS;
	else
		return META_ERR_UNKNOWN;
}
bool CRadarApp::GetSoundAlarm()
{
	if(m_iniHelper==NULL)
		return true;//默认开启
	char c_value[50];

	m_iniHelper->ReadIniFile(INI_SEC_SYS,INI_P_SYS_SOUNDALARM,"1",c_value,50);
	int tag=atoi(c_value);
	return tag==1;
}

META_ERROR	CRadarApp::SetAlarmShwoCnt(int cnt)
{
	if(m_iniHelper==NULL)
		return META_ERR_UNKNOWN;
	char c_value[50];
	
	_itoa(cnt,c_value,10 );//10表示10进制	

	if(m_iniHelper->WriteIniFile(INI_SEC_SYS,INI_P_SYS_ALARMSHOWCNT,c_value))
		return META_ERR_SUCCESS;
	else
		return META_ERR_UNKNOWN;

}

int	CRadarApp::GetAlarmShwoCnt()
{
	if(m_iniHelper==NULL)
		return true;//默认开启
	char c_value[50];

	m_iniHelper->ReadIniFile(INI_SEC_SYS,INI_P_SYS_ALARMSHOWCNT,"100",c_value,50);
	int cnt=atoi(c_value);
	return cnt;
	
}




//算法配置
BOOL CRadarApp::GetAlgConfig(AlgorithmConfigInfo * cfg)
{
	if(m_iniHelper==NULL)
		return FALSE;
	char c_value[50];

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_BLDMAPPERIOD,"0",c_value,50);
	cfg->bldmapPeriod=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_BKGRDOFFSET,"300",c_value,50);
	cfg->bkgrdOffset=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_CHKWIDTHTHRESHOLD,"100",c_value,50);
	cfg->chkWidthThreshold=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_FUSHIONSTEPNUM,"1",c_value,50);
	cfg->fushionStepNum=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_SAMEOBLENGTH,"50",c_value,50);
	cfg->sameobLength=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_FUSHIONTIME,"2000",c_value,50);
	cfg->fushionTime=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_ALG,INI_P_ALG_RADARTYPE,"0",c_value,50);
	cfg->radarType=atoi(c_value);

	return TRUE;
	
}

META_ERROR CRadarApp::SetAlgConfig(AlgorithmConfigInfo* cfg)
{
	if(m_iniHelper==NULL)
		return META_ERR_UNKNOWN;
	
	char c_value[50];
	
	_itoa(cfg->bkgrdOffset,c_value,10 );//10表示10进制
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_BKGRDOFFSET,c_value);
	
	_itoa(cfg->bldmapPeriod,c_value,10 );
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_BLDMAPPERIOD,c_value);
	
	_itoa(cfg->chkWidthThreshold,c_value,10 );
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_CHKWIDTHTHRESHOLD,c_value);
	
	_itoa(cfg->fushionStepNum,c_value,10 );
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_FUSHIONSTEPNUM,c_value);
	
	_itoa(cfg->sameobLength,c_value,10 );
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_SAMEOBLENGTH,c_value);
	
	_itoa(cfg->fushionTime,c_value,10 );
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_FUSHIONTIME,c_value);

	_itoa(cfg->radarType,c_value,10 );
	m_iniHelper->WriteIniFile(INI_SEC_ALG,INI_P_ALG_RADARTYPE,c_value);

	return META_ERR_SUCCESS;

	
}

BOOL CRadarApp::UpdateAlgConfig()
{
	AlgorithmConfigInfo c;

	GetAlgConfig(&c);

	//to do:需要设置一些初始化参数，后续会从配置文件或者数据库读取参数传入算法模块
	m_algorithm->Initial(c);
	return TRUE;
}

//雷达配置
BOOL CRadarApp::GetRadarConfig(HardConfigInfo * cfg)
{
	if(m_iniHelper==NULL)
		return FALSE;
	char c_value[50];

	
	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_PRODUCT,"0",c_value,50);//默认 0 就是SCIP
	cfg->radar=(EnumRadar)(atoi(c_value));

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_BITRATE,"115200",c_value,50);//波特率
	cfg->BitRate=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_MOTORRATE,"0",c_value,50);//马达转速
	cfg->motorRate=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_STARTANGLE,"-225",c_value,50);//起始角
	cfg->startAngle=(long)atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_STOPANGLE,"1125",c_value,50);//结束角
	cfg->stopAngle=(long)atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_COMPORT,"COM1",c_value,50);//COM口
	memcpy(cfg->comDevice,c_value,50);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_IPADDR,"127.0.0.1",c_value,50);//IP地址
	memcpy(cfg->ip,c_value,50);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_IPPORT,"1900",c_value,50);//IP端口
	cfg->port=atoi(c_value);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_SAVERAWDATA,"0",c_value,50);//是否保存原始数据
	cfg->saveRawData=(atoi(c_value)==1);

	char file[500];
	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_RAWDATAFILE,"rawdata.txt",file,500);//原始数据文件	
	memcpy(cfg->rawDataFile,file,500);

	m_iniHelper->ReadIniFile(INI_SEC_RADAR,INI_P_RADAR_VALIDDISTANCE,"20000",c_value,50);//有效距离
	cfg->validDistance=atoi(c_value);

	return TRUE;
}
META_ERROR CRadarApp::SetRadarConfig(HardConfigInfo* cfg)
{
	if(m_iniHelper==NULL)
		return META_ERR_UNKNOWN;
	
	char c_value[50];
	BOOL tag=FALSE;
	
	_itoa(cfg->radar,c_value,10 );//10表示10进制
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_PRODUCT,c_value); //雷达产品
	
	_itoa(cfg->BitRate,c_value,10 );
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_BITRATE,c_value);//波特率
	
	_itoa(cfg->motorRate,c_value,10 );
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_MOTORRATE,c_value);//马达转速
	
	ltoa(cfg->startAngle,c_value,10 );
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_STARTANGLE,c_value);//起始角
	
	ltoa(cfg->stopAngle,c_value,10 );
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_STOPANGLE,c_value);//结束角
	

	m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_COMPORT,cfg->comDevice);//com口
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_IPADDR,cfg->ip);//IP地址


	_itoa(cfg->port,c_value,10 );
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_IPPORT,c_value);//IP端口

	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_SAVERAWDATA,cfg->saveRawData?"1":"0");//是否保存原始数据

	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_RAWDATAFILE,cfg->rawDataFile);//原始数据文件

	_itoa(cfg->validDistance,c_value,10 );//10表示10进制
	tag=m_iniHelper->WriteIniFile(INI_SEC_RADAR,INI_P_RADAR_VALIDDISTANCE,c_value); //有效距离

	if(tag)
		return META_ERR_SUCCESS;
	else
		return META_ERR_UNKNOWN;
}

BOOL CRadarApp::UpdateRadarConfig()
{
	HardConfigInfo c;
	
	GetRadarConfig(&c);

	m_radarComm->Comm_SetRadarConfig(c);
	return TRUE;
}



BOOL CRadarApp::ReadIniFile(
		LPCSTR lpAppName,				/*节点名称*/
		LPCSTR lpKeyName,				/*键*/
		LPCSTR lpDefault,				/*默认值。=NULL*/
		LPSTR lpReturnedString,		/*返回键值*/
		DWORD nSize					/*返回键值尺寸*/
    )
{
	return  m_iniHelper->ReadIniFile(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize);
}

BOOL CRadarApp::WriteIniFile(
		LPCSTR lpAppName,				/*节点名称*/
		LPCSTR lpKeyName,				/*键*/
		LPCSTR lpString				/*键值*/
    )
{
	return m_iniHelper->WriteIniFile(lpAppName,lpKeyName,lpString);
}




void *	CRadarApp::Thread()
{
	JThread::ThreadStarted();
	DataFrame pData;
	DWORD ret;
	int delayCnt=0;

	while(1)
	{
		//通过CommDll获取数据，然后通知UI显示
		Sleep(10);
		
		bool tag=false;
		tag=m_radarComm->Comm_GetRawDataFromFIFO(&pData);
		
		delayCnt+=10;//累加10ms，Sleep(50);
		if((delayCnt>=m_delayTime) )
			//&& (tag==false))
		{
			SendMessage(m_hwnd,WM_GETDATATIMEOUT,0,0);
		}
		if(tag)
		{
			delayCnt=0;
			
			//把pData传入算法模块，运算后，得到结果，输出到UI
			ret=m_algorithm->GetResult(pData);
			
			//根据返回结果来处理,按位与
			if((ret & GET_NEW_MAP)==GET_NEW_MAP)//准备地图
			{
				if(m_hwnd!=NULL)	
					SendMessage(m_hwnd,WM_GETMAP,(LONG)&m_algorithm->m_Map,0);				
			}
			if((ret & GET_FINAL_RESULT ) ==GET_FINAL_RESULT)//得到数据
			{
				if(m_hwnd!=NULL)	
					SendMessage(m_hwnd,WM_GETDATA,(LONG)&pData,(LONG)&m_algorithm->m_FinalResult);
			}

		}		
	}
}
