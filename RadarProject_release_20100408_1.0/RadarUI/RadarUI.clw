; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRadarLoginDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RadarUI.h"

ClassCount=13
Class1=CRadarUIApp
Class2=CRadarUIDlg

ResourceCount=10
Resource1=IDR_MAINFRAME
Class3=CRadarMapCtrl
Resource2=IDD_DIALOG_PWDSET
Class4=CRadarLoginDlg
Resource3=IDD_DIALOG_LOGIN
Class5=CRadarBaseDlg
Resource4=IDD_DIALOG_BASEDLG
Class6=CRadarParamSetDlg
Resource5=IDD_DIALOG_PARAMSET
Class7=CRadarSetRadarDlg
Resource6=IDD_DIALOG_SYSSET
Class8=CRadarSetPwdDlg
Resource7=IDD_DIALOG_ALGSET
Class9=CRadarSetAlgDlg
Resource8=IDD_DIALOG_RADARSET
Class10=CRadarSetSysDlg
Resource9=IDD_RADARUI_DIALOG
Class11=CRadarHistoryDlg
Class12=CRadarButton
Class13=CRadarStateButton
Resource10=IDD_DIALOG_HISTORY

[CLS:CRadarUIApp]
Type=0
HeaderFile=RadarUI.h
ImplementationFile=RadarUI.cpp
Filter=N

[CLS:CRadarUIDlg]
Type=0
HeaderFile=RadarUIDlg.h
ImplementationFile=RadarUIDlg.cpp
Filter=W
BaseClass=CRadarBaseDlg
VirtualFilter=dWC
LastObject=CRadarUIDlg



[DLG:IDD_RADARUI_DIALOG]
Type=1
Class=CRadarUIDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_BUTTON_STARTRADAR,button,1342242816
Control3=IDC_BUTTON_STOPRADAR,button,1342242816
Control4=IDC_STATIC_MAP,static,1342308608
Control5=IDC_BUTTON_SET,button,1342242816
Control6=IDC_BUTTON_ALARM,button,1342242816
Control7=IDC_BUTTON_CLOSESOUND,button,1342242816
Control8=IDC_LIST_ALARMRECORD,SysListView32,1350631425
Control9=IDC_BUTTON_HISTORY,button,1342242816

[CLS:CRadarMapCtrl]
Type=0
HeaderFile=RadarMapCtrl.h
ImplementationFile=RadarMapCtrl.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CRadarMapCtrl

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=CRadarLoginDlg
ControlCount=3
Control1=ID_LOGIN,button,1342242817
Control2=IDC_EDIT_PWD,edit,1350631584
Control3=IDC_BTN_CLOSE,button,1342242816

[CLS:CRadarLoginDlg]
Type=0
HeaderFile=RadarLoginDlg.h
ImplementationFile=RadarLoginDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
LastObject=IDC_STATIC_VER
VirtualFilter=dWC

[DLG:IDD_DIALOG_BASEDLG]
Type=1
Class=CRadarBaseDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CRadarBaseDlg]
Type=0
HeaderFile=RadarBaseDlg.h
ImplementationFile=RadarBaseDlg.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_DIALOG_PARAMSET]
Type=1
Class=CRadarParamSetDlg
ControlCount=5
Control1=IDC_BUTTON_PWD,button,1342242816
Control2=IDC_BUTTON_RADAR,button,1342242816
Control3=IDC_BUTTON_SYS,button,1342242816
Control4=IDC_BUTTON_ALG,button,1342242816
Control5=IDC_BUTTON_RETURN,button,1342242816

[CLS:CRadarParamSetDlg]
Type=0
HeaderFile=RadarParamSetDlg.h
ImplementationFile=RadarParamSetDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
VirtualFilter=dWC
LastObject=CRadarParamSetDlg

