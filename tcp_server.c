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
    struct sockaddr_in server_sockaddr;//����������socket�洢�ṹ
    int sin_size,recvbytes;
    int sockfd,client_fd;//socket������
    char buf[MAXDATASIZE];//���������
 
     //1.����socket
    //AF_INET ��ʾIPV4
    //SOCK_STREAM ��ʾTCP
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("Socket");
        exit(1);
    }
 
    printf("Socket successful!,sockfd=%d\n",sockfd);
 
    //��sockaddt_in�ṹ�����socket��Ϣ
    server_sockaddr.sin_family 		= AF_INET;//IPv4
    server_sockaddr.sin_port 		= htons(SERVPORT);//�˿�
    server_sockaddr.sin_addr.s_addr 	= INADDR_ANY;//������������IP������ʹ��
    bzero(&(server_sockaddr.sin_zero),8);//������8�ֽ�����
 
    //2.�� fd�� �˿ں͵�ַ
    if((bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))) < 0) {
        perror("bind");
        exit(-1);
    }
 
    printf("bind successful !\n");
 
    //3.����
    if(listen(sockfd,BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

 
    printf("listening ... \n");
 
    
	int accept_fd = 0;

    //��������ͻ�����Ϣ�Ľṹ��
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
        //��
        printf("client >  ");
        fflush(stdout);
        recv(accept_fd, buf, 128, 0);
        printf("%s\n", buf);
        if (strcmp(buf, "quit") == 0)
        {
            //�ر��ļ�������
            close(sockfd);
            close(accept_fd);
            break;
        }

        //��
        printf("input  > ");
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        send(accept_fd, buf, 128, 0);
        if (strcmp(buf, "quit") == 0) // break;
        {
            //�ر��ļ�������
            close(sockfd);
            close(accept_fd);
            break;
        }
    }
 
    //6.�ر�
    close(sockfd);
 
}