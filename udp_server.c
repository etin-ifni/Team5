#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 5000  //�˿ںţ��Զ��壩

int main ()
{
	int sock = 0;
	struct sockaddr_in_my_addr;
	cha msg[] = "Hello client";
	//����UDP socket
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1){
		peeror("socket");//����Ƿ�������ʼ��socket
		exit(EXIT_FAILURE);
		
		return -1;
	}
	
	//��IP��ַ��˿ں�
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;//��ַ�ṹ��Э����
	my_addr.sin_port = htons(MYPORT);//��ַ�ṹ�Ķ˿ڵ�ַ�������ֽ���
	my_addr.sin_addr = htonl(INADDR_ANY);//������IP��ַ
	
	if (bind(sock, (struct sockaddr *) &my_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
		
		return -1;
	}
	
	//���տͻ�������
	recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&cl_addr,&addrlen);
	printf("�ͻ�������:%s",buf);
	
	
	//���ͷ�����Ӧ��
	sendto(sock,msg,strlen(msg),0,(struct sockaddr *)&cl_addr,sizeof(cl_addr));
	
	return 0;
}