// RadarFileOp.cpp: implementation of the CRadarFileOp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarFileOp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadarFileOp::CRadarFileOp()
{

}

CRadarFileOp::~CRadarFileOp()
{

}

//判断文件夹是否存在
BOOL   CRadarFileOp::FolderExist(CString strPath)
{
	WIN32_FIND_DATA   wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(strPath, &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
		rValue = TRUE;   
	}
	FindClose(hFind);
    return rValue;
}

//判断文件是否存在
BOOL   CRadarFileOp::FileExist(CString strFileName)
{
	CFileFind fFind;
	return fFind.FindFile(strFileName); 
}

//创建文件夹
BOOL CRadarFileOp::CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
    //上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
	return ::CreateDirectory( strPath, &attrib);
} 
