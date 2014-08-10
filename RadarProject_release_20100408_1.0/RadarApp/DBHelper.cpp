// DBHelper.cpp: implementation of the CDBHelper class.
//
//////////////////////////////////////////////////////////////////////
#include "DBHelper.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBHelper::CDBHelper(char * mdbFile)
{
	CoInitialize(NULL);
	char tempStr[500]="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	
	char * c=strcat(tempStr,mdbFile);
	memcpy(m_connectStr, c,500);

	m_pConnection.CreateInstance(__uuidof(Connection));
	
	try                 
	{	
		// 打开本地Access库 
		m_pConnection->Open(m_connectStr,"","",adModeUnknown);
		//m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=data.mdb","","",adModeUnknown);
		
	}
	catch(_com_error e)
	{
		 throw ;
	} 
}

CDBHelper::~CDBHelper()
{
	// 关闭ADO连接状态
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;

	CoUninitialize();
}



