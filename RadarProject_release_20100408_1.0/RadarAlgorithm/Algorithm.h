// Algorithm.h: interface for the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHM_H__7D1AD2D9_746D_4E77_9790_61280A9D8D07__INCLUDED_)
#define AFX_ALGORITHM_H__7D1AD2D9_746D_4E77_9790_61280A9D8D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "struct.h"


//一些宏定义
#define GET_NEW_MAP 0x00000001
#define GET_MID_RESULT 0x00000002
#define GET_FINAL_RESULT 0x00000004

#define MAX_DATA_LENGTH 1440    //一扫描帧的最大数据长度
#define MAX_FRAME_NUM    30     //原始帧队列中的最大帧数量
#define MAX_OBJECT_NUM    1000     //最大目标数量
#define BLDMAP_FRAME_NUM 10     //建立地图所需帧数
#define OMIT_POINT_NUM  5       //忽略掉的点数
#define OMIT_POINT_NUM_TCP 150   //求取前景点时两边忽略掉的点数，针对定制TCP雷达

#define PI 3.1415926

//声明计算两点间距离的全局函数
double CmptDistance(POINT pt1, POINT pt2);
//声明进行数据插值转换的全局函数
void TransformData(int *pDest,int nDestLength,int *pSource,int nSourceLength);

//原始数据帧队列结构体：
struct DataFrameQueue
{
    int curFrameNum;    //当前实际存放的数据帧数目
    DataFrame frame[MAX_FRAME_NUM];  //存放原始数据帧
};

//前景点集：
struct ForegroundPointSet
{
    int pointNum;    //点个数
    POINT point[MAX_DATA_LENGTH];  //存放前景点
};

//目标特征结构体
struct SegmentFeature
{
    int pointNumber; // 数据点个数
	 int standardDeviation; // 标准差
	 int preceedingDistance; // 该段第一个点与前一段最后一个点的距离
	 int succeedingDistance; // 该段最后点与下一段第一个点的距离
	 int width; // 宽度，即第一点与最后一点的距离
	 int lineartiy; // 线性度
	 int boundaryLength; // 边界长度
	 int curvature; // 曲率
	 int depth; // 深度，即纵向最大距离
	 BOOL bWarning;   //决定报警与否
};

//特征集合
struct FeatureExtraction
{
    int segNumber;  // 数据段个数
    SegmentFeature segFeature[MAX_DATA_LENGTH];   //存储数据段特征
};

#ifdef RADARALGORITHM_EXPORTS
class _declspec(dllexport) CAlgorithm     //导出类circle
#else
class _declspec(dllimport) CAlgorithm     //导入类circle
#endif
{
public:
	CAlgorithm();
	virtual ~CAlgorithm();

	//公有成员
	BkgrdMap m_Map;  //背景地图
	WarningResult m_FinalResult;   //最终结果
	WarningResult m_MidResult;  //单步结果

public:
	//公有函数

	BOOL Initial(AlgorithmConfigInfo &cfgInfo);
	DWORD GetResult(DataFrame &frm);
	void  ResetState(BYTE state);//设置m_TemporaryState
protected:
	BYTE m_TemporaryState;
protected:
	AlgorithmConfigInfo m_CfgInfo;   //算法所需的配置信息
	DataFrameQueue m_DataFrameQueue;  //原始数据帧队列
	DataFrame * m_pCurDataFrame;          //指向当前数据帧的指针

	int m_nStdDataLength;                //标准数据长度
	BOOL m_bHaveStdDataLength;             //是否获取了标准数据长度

	int m_BackOffset[MAX_DATA_LENGTH];                     //背景偏移量

	ForegroundPointSet m_FogrdPntSet;    //前景点集 
	int m_nSplitIndex[MAX_DATA_LENGTH];    //对前景点集的分割索引
	int m_nSplitNum;                        //分割索引的个数，表征有多少个初级目标点集

	FeatureExtraction m_FeatureSet;         //目标特征集合

	double m_fStartAngle;                 //起始角度（单位：弧度）
	double m_fStopAngle;                 //终止角度（单位：弧度）
	double m_fAngleStep;                  //角度步进


	DWORD GetHokuyoResult(DataFrame &frm);    //获取日本激光雷达结果
	DWORD GetTCPResult(DataFrame &frm);    //获取自制TCP雷达结果
	DWORD GetLeuzeResult(DataFrame &frm);    //获取Leuze雷达结果

	void InputData(DataFrame frm);        //将原始数据添加进数据帧队列中
	void OutQueue(int num);             //清出数据帧队列中的前若干帧
	void ClearQueue();                   //清空数据帧队列
	DWORD PreProcess();                    //预处理数据帧队列中的当前帧
	DWORD PreProcessTCP();                    //预处理数据帧队列中的当前帧，针对定制TCP雷达
	DWORD BuildMap();                       //建立地图
	int GetMapPeriod();                    //获取当前地图以存在了多久
	DWORD GetWarningResult();              //获取报警结果
	DWORD GetTCPWarningResult();              //获取报警结果，针对定制TCP雷达
	//DWORD GetWarningResult2();              //获取报警结果，采用方法2
	void GetPointSet();                    //获取前景点
	void GetPointSet2();                    //获取前景点，采用自适应的背景偏移量方法
	void GetPointSetTCP();                    //获取前景点，采用自适应的背景偏移量方法，针对定制TCP雷达
	void SplitObject();                    //从前景点分割出目标
	void DetectObject();                    //检测目标 
	void ExtractFeature();                  //提取目标特征
	void AnalyzeJudge();                    //根据特征判别是否报警
	DWORD GenerateResult();                  //产生报警结果

};

#endif // !defined(AFX_ALGORITHM_H__7D1AD2D9_746D_4E77_9790_61280A9D8D07__INCLUDED_)
