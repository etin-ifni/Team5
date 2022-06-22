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
 
int main() {
    struct sockaddr_in server_sockaddr;//声明服务器socket存储结构
    int sin_size,recvbytes;
    int sockfd,client_fd;//socket描述符
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
 
    
	int accept_fd = 0;

    //用来保存客户端信息的结构体
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);

    printf("Waiting for the client\n");
    if ((accept_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
    {
        perror("accept error");
        exit(-1);
    }
	while (1)
    {
        char buf[128] = {0};
        //收
        printf("client >  ");
        fflush(stdout);
        recv(accept_fd, buf, 128, 0);
        printf("%s\n", buf);
        if (strcmp(buf, "quit") == 0)
        {
            //关闭文件描述符
            close(sockfd);
            close(accept_fd);
            break;
        }

        //发
        printf("input  > ");
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        send(accept_fd, buf, 128, 0);
        if (strcmp(buf, "quit") == 0) // break;
        {
            //关闭文件描述符
            close(sockfd);
            close(accept_fd);
            break;
        }
    }
 
    //6.关闭
    close(sockfd);
 
}