[DLG:IDD_DIALOG_RADARSET]
Type=1
Class=CRadarSetRadarDlg
ControlCount=14
Control1=IDC_BUTTON_OK,button,1342242816
Control2=IDC_BUTTON_RETURN,button,1342242816
Control3=IDC_COMBO_RADAR,combobox,1344340227
Control4=IDC_EDIT_BITRATE,edit,1350631552
Control5=IDC_EDIT_COMPORT,edit,1350631552
Control6=IDC_EDIT_STARTANGLE,edit,1350631552
Control7=IDC_EDIT_STOPANGLE,edit,1350631552
Control8=IDC_EDIT_IPADDR,edit,1350631552
Control9=IDC_EDIT_IPPORT,edit,1350631552
Control10=IDC_EDIT_MOTORRATE,edit,1350631552
Control11=IDC_EDIT_FILE,edit,1350631552
Control12=IDC_BUTTON_FILE,button,1342242816
Control13=IDC_EDIT_VALIDDISTANCE,edit,1350631552
Control14=IDC_BUTTON_RADIO_SAVEFILE,button,1342242816

[CLS:CRadarSetRadarDlg]
Type=0
HeaderFile=RadarSetRadarDlg.h
ImplementationFile=RadarSetRadarDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
LastObject=IDC_RADIO_SAVE
VirtualFilter=dWC

[DLG:IDD_DIALOG_PWDSET]
Type=1
Class=CRadarSetPwdDlg
ControlCount=5
Control1=IDC_EDIT_OLDPWD,edit,1350631584
Control2=IDC_EDIT_NEWPWD,edit,1350631584
Control3=IDC_EDIT_NEWPWD1,edit,1350631584
Control4=IDC_BUTTON_OK,button,1342242816
Control5=IDC_BUTTON_RETURN,button,1342242816

[CLS:CRadarSetPwdDlg]
Type=0
HeaderFile=RadarSetPwdDlg.h
ImplementationFile=RadarSetPwdDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
LastObject=CRadarSetPwdDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_ALGSET]
Type=1
Class=CRadarSetAlgDlg
ControlCount=8
Control1=IDC_BUTTON_OK,button,1342242816
Control2=IDC_BUTTON_RETURN,button,1342242816
Control3=IDC_EDIT_BKGRDOFFSET,edit,1350631552
Control4=IDC_EDIT_SAMEOBLENGTH,edit,1350631552
Control5=IDC_EDIT_WIDTH_THRESHOLD,edit,1350631552
Control6=IDC_EDIT_FUSHION_STEP_NUM,edit,1350631552
Control7=IDC_EDIT_FUSHION_TIME,edit,1350631552
Control8=IDC_EDIT_BULD_MAP_PRD,edit,1350631552

[CLS:CRadarSetAlgDlg]
Type=0
HeaderFile=RadarSetAlgDlg.h
ImplementationFile=RadarSetAlgDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
LastObject=CRadarSetAlgDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_SYSSET]
Type=1
Class=CRadarSetSysDlg
ControlCount=5
Control1=IDC_BUTTON_OK,button,1342242816
Control2=IDC_BUTTON_RETURN,button,1342242816
Control3=IDC_EDIT_ALARMRECORDCNT,edit,1350631552
Control4=IDC_BUTTON_RADIO_ALARM,button,1342242816
Control5=IDC_BUTTON_RADIO_SOUND,button,1342242816

[CLS:CRadarSetSysDlg]
Type=0
HeaderFile=RadarSetSysDlg.h
ImplementationFile=RadarSetSysDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
LastObject=IDC_BUTTON_OK
VirtualFilter=dWC

[DLG:IDD_DIALOG_HISTORY]
Type=1
Class=CRadarHistoryDlg
ControlCount=5
Control1=IDC_BUTTON_RETURN,button,1342242816
Control2=IDC_LIST_RECORD,SysListView32,1350631425
Control3=IDC_STATIC_MAP,static,1342308608
Control4=IDC_TREE_TIME,SysTreeView32,1350631431
Control5=IDC_BUTTON_REFRESH,button,1342242816

[CLS:CRadarHistoryDlg]
Type=0
HeaderFile=RadarHistoryDlg.h
ImplementationFile=RadarHistoryDlg.cpp
BaseClass=CRadarBaseDlg
Filter=W
LastObject=CRadarHistoryDlg
VirtualFilter=dWC

[CLS:CRadarButton]
Type=0
HeaderFile=RadarButton.h
ImplementationFile=RadarButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CRadarButton

[CLS:CRadarStateButton]
Type=0
HeaderFile=RadarStateButton.h
ImplementationFile=RadarStateButton.cpp
BaseClass=CButton
Filter=W

