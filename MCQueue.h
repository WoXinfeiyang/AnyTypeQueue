
#ifndef _MCQUEUE_H_
#define _MCQUEUE_H_

#include "Typedef.h"

// ����������ݽṹ
typedef struct _MC_QUEUE
{
    UINT32 itemBufferAddr;      // �ⲿ�����׵�ַ
    UINT16 bufferSize;          // �����С
    UINT8  itemSize;            // Ԫ�ش�С
    UINT16 headPtr;             // ����ͷ
    UINT16 tailPtr;             // β
    UINT16 queueSize;           // ����Ԫ�ظ���
    BOOL   hasBeenInit;         // �����Ƿ񱻳�ʼ��
}MC_QUEUE;

// ���г�ʼ��
void   MCQueueInit(MC_QUEUE *queue, void *itemBuffer, UINT8 itemSize, UINT16 bufferSize);
// ������
BOOL   MCIsQueueFull(MC_QUEUE *queue);
// ���п�
BOOL   MCIsQueueEmpty(MC_QUEUE *queue);
// ��ö���Ԫ�ظ���
UINT16 MCQueueGetSize(MC_QUEUE *queue);
// ��ն���
void   MCQueueClear(MC_QUEUE *queue);
// ��Ԫ�������
BOOL   MCQueueInput(MC_QUEUE *queue, void *item);
// ����ͷԪ�س�����
void *MCQueueOutput(MC_QUEUE *queue);
// ��ȡָ����ŵĶ���Ԫ��
void *MCQueuePeekItem(MC_QUEUE *queue, UINT16 itemIndex);

#endif // _MCQUEUE_H_
