#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 5000  //端口号（自定义）

int main ()
{
	int sock = 0;
	struct sockaddr_in_my_addr;
	cha msg[] = "Hello client";
	//创建UDP socket
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1){
		peeror("socket");//检查是否正常初始化socket
		exit(EXIT_FAILURE);
		
		return -1;
	}
	
	//绑定IP地址与端口号
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;//地址结构的协议族
	my_addr.sin_port = htons(MYPORT);//地址结构的端口地址，网络字节序
	my_addr.sin_addr = htonl(INADDR_ANY);//服务器IP地址
	
	if (bind(sock, (struct sockaddr *) &my_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
		
		return -1;
	}
	
	//接收客户端请求
	recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&cl_addr,&addrlen);
	printf("客户端请求:%s",buf);
	
	
	//发送服务器应答
	sendto(sock,msg,strlen(msg),0,(struct sockaddr *)&cl_addr,sizeof(cl_addr));
	
	return 0;
}