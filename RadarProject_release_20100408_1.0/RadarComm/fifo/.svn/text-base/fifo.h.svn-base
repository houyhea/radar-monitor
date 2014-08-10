/*****************************************************************
	
*文件名：		fifo.h
*处理器名：	        --
*编译器名：	        --
*公司名：		中科院无锡微系统分中心
*当前版本号：	        v1.0
*copyright? 2009, 中科院无锡微系统分中心  All rights reserved.
*
*作者			时间					备注
*LiPengYu		2009-07-16		
*输入作者名		输入编写文档时间		编写了哪些部分
******************************************************************/


#ifndef _FIFO_H_
#define _FIFO_H_

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

//#include "config.h"
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef BOOL
//#define BOOL unsigned char 
#define BOOL int	//zyong 注意这里，必须定义成跟win32系统一致的INT，否则会出现编译错误
#endif

typedef unsigned char  uint8;                   // 无符号8位整型变量  
typedef signed   char  int8;                    // 有符号8位整型变量  
typedef unsigned short uint16;                  // 无符号16位整型变量 
typedef signed   short int16;                   // 有符号16位整型变量 
typedef unsigned long   uint32;                  // 无符号32位整型变量 
typedef signed   long   int32;                   // 有符号32位整型变量 
typedef float          fp32;                    // 单精度浮点数（32位长度） 
typedef double         fp64;                    // 双精度浮点数（64位长度） 


//#pragma pack(1)
typedef struct _FIFO_LIST
{  
  uint16 head; //index of head.
  uint16 tail; //index of tail.      
  uint16 item_size; //item size.  
  uint16 item_max_num;
  uint16 item_cnt;  //total number of item  
  uint8* pbuffer;//buffer of fifo.
}FIFO_LIST;
//#pragma pack()




 FIFO_LIST* fifo_create(uint16 item_size, uint16 item_cnt);
 BOOL fifo_set(FIFO_LIST* pfifo, uint8* pitem);
 BOOL fifo_get(FIFO_LIST* pfifo, uint8* pdest);
 uint16 fifo_get_datacnt(FIFO_LIST* pfifo);
 BOOL fifo_delete(FIFO_LIST* pfifo);

#ifdef __cplusplus    // If used by C++ code, 
}          // we need to export the C interface
#endif

#endif
