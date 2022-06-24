#ifndef _queue_H
#define _queue_H

#define MAX_MSG 128     //消息最大长度
//typedef char T[MAX_MSG] ;
typedef char T[MAX_MSG];
//定义队列
typedef struct queue Queue;
struct queue{
    T data;        //保存该节点消息
    Queue* next;  //指向下一节点
};

//队列长度
static int length=0;
//创建队列
Queue* CreateQueue();
//删除队列
void DestroyQueue(Queue* h);
//进队操作
int Push(Queue* h, T t);
//出队操作
int Pop(Queue* h, T t);
//显示队列元素
void Print(Queue* h);
#endif