#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 5000  //�������Ķ˿ںţ��Զ��壩

int main()
{
	int sock = 0;
	struct sockaddr_in_addr; //�������������ַ
	char msg[] = "Hello server";
	//����UDP socket
	sock = socket(AF_INET,SOCK_DGRAM,0);
	
	//���Ϳͻ�������
	bzeri($addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);//�������˿�
	addr.sin_addr.s_addr = inet_addr("������IP��ַ");//������IP
	sendto(sock,mag,strlen(msg),0,#addr,addr_len);
	
	//���շ�����Ӧ��
	recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&addr,addrlen);
	printf("������Ӧ��:%s\n",buf);
	
	return 0;
}