#include <stdio.h>
#include "queue.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

 
#define SERVPORT 5051
#define BACKLOG 10
#define MAXDATASIZE 15

//消息处理任务声明
void *msgfunc(void* arg);

int main ()
{	
	struct sockaddr_in server_sockaddr;//声明服务器socket存储结构
	struct sockaddr_in client_addr;
    int sin_size,recvbytes;
    int sockfd,connfd;//socket描述符
    char buf[MAXDATASIZE];//传输的数据
 
     //1.建立socket
    //AF_INET 表示IPV4
    //SOCK_STREAM 表示TCP
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("Socket");
        exit(1);
    }
 
    printf("Socket successful!,sockfd=%d\n",sockfd);
 
    //以sockaddt_in结构体填充socket信息
    server_sockaddr.sin_family 		= AF_INET;//IPv4
    server_sockaddr.sin_port 		= htons(SERVPORT);//端口
    server_sockaddr.sin_addr.s_addr 	= htonl(INADDR_ANY);//本主机的任意IP都可以使用
    bzero(&(server_sockaddr.sin_zero),8);//保留的8字节置零
 
    //2.绑定 fd与 端口和地址
    if((bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))) < 0) {
        perror("bind");
        exit(-1);
    }
 
    printf("bind successful !\n");
	
	
	if(listen(sockfd,BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

 
    printf("listening ... \n");

	while(1)
	{		
		//4. 等待并建立客户端的连接
		//用来保存客户端信息的结构体
		memset(&client_addr, 0, sizeof(client_addr));
		socklen_t client_addr_len = sizeof(client_addr);

		printf("Waiting for the client\n");
		if ((connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
		{
			perror("accept error");
			exit(-1);
		}
	
		//5. 为已连接客户端创建消息处理任务
		create_task(msgfunc, (void*)&connfd);
		
		
	}
	
	close(sockfd);
	
	return 0;
}

//消息处理任务实现
void *msgfunc(void* arg)
{
	int connfd = *(int*)arg; //连接套接字
	Queue *que = NULL;
	T msg = {0};
	
	//1.创建消息队列
	que = CreateQueue();
	
	while(1)
	{
		//先情空缓存
		memset(msg, 0 , sizeof(msg));
		
		//接收对方消息
		if(-1 == recv(connfd, msg, sizeof(msg), 0))
		{
			printf("Eooro");
			//continue;
			break;
		};
		
		//对方确认消息接收完备
		if (0==strcmp("exit",msg))
		{
			break;
		};
		
		printf("push:%s\n", msg);
		Push(que, msg);//进队
		
		
	}
	
	//显示所有已接收消息
	printf("==================\n");
	Print(que);
	//释放队列
	DestroyQueue(que);
	
	close(connfd);
}
