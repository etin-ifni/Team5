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

//TCP聊天客户端
int main ()
{
	char chat[64] = {0};
	char buf[64] = {0};
	
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
	
	//3. 循环聊天
	while(1)
	{
		
		//先情空缓存
		memset(chat, 0 , sizeof(chat));
		memset(buf, 0 , sizeof(buf));
		
		//从控制台获取聊天输入
		printf("please chat:");
		scanf("%s", chat);
		
		//向服务器发聊天信息
		send(sockfd, chat, strlen(chat), 0);
		
		//从服务器收聊天信息
		recv(sockfd, buf, sizeof(buf), 0);
		printf("from server: %s\n", buf);
		
		/*
		char bu[128] = {0};
        //发
        printf("input  > ");
        scanf("%s", bu);
        send(sockfd, bu, 128,0);
        if (strcmp(bu,"quit")==0)
        {
            //关闭文件描述符
            close(sockfd);
            break;
        }

        //收
        memset(bu, 0, sizeof(bu));
        printf("server > ");
        fflush(stdout);
	    recv(sockfd, bu, 128,0);
        printf("%s\n", bu);
        if (strcmp(bu,"quit")==0)
        {
            //关闭文件描述符
            close(sockfd);
            break;
        }
		*/
		
	}
	
	close(sockfd);	
	
	return 0;
}