
#include<stdio.h>
#include <string.h>
#include<malloc.h>

#include "MCQueue.h"


/*
函数名称：
函数参数：
    UINT32 itemBufferAddr;      // 外部数组首地址
    UINT16 bufferSize;          // 数组大小,即所创建队列的大小
    UINT8  itemSize;            // 元素大小
    UINT16 headPtr;             // 队列头
    UINT16 tailPtr;             // 尾
    UINT16 queueSize;           // 队列元素个数
    BOOL   hasBeenInit;         // 队列是否被初始化
函数返回值：获取队列元素的地址
说明：
*/
void MCQueueInit(MC_QUEUE *queue, void *itemBuffer, UINT8 itemSize, UINT16 bufferSize)
{
    if(queue==NULL)
	{
		return;
	} 
    queue->itemBufferAddr =(UINT32)itemBuffer;// 外部数组地址
    queue->bufferSize  = bufferSize;// 外部数组大小,即所创建队列的大小
    queue->itemSize    = itemSize*sizeof(CHAR);//队列中一个元素所占内存的大小(单位：字节)
    queue->headPtr     = 0;
    queue->tailPtr     = 0;
    queue->queueSize   = 0;
    queue->hasBeenInit = TRUE;
}

BOOL MCIsQueueFull(MC_QUEUE *queue)
{
    if((queue->hasBeenInit!=TRUE)||(queue==NULL))
	{
		return FALSE;
	}
	//if((queue->tailPtr+1)%queue->bufferSize==queue->headPtr)
    if(queue->queueSize==queue->bufferSize)
	    return TRUE;
    else 
        return FALSE;
}

BOOL MCIsQueueEmpty(MC_QUEUE *queue)
{
    if((queue->hasBeenInit!=TRUE)||(queue==NULL))
    
	{
		return FALSE;
	}

    if(queue->queueSize==0)
	//if(queue->headPtr==queue->tailPtr)
        return TRUE;
    else
        return FALSE;
}

UINT16 MCQueueGetSize(MC_QUEUE *queue)
{
    UINT16 ret;

	if((queue->hasBeenInit!=TRUE)||(queue==NULL))
	{
	    return FALSE;
	}
	/*两种方法对队列长队*/
    //ret=(queue->tailPtr -queue->headPtr+queue->bufferSize)%queue->bufferSize;
	ret=queue->queueSize;
    return ret;
}

void MCQueueClear(MC_QUEUE *queue)
{
    if((queue->hasBeenInit!=TRUE)||(queue==NULL))
	{
		return;
	}
	queue->headPtr     = 0;
    queue->tailPtr     = 0;
    queue->queueSize   = 0;
}

BOOL MCQueueInput(MC_QUEUE *queue, void *item)
{
    if((queue->hasBeenInit!=TRUE)||(queue==NULL))
	{
		printf("\n队列未初始化或者队列指正为空!请检查!\n");
		return FALSE;
	}
	
	if(MCIsQueueFull(queue)==TRUE)
    {
        printf("\n队列已满，无法继续入队!\n");
        return FALSE;
    }


    memcpy(queue->itemBufferAddr+queue->tailPtr*queue->itemSize,item,queue->itemSize);

    queue->tailPtr=(queue->tailPtr+1)%queue->bufferSize;
    queue->queueSize++;// 队列元素增加
    return TRUE;
}

void *MCQueueOutput(MC_QUEUE *queue)
{
    if((queue->hasBeenInit!=TRUE)||(queue==NULL))
	{
		return FALSE;
	}
    
	if(MCIsQueueEmpty(queue)==TRUE)
    {
        printf("\n队列为空，无法出队列!\n");
        return FALSE;
    }
    queue->headPtr=(queue->headPtr+1)%queue->itemSize;
    queue->queueSize--;
	return queue->itemBufferAddr+(queue->headPtr-1)*queue->itemSize;
   
}

/*
函数名称：MCQueuePeekItem
函数参数：
       queue-------------队列地址
       itemIndex---------要获取队列元素的序号（指针）
函数返回值：获取队列元素的地址
说明：itemIndex范围：[0,queue->itemSize]
*/
void *MCQueuePeekItem(MC_QUEUE *queue, UINT16 itemIndex)
{
    //UINT32 ret;
    INT32 index;

    if((queue->hasBeenInit!=TRUE)||(queue==NULL)||(itemIndex>queue->bufferSize))
	{
		return FALSE;
	}

    index=(queue->headPtr+itemIndex)%queue->bufferSize;	
    return queue->itemBufferAddr+index*queue->itemSize;
}
