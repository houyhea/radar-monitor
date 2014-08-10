/*****************************************************************
*文件名：			RadarFileOp.h
*处理器名：	        -
*编译器名：	        -
*公司名：			中科院无锡物联网产业研究院
*当前版本号：	    v1.0
*
*Copyright? 2009, 中科院无锡物联网产业研究院 All rights reserved.
*
*作者			时间					备注
*zhangyong		2010-1-27			
*
*说明
	文件目录操作辅助类
******************************************************************/
// RadarFileOp.h: interface for the CRadarFileOp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARFILEOP_H__6C633A0F_006C_43FA_A288_C1CCDC252009__INCLUDED_)
#define AFX_RADARFILEOP_H__6C633A0F_006C_43FA_A288_C1CCDC252009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRadarFileOp  
{
public:
	CRadarFileOp();
	virtual ~CRadarFileOp();
	BOOL   FolderExist(CString strPath);

	BOOL   FileExist(CString strFileName);
	BOOL CreateFolder(CString strPath);

};

#endif // !defined(AFX_RADARFILEOP_H__6C633A0F_006C_43FA_A288_C1CCDC252009__INCLUDED_)
