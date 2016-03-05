
#ifndef _MCQUEUE_H_
#define _MCQUEUE_H_

#include "Typedef.h"

// 定义队列数据结构
typedef struct _MC_QUEUE
{
    UINT32 itemBufferAddr;      // 外部数组首地址
    UINT16 bufferSize;          // 数组大小
    UINT8  itemSize;            // 元素大小
    UINT16 headPtr;             // 队列头
    UINT16 tailPtr;             // 尾
    UINT16 queueSize;           // 队列元素个数
    BOOL   hasBeenInit;         // 队列是否被初始化
}MC_QUEUE;

// 队列初始化
void   MCQueueInit(MC_QUEUE *queue, void *itemBuffer, UINT8 itemSize, UINT16 bufferSize);
// 队列满
BOOL   MCIsQueueFull(MC_QUEUE *queue);
// 队列空
BOOL   MCIsQueueEmpty(MC_QUEUE *queue);
// 获得队列元素个数
UINT16 MCQueueGetSize(MC_QUEUE *queue);
// 清空队列
void   MCQueueClear(MC_QUEUE *queue);
// 新元素入队列
BOOL   MCQueueInput(MC_QUEUE *queue, void *item);
// 队列头元素出队列
void *MCQueueOutput(MC_QUEUE *queue);
// 获取指定序号的队列元素
void *MCQueuePeekItem(MC_QUEUE *queue, UINT16 itemIndex);

#endif // _MCQUEUE_H_
