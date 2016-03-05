#include<stdio.h>
#include"MCQueue.h"

typedef struct _Nod
{
INT32 data_int;
CHAR data_char[20];
}Nod;

void main()
{
MC_QUEUE gQueue;
Nod gArray1[10];
Nod gArray2[10]=
{
	{01,"zhao"},
	{02,"Qian"},
	{03,"Sun"},
	{04,"Li"},
	{05,"zhou"},
	{06,"Wu"},
	{07,"zheng"},
	{8,"wang"},
	{9,"feng"},
	{00,"cheng"}
};
Nod *gMsg;

INT16 i=0;

MCQueueInit(&gQueue,gArray1,sizeof(Nod),5);

for(i=0;i<10;i++)
	
{
	MCQueueInput(&gQueue,&gArray2[i]);
	//MCQueueInput(0,&gArray2[i]);
	printf("入队元素：");
	gMsg=(Nod*)MCQueuePeekItem(&gQueue,i);
	printf("%d,%s\n",gMsg->data_int,gMsg->data_char);
}

//第一次出队
printf("出队元素：\n");
gMsg=(Nod*)MCQueueOutput(&gQueue);
printf("%d,%s\n",gMsg->data_int,gMsg->data_char);

printf("获取元素：\n");
for(i=0;i<10/*MCQueueGetSize(&gQueue)*/;i++)
	{
	gMsg=(Nod*)MCQueueOutput(&gQueue);
	//gMsg=(Nod*)MCQueuePeekItem(&gQueue,i);
	printf("%d,%s\n",gMsg->data_int,gMsg->data_char);
	}	

}