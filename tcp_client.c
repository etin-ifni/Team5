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
 
int main(int argc,char *argv[]) {
    int sockfd,sendbytes;
    struct sockaddr_in serv_addr;//��Ҫ���ӵķ�������ַ��Ϣ
 
    //1.����socket
    //AF_INET ��ʾIPV4
    //SOCK_STREAM ��ʾTCP
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
    }
 
    //����������ַ��Ϣ
    serv_addr.sin_family 	= AF_INET; //������IPЭ��: IPV4
    serv_addr.sin_port 		= htons(SERVPORT); //�����Ķ˿ں�
    serv_addr.sin_addr.s_addr   = inet_addr("192.168.43.69"); //������IP��ַ: ʵ�ʵķ�����IP��ַ
    bzero(&(serv_addr.sin_zero),8); //������8�ֽ�����
 
    //2.����Է�������������Ϣ
    //��������,��Ҫ��sockaddr_in���͵����ݽṹǿ��ת��Ϊsockaddr
    if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))) < 0) {
        perror("Connection Fail!");
        exit(1);
    }
 
    printf("Connection successful!!! \n");
 
    //3.������Ϣ����������
     while (1)
    {
        char bu[128] = {0};
        //��
        printf("input  > ");
        scanf("%s", bu);
        send(sockfd, bu, 128,0);
        if (strcmp(bu,"quit")==0)
        {
            //�ر��ļ�������
            close(sockfd);
            break;
        }

        //��
        memset(bu, 0, sizeof(bu));
        printf("server > ");
        fflush(stdout);
	    recv(sockfd, bu, 128,0);
        printf("%s\n", bu);
        if (strcmp(bu,"quit")==0)
        {
            //�ر��ļ�������
            close(sockfd);
            break;
        }
    
    }



 
    //4.�ر�
    close(sockfd);
 
}