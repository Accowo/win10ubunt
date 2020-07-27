#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>

#define MAXLINE 80
#define SERV_PORT 8000

int main() {
	
	struct sockaddr_in servaddr, cliaddr;
	int  listenfd, connfd;
	socklen_t cliaddr_len;
	char buf[MAXLINE];
	int n, i;
	char str[INET_ADDRSTRLEN];//接收客户端的IP地址
	//创建socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	//初始化服务器IP和端口
	bzero(&servaddr, sizeof(servaddr));	//结构体清零
	servaddr.sin_family = AF_INET;			//IPv4
	servaddr.sin_port = htons(SERV_PORT);	//port
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//ip
	//绑定套接字，IP和端口
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	//设置处于监听状态，并设置同时连接的客户端上限
	listen(listenfd, 20);
	//阻塞等待客户端连接
	printf("Accepting connections ...\n");
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		//读取客户端发来的数据
		n = read(connfd, buf, MAXLINE);
		printf("received form %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
		//小写转大写处理
		for (i = 0; i < n; i++) {
			buf[i] = toupper(buf[i]);
		}
		//将处理完的数据发回
		write(connfd, buf, n);
		close(connfd);
	}
	return 0;
}
