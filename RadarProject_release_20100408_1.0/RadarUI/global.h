/*****************************************************************
*文件名：			global.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2010-1-06			
*
*说明
	全局头文件，全局的宏定义放在这里。
******************************************************************/
#ifndef _RDGlobal_H_
#define _RDGlobal_H_

#define WM_SYSPARAM_CHANGE	WM_USER+201		//系统参数改变消息


//雷达控件相关图片宏定义
#define MAP_BG				"bmp\\map\\bg.bmp"
#define MAP_STATEING		"bmp\\map\\stateing.bmp"		//学习中
#define MAP_STATED			"bmp\\map\\stated.bmp"		//学习完成，扫描中
#define MAP_STATESTART		"bmp\\map\\statestart.bmp"	//等待启动
#define MAP_STATE_PLAYBACK	"bmp\\map\\playback.bmp"		//数据回放

#define MAP_ZOOMIN			"bmp\\map\\zoomin.bmp"
#define MAP_ZOOMIND			"bmp\\map\\zoomind.bmp"
#define MAP_ZOOMOUT			"bmp\\map\\zoomout.bmp"
#define MAP_ZOOMOUTD		"bmp\\map\\zoomoutd.bmp"


//报警声音
#define ALARM_SOUND			"wav\\alarm.wav"

//历史数据目录
#define DIR_HISTORY			"history"



//////////////////////////////////////UI美化BMP////////////////////////////////////
#define UI_MAINBG								"bmp\\mainbg.bmp"
//关闭按钮
#define UI_MAIN_CLOSEBTN_NORMAL					"bmp\\mainCloseBtnN.bmp"
#define UI_MAIN_CLOSEBTN_HOVER					"bmp\\mainCloseBtnH.bmp"

//开启雷达按钮
#define UI_MAIN_OPENRADARBTN_NORMAL				"bmp\\mainStartBtnN.bmp"
#define UI_MAIN_OPENRADARBTN_HOVER				"bmp\\mainStartBtnH.bmp"
#define UI_MAIN_OPENRADARBTN_DISABLE			"bmp\\mainStartBtnD.bmp"

//停止雷达按钮
#define UI_MAIN_STOPRADARBTN_NORMAL				"bmp\\mainStopBtnN.bmp"
#define UI_MAIN_STOPRADARBTN_HOVER				"bmp\\mainStopBtnH.bmp"
#define UI_MAIN_STOPRADARBTN_DISABLE			"bmp\\mainStopBtnD.bmp"

//历史数据按钮
#define UI_MAIN_HISTORYBTN_NORMAL				"bmp\\mainHistoryBtnN.bmp"
#define UI_MAIN_HISTORYBTN_HOVER				"bmp\\mainHistoryBtnH.bmp"
#define UI_MAIN_HISTORYBTN_DISABLE				"bmp\\mainHistoryBtnD.bmp"

//参数设置按钮
#define UI_MAIN_PARAMBTN_NORMAL					"bmp\\mainParamBtnN.bmp"
#define UI_MAIN_PARAMBTN_HOVER					"bmp\\mainParamBtnH.bmp"
#define UI_MAIN_PARAMBTN_DISABLE				"bmp\\mainParamBtnD.bmp"

//响应/取消报警按钮
#define UI_MAIN_ALARMBTN_ON						"bmp\\mainAlarmBtnAnwser.bmp"
#define UI_MAIN_ALARMBTN_OFF					"bmp\\mainAlarmBtnCancel.bmp"
#define UI_MAIN_ALARMBTN_DISABLE				"bmp\\mainAlarmBtnCancel.bmp"

//开启/关闭声音按钮
#define UI_MAIN_SOUNDBTN_ON						"bmp\\mainOpenSoundBtn.bmp"
#define UI_MAIN_SOUNDBTN_OFF					"bmp\\mainCloseSoundBtn.bmp"
#define UI_MAIN_SOUNDBTN_DISABLE				"bmp\\mainOpenSoundBtn.bmp"

//登陆
#define UI_LOGINBG								"bmp\\loginbg.bmp"
#define UI_LOGINBTN_NORMAL						"bmp\\loginnormal.bmp"
#define UI_LOGINBTN_HOVER						"bmp\\loginhover.bmp"

//关闭
#define UI_LOGINCLOSEBTN_NORMAL					"bmp\\logincloseN.bmp"
#define UI_LOGINCLOSEBTN_HOVER					"bmp\\logincloseH.bmp"

///////////////////////////历史数据
#define UI_HISTORY_BG							"bmp\\history\\historybg.bmp"
#define UI_HISTORY_RETURNN						"bmp\\history\\returnn.bmp"
#define UI_HISTORY_RETURNH						"bmp\\history\\returnh.bmp"
#define UI_HISTORY_RETURND						"bmp\\history\\returnd.bmp"

#define UI_HISTORY_REFRESHN						"bmp\\history\\refreshn.bmp"
#define UI_HISTORY_REFRESHH						"bmp\\history\\refreshh.bmp"
#define UI_HISTORY_REFRESHD						"bmp\\history\\refreshd.bmp"

///////////////////////////参数设置
#define UI_PARAM_BG								"bmp\\paramset\\paramsetbg.bmp"

#define UI_PARAM_ALGSETN						"bmp\\paramset\\algsetn.bmp"
#define UI_PARAM_ALGSETH						"bmp\\paramset\\algseth.bmp"
#define UI_PARAM_ALGSETD						"bmp\\paramset\\algsetd.bmp"

#define UI_PARAM_PWDSETN						"bmp\\paramset\\pwdsetn.bmp"
#define UI_PARAM_PWDSETH						"bmp\\paramset\\pwdseth.bmp"
#define UI_PARAM_PWDSETD						"bmp\\paramset\\pwdsetd.bmp"

#define UI_PARAM_RADARSETN						"bmp\\paramset\\radarsetn.bmp"
#define UI_PARAM_RADARSETH						"bmp\\paramset\\radarseth.bmp"
#define UI_PARAM_RADARSETD						"bmp\\paramset\\radarsetd.bmp"

#define UI_PARAM_SYSSETN						"bmp\\paramset\\syssetn.bmp"
#define UI_PARAM_SYSSETH						"bmp\\paramset\\sysseth.bmp"
#define UI_PARAM_SYSSETD						"bmp\\paramset\\syssetd.bmp"


////////////////////////COMMON
#define UI_COMMON_CONFIRMN						"bmp\\common\\confirmn.bmp"
#define UI_COMMON_CONFIRMH						"bmp\\common\\confirmh.bmp"
#define UI_COMMON_CONFIRMD						"bmp\\common\\confirmd.bmp"

#define UI_COMMON_RETURNN						"bmp\\common\\returnn.bmp"
#define UI_COMMON_RETURNH						"bmp\\common\\returnh.bmp"
#define UI_COMMON_RETURND						"bmp\\common\\returnd.bmp"

#define UI_COMMON_RADIO_UNCHECKED				"bmp\\common\\radioUnchecked.bmp"
#define UI_COMMON_RADIO_CHECKED					"bmp\\common\\radiochecked.bmp"

///////////////////////PWD SET
#define UI_PWD_BG								"bmp\\pwd\\pwdBg.bmp"

///////////////////////SYS SET
#define UI_SYSTEM_BG							"bmp\\system\\sysBg.bmp"

///////////////////////RADAR SET
#define UI_RADAR_BG								"bmp\\radar\\radarBg.bmp"

///////////////////////ALG SET
#define UI_ALG_BG								"bmp\\alg\\algbg.bmp"

#endif 