#include<stdio.h>
#include"queue.h"
#include <string.h>
int main()
{
	Queue *que = NULL;
	char op = 0 ;
	//char msg [128];
	T msg;
	//1创建队列
	que = CreateQueue();
	
	while(1)
	{
		//显示队列操作菜单
		printf("1：进队\n");
		printf("2：出队\n");
		printf("3：显示\n");
		printf("请选择你需要的队列操作：\n");
		
		
		//3 接受用户选择操作选项
		scanf("%c", &op);
		
		//4 执行相应的队列操作
		switch(op)
		{
			case '1'://进队
				memset(msg,0,sizeof(msg));
				printf("请输入进队消息：\n");
				scanf("%s",msg);
				Push(que,msg);
				printf("=================\n");
				break;
			case '2'://出队
				Pop(que,msg);
				printf("=================\n");
				break;
			case '3'://显示
				Print(que);
				printf("=================\n");
				break;
			default:
				printf("你输入的选项无效！\n");
				break;
		}
		
		getchar();//去掉上次的回车
	}
		return 0 ;
}