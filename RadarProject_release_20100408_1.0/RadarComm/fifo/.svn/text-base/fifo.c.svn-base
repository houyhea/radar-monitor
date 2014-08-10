/*****************************************************************
	FIFO 实现
******************************************************************
*文件名：		fifo.c
*处理器名：	        --
*编译器名：	        --
*公司名：		中科院无锡微系统分中心
*当前版本号：	        v1.0
*copyright? 2007, 中科院无锡微系统分中心 All rights reserved.
*
*作者			时间					备注
*LiPengyu		2009-07-22		编写了哪些部分
*输入作者名		输入编写文档时间		编写了哪些部分
******************************************************************/
////////////////////////头文件引用部分//////////////////////////////



//#include <msp430x14x.h>
#include <stdlib.h>
#include <string.h> 
//#include "mac_inter.h"
#include "fifo.h"
//#include "hal.h"

#ifdef __cplusplus    
extern "C" {
#endif


/****************************************************
*	函数名：FIFO_LIST* fifo_create(uint8 item_size, uint16 item_cnt)
*	作者：  产品开发组
*	完成时间：2009-07-16
*	函数功能说明：
*		申请FIFO
*	参数：
*		uint8 item_size, uint16 item_cnt
*	返回值：
*		FIFO_LIST*  FIFO的首地址
*******************************************************/
FIFO_LIST* fifo_create(uint16 item_size, uint16 item_cnt)
{
   FIFO_LIST* phead;
   uint16  size=item_size*item_cnt+sizeof(FIFO_LIST); 
   //uint16* pbuffer=malloc((size+1)/2);
   uint16* pbuffer=malloc(size);
   if(pbuffer==NULL)
   {       
        //debug("SRAMalloc pbuffer error!len %d",size);
         return NULL;
   }
   phead=(FIFO_LIST*)pbuffer;
   phead->head=0; //index of head.
   phead->tail=0; //index of tail.
   phead->item_cnt=0;  //total number of item
   phead->item_max_num=item_cnt;
   phead->item_size=item_size;
   phead->pbuffer=(uint8*)(pbuffer+(sizeof(FIFO_LIST)/2));//buffer of fifo. 
   
   return phead;  
}
/****************************************************
*	函数名：inline uint16   fifo_next_item(FIFO_LIST* pfifo, uint16 cur_item)
*	作者：  产品开发组
*	完成时间：2009-07-16
*	函数功能说明：
*		FIFO指针加加，FIFO读出数据后，指向下一个item
*	参数：
*		FIFO_LIST* pfifo  当前FIFO
*               uint16 cur_item 当前指针
*	返回值：
*		 FIFO的当前指针地址
*******************************************************/
uint16   fifo_next_item(FIFO_LIST* pfifo, uint16 cur_item)
{
  cur_item++;
  if(cur_item>=pfifo->item_max_num)
    cur_item=0;
  return cur_item;
}
/****************************************************
*	函数名：BOOL fifo_set(FIFO_LIST* pfifo, uint8* pitem) 
*	作者：  产品开发组
*	完成时间：2009-07-16
*	函数功能说明：
*		把数据存入FIFO
*	参数：
*		FIFO_LIST* pfifo  当前FIFO
*               uint8* pitem  当前FIFO指针
*	返回值：
*		 BOOL FALSE or TRUE 存入是否成功
*******************************************************/
BOOL fifo_set(FIFO_LIST* pfifo, uint8* pitem) 
{
 
	uint8* dst;
  //judge if it is full.
  if(pfifo->item_max_num==(pfifo->item_cnt+1))
  {
	  return FALSE;
  }
  
  dst=pfifo->pbuffer+pfifo->item_size*pfifo->tail;
  //memcpy(dst, pitem, pfifo->item_size);
  memcpy(dst, pitem, 5770);
  
  pfifo->tail=fifo_next_item(pfifo,pfifo->tail);
  pfifo->item_cnt++;

  
  return TRUE;

}
/****************************************************
*	函数名：BOOL fifo_get(FIFO_LIST* pfifo, uint8* pdest)
*	作者：  产品开发组
*	完成时间：2009-07-16
*	函数功能说明：
*		从FIFO中读取数据
*	参数：
*		FIFO_LIST* pfifo  当前FIFO
*               uint8* pdest  当前FIFO指针
*	返回值：
*		 BOOL FALSE or TRUE 读取是否成功
*******************************************************/
BOOL fifo_get(FIFO_LIST* pfifo, uint8* pdest)
{
   uint8* src;
  //judge if it is empty.
  if(0==pfifo->item_cnt)
    return FALSE;
  
  src=pfifo->pbuffer+pfifo->item_size*pfifo->head;  
  memcpy(pdest, src, pfifo->item_size);
  
  
  pfifo->head=fifo_next_item(pfifo,pfifo->head);
  pfifo->item_cnt--;      
  
   return TRUE;
}
/****************************************************
*	函数名：uint16 fifo_get_datacnt(FIFO_LIST* pfifo)
*	作者：  产品开发组
*	完成时间：2009-07-16
*	函数功能说明：
*		获取FIFO的长度
*	参数：
*		FIFO_LIST* pfifo  当前FIFO
*              
*	返回值：
*		uint16  长度
*******************************************************/
uint16 fifo_get_datacnt(FIFO_LIST* pfifo)
{
  return pfifo->item_cnt;
}

BOOL fifo_delete(FIFO_LIST* pfifo)
{
	 free((void *)pfifo);
	return TRUE;
}

#ifdef __cplusplus    // If used by C++ code, 
}          // we need to export the C interface
#endif