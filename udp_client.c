#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 5000  //服务器的端口号（自定义）

int main()
{
	int sock = 0;
	struct sockaddr_in_addr; //服务器的网络地址
	char msg[] = "Hello server";
	//创建UDP socket
	sock = socket(AF_INET,SOCK_DGRAM,0);
	
	//发送客户端请求
	bzeri($addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);//服务器端口
	addr.sin_addr.s_addr = inet_addr("服务器IP地址");//服务器IP
	sendto(sock,mag,strlen(msg),0,#addr,addr_len);
	
	//接收服务器应答
	recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&addr,addrlen);
	printf("服务器应答:%s\n",buf);
	
	return 0;
}