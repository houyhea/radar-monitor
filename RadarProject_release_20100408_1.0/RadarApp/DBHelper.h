/*****************************************************************
*文件名：			DBHelper.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2010, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2010-1-7			
*
*说明
	激光雷达--应用程序层--数据库操作类。采用ADO方式操作ACCESS数据库。
	Active Data Object，活动数据对象，基于COM组件模型。
******************************************************************/
// DBHelper.h: interface for the CDBHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBHELPER_H__3E46DC14_9C62_4A66_98B7_CAC3B8ACF285__INCLUDED_)
#define AFX_DBHELPER_H__3E46DC14_9C62_4A66_98B7_CAC3B8ACF285__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "c:\program files\common files\system\ado\msado15.dll" \
no_namespace \
rename ("EOF", "adoEOF") 


class CDBHelper  
{
public:
	CDBHelper(char* mdbFile);
	virtual		~CDBHelper();

	
	_ConnectionPtr		m_pConnection;					// 定义ADO连接变量指针

	char				m_connectStr[500];				//连接字符串
	//还未写完，还有一些读取，插入，修改，删除的操作方法没有写

};

#endif // !defined(AFX_DBHELPER_H__3E46DC14_9C62_4A66_98B7_CAC3B8ACF285__INCLUDED_)
