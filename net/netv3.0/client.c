#include "wrap.h" 

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[]){

	struct sockaddr_in servaddr;
	int sockfd;
//	char *str;//要发送的信息
	char buf[MAXLINE];
	int n;
/********************************************************
	if (argc != 2) {
		fputs("usage: ./client message\n", stderr);
		exit(1);
	}
	str = argv[1];
*******************************************************/

	//创建套接字
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	//初始化服务器IP和PORT
	bzero((struct sockaddr *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//发送连接服务器的请求,阻塞等待服务器应答
	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	while (fgets(buf, sizeof(buf), stdin) != NULL) {	//键盘读取
		//发送信息
		Write(sockfd, buf, strlen(buf));
		//读取服务器返回的信息
		n = Read(sockfd, buf, sizeof(buf));
		if (n == 0) {
			printf("the other side has been closed.\n");
			break;
		} else {
			//将接受到的信息输出到屏幕
			Write(STDOUT_FILENO, buf, n);
		}
	}
/*****************************************
	//发送信息
	Write(sockfd, str, strlen(str));
	//读取服务器返回的信息
	n = Read(sockfd, buf, sizeof(buf));
	//将接受到的信息输出到屏幕
	printf("Response from server:\n");
	Write(STDOUT_FILENO, buf, n);
********************************************/
	Close(sockfd);

	return 0;
}
