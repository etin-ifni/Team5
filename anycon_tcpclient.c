#include <stdio.h>
#include "queue.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVPORT 5051

//TCP异步并发服务器测试客户端
int main ()
{
	char msg[128] = {0};
	
	int sockfd,sendbytes;
    struct sockaddr_in serv_addr;//需要连接的服务器地址信息
 
    //1.创建socket
    //AF_INET 表示IPV4
    //SOCK_STREAM 表示TCP
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
    }
 
    //填充服务器地址信息
    serv_addr.sin_family 	= AF_INET; //网络层的IP协议: IPV4
    serv_addr.sin_port 		= htons(SERVPORT); //传输层的端口号
    serv_addr.sin_addr.s_addr   = inet_addr("192.168.43.69"); //网络层的IP地址: 实际的服务器IP地址
    bzero(&(serv_addr.sin_zero),8); //保留的8字节置零
 
    //2.发起对服务器的连接信息
    //三次握手,需要将sockaddr_in类型的数据结构强制转换为sockaddr
    if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))) < 0) {
        perror("Connection Fail!");
        exit(1);
    }
 
    printf("Connection successful!!! \n");

	//3. 循环发送
	while(1)
	{
		//先情空缓存
		memset(msg, 0 , sizeof(msg));
		
		//从控制台获取消息输入
		printf("please input:");
		scanf("%s", msg);
		
		if ('q' == msg[0])
		{
			break; //消息输入结束
		}
		else
		{
			//向服务器发信息
			send(sockfd, msg, strlen(msg), 0);
		}
	}
	
	close(sockfd);	
	
	return 0;
}