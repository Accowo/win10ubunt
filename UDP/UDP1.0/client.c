#include "wrap.h" 

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[]){

	struct sockaddr_in servaddr;
	int sockfd;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int n;
	socklen_t servaddr_len;
	//创建套接字
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	//初始化服务器IP和PORT
	bzero((struct sockaddr *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (fgets(buf, sizeof(buf), stdin) != NULL) {	//键盘读取
		//发送信息给服务器
		n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		if (n == -1) {
			perr_exit("sendto error");
		}
		//读取服务器返回的信息
		n = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, 0);
		if (n == -1) {
			perr_exit("recvfrom error");
		} 
		//将接受到的信息输出到屏幕
		Write(STDOUT_FILENO, buf, n);
		
	}
	Close(sockfd);

	return 0;
}
