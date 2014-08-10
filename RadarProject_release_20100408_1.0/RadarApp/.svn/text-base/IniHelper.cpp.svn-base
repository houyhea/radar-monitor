// IniHelper.cpp: implementation of the CIniHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "IniHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniHelper::CIniHelper(LPCSTR directory,   /*当前程序的子目录，如果文件在根目录，则传入空字符串*/
					   LPCSTR file			/*ini文件相对于当前程序的路径*/
					   )
{
	if("" != directory)
		CreateDirectory(directory,NULL);
	memcpy(m_iniFile,file,250);

	
}

CIniHelper::~CIniHelper()
{

}
BOOL CIniHelper::ReadIniFile(
		LPCSTR lpAppName,				/*节点名称*/
		LPCSTR lpKeyName,				/*键*/
		LPCSTR lpDefault,				/*默认值。=NULL*/
		LPSTR lpReturnedString,		/*返回键值*/
		DWORD nSize					/*返回键值尺寸*/
    )
{
	return GetPrivateProfileString (lpAppName,lpKeyName, lpDefault, lpReturnedString, nSize, m_iniFile); 
}

BOOL CIniHelper::WriteIniFile(
		LPCSTR lpAppName,				/*节点名称*/
		LPCSTR lpKeyName,				/*键*/
		LPCSTR lpString				/*键值*/
    )
{
	return WritePrivateProfileString (lpAppName,lpKeyName,lpString, m_iniFile); 
}
