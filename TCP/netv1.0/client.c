#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[]){

	struct sockaddr_in servaddr;
	int sockfd;
	char *str;//要发送的信息
	char buf[MAXLINE];
	int n;

	if (argc != 2) {
		fputs("usage: ./client message\n", stderr);
		exit(1);
	}
	str = argv[1];
	//创建套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//初始化服务器IP和PORT
	bzero((struct sockaddr *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//发送连接服务器的请求,阻塞等待服务器应答
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	//发送信息
	write(sockfd, str, strlen(str));
	//读取服务器返回的信息
	n = read(sockfd, buf, sizeof(buf));
	//将接受到的信息输出到屏幕
	printf("Response from server:\n");
	write(STDOUT_FILENO, buf, n);

	close(sockfd);

	return 0;
}
