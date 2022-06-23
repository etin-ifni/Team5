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

//聊天任务声明
void *chatfunc(void* arg);

int main ()
{	
	//1. 创建TCP socket
	//int sockfd = 0;
	//sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2. 绑定IP地址与端口号
	//bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))
	//3. 创建监听客户端连接队列
	//listen(sockfd, 10);
	
	struct sockaddr_in server_sockaddr;//声明服务器socket存储结构
    int sin_size,recvbytes;
    int sockfd,client_fd;//socket描述符
    char buf[MAXDATASIZE];//传输的数据
 
     //1.socket
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
    server_sockaddr.sin_addr.s_addr 	= INADDR_ANY;//本主机的任意IP都可以使用
    bzero(&(server_sockaddr.sin_zero),8);//保留的8字节置零
 
    //2.绑定 fd与 端口和地址
    if((bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))) < 0) {
        perror("bind");
        exit(-1);
    }
 
    printf("bind successful !\n");
 
    //3.监听
    if(listen(sockfd,BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

 
    printf("listening ... \n");
	
	

	while(1)
	{		
		//4. 等待并建立客户端的连接
		//connfd = accept(sockfd, (struct sockaddr*)&clientaddr,socklen_t addrlen);
	
		//5. 为已连接客户端创建聊天任务
		//create_task(chattask, (void*)&connfd);
		
		struct sockaddr_in client_addr;
		memset(&client_addr, 0, sizeof(client_addr));
		socklen_t client_addr_len = sizeof(client_addr);
	
		//4. 等待并建立客户端的连接
		int connfd = 0;
		printf("Waiting for the client\n");
		connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
	
		//5. 为已连接客户端创建聊天任务
		create_task(chatfunc, (void*)&connfd);

	}
	
	close(sockfd);
	
	return 0;
}

//聊天任务实现
void *chatfunc(void* arg)
{
	int connfd = *(int*)arg; //连接套接字
	char buf[64] = {0};
	char msg[64] = {0};
	
	while(1)
	{
	/*
		//先情空缓存
		memset(msg, 0 , sizeof(msg));
		memset(buf, 0 , sizeof(buf));
		
		
		
		//从服务器收聊天信息
		recv(connfd, buf, sizeof(buf), 0);
		printf("from client: %s\n", buf);
		
		
		//从控制台获取聊天输入
		printf("please chat:");
		scanf("%s", msg);
		
		//向服务器发聊天信息
		send(connfd, msg, strlen(msg), 0);
	*/
		char buf[128] = {0};
        //收
        printf("client >  ");
        //fflush(stdout);
		
        recv(connfd, buf, 128, 0);
        printf("%s\n", buf);
		
        if (strcmp(buf, "quit") == 0)
        {
            //关闭文件描述符
           // close(sockfd);
            close(connfd);
            break;
        }

        //发
        printf("input  > ");
		fflush(stdout);
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        send(connfd, buf, strlen(buf), 0);
		
        if (strcmp(buf, "quit") == 0) // break;
        {
            //关闭文件描述符
          //  close(sockfd);
            close(connfd);
            break;
        }
		
	}
	
	close(connfd);
}
