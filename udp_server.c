#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

#define MYPORT 5000
int main()
{
	int sock = 0;
	struct sockaddr_in my_addr,cl_addr;
	int addrlen = sizeof(cl_addr);
	char buf[64] = {0};
	char msg[64] = {0};
	//1 创建UDP socket
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if (sock == -1) { //检查是否正常初始化socket
        printf("socket failed!\n");
        return -1;
    }
	while(1){
		//从控制台输入聊天信息
		//printf("输入向客户端发送的信息:\n"); 
		//2 绑定ip地址与端口号
		bzero(&my_addr, sizeof(my_addr));
		my_addr.sin_family = AF_INET; //地址结构的协议族
		my_addr.sin_port = htons(MYPORT); //地址结构的端口地址，网络字节序
		my_addr.sin_addr.s_addr = INADDR_ANY;//服务器IP地址
		if (bind(sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) { // 判断是否绑定成功
			printf("bind failed!\n");
			return -1;
		}
		//3 接收客户端请求
		recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&cl_addr, &addrlen);
		printf("客户端请求: %s",buf);
	
		//4 发送服务器应答
		sendto(sock,msg,strlen(msg),0,(struct sockaddr *)&cl_addr, sizeof(cl_addr));
	}
	return 0;
}