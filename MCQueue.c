
#include<stdio.h>
#include <string.h>
#include<malloc.h>

#include "MCQueue.h"


/*
�������ƣ�
����������
    UINT32 itemBufferAddr;      // �ⲿ�����׵�ַ
    UINT16 bufferSize;          // �����С,�����������еĴ�С
    UINT8  itemSize;            // Ԫ�ش�С
    UINT16 headPtr;             // ����ͷ
    UINT16 tailPtr;             // β
    UINT16 queueSize;           // ����Ԫ�ظ���
    BOOL   hasBeenInit;         // �����Ƿ񱻳�ʼ��
��������ֵ����ȡ����Ԫ�صĵ�ַ
˵����
*/
void MCQueueInit(MC_QUEUE *queue, void *itemBuffer, UINT8 itemSize, UINT16 bufferSize)
{
    if(queue==NULL)
	{
		return;
	} 
    queue->itemBufferAddr =(UINT32)itemBuffer;// �ⲿ�����ַ
    queue->bufferSize  = bufferSize;// �ⲿ�����С,�����������еĴ�С
    queue->itemSize    = itemSize*sizeof(CHAR);//������һ��Ԫ����ռ�ڴ�Ĵ�С(��λ���ֽ�)
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
	/*���ַ����Զ��г���*/
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
		printf("\n����δ��ʼ�����߶���ָ��Ϊ��!����!\n");
		return FALSE;
	}
	
	if(MCIsQueueFull(queue)==TRUE)
    {
        printf("\n�����������޷��������!\n");
        return FALSE;
    }


    memcpy(queue->itemBufferAddr+queue->tailPtr*queue->itemSize,item,queue->itemSize);

    queue->tailPtr=(queue->tailPtr+1)%queue->bufferSize;
    queue->queueSize++;// ����Ԫ������
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
        printf("\n����Ϊ�գ��޷�������!\n");
        return FALSE;
    }
    queue->headPtr=(queue->headPtr+1)%queue->itemSize;
    queue->queueSize--;
	return queue->itemBufferAddr+(queue->headPtr-1)*queue->itemSize;
   
}

/*
�������ƣ�MCQueuePeekItem
����������
       queue-------------���е�ַ
       itemIndex---------Ҫ��ȡ����Ԫ�ص���ţ�ָ�룩
��������ֵ����ȡ����Ԫ�صĵ�ַ
˵����itemIndex��Χ��[0,queue->itemSize]
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
