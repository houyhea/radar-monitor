/*****************************************************************
*文件名：			IniHelper.h
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
	激光雷达--应用程序层--INI文件读取类。
******************************************************************/

// IniHelper.h: interface for the CIniHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIHELPER_H__4D449A73_148C_464E_A056_1CE93BFE90C3__INCLUDED_)
#define AFX_INIHELPER_H__4D449A73_148C_464E_A056_1CE93BFE90C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
class CIniHelper  
{
public:
	CIniHelper::CIniHelper(LPCSTR directory,   /*当前程序的子目录，如果文件在根目录，则传入NULL*/
					   LPCSTR file				/*ini文件相对于当前程序的路径*/
					   );
	virtual ~CIniHelper();

	/**	描述:读取INI文件键值
	 *	参数:
	 *		
	 *	返回值:
	 *	*/
	BOOL ReadIniFile(
		LPCSTR lpAppName,				/*节点名称*/
		LPCSTR lpKeyName,				/*键*/
		LPCSTR lpDefault,				/*默认值。=NULL*/
		LPSTR lpReturnedString,		/*返回键值*/
		DWORD nSize					/*返回键值尺寸*/
    );

	/**	描述:写入INI文件键值
	 *	参数:
	 *		
	 *	返回值:
	 *	*/
	BOOL WriteIniFile(
		LPCSTR lpAppName,				/*节点名称*/
		LPCSTR lpKeyName,				/*键*/
		LPCSTR lpString				/*键值*/
    );
protected:
	char m_iniFile[250];		//ini文件路径
};

#endif // !defined(AFX_INIHELPER_H__4D449A73_148C_464E_A056_1CE93BFE90C3__INCLUDED_)
