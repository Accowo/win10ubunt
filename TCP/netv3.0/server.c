#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

void clear_child(int signum) {
	int stat_val;
	pid_t pid = waitpid(-1, &stat_val, WNOHANG);
	if (WIFEXITED(stat_val)) 
		 printf("Son server pid:%d exited with code %d\n", pid, WEXITSTATUS(stat_val)); 
	else if (WIFSIGNALED(stat_val))
		 printf("Son server pid:%d terminated abnormally, signal %d\n", pid, WTERMSIG(stat_val));
}

int main() {
	
	signal(SIGCHLD, clear_child);
	struct sockaddr_in servaddr, cliaddr;
	int  listenfd, connfd;
	socklen_t cliaddr_len;
	char buf[MAXLINE];
	int n, i;
	char str[INET_ADDRSTRLEN];//接收客户端的IP地址
	pid_t pid;
	//创建socket
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	//初始化服务器IP和端口
	bzero(&servaddr, sizeof(servaddr));	//结构体清零
	servaddr.sin_family = AF_INET;			//IPv4
	servaddr.sin_port = htons(SERV_PORT);	//port
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//ip
	//绑定套接字，IP和端口
	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	//设置处于监听状态，并设置同时连接的客户端上限
	Listen(listenfd, 20);
	//阻塞等待客户端连接
	printf("Accepting connections ...\n");
	while (1) {
		cliaddr_len = sizeof(cliaddr);
		//阻塞等待下一个客户端的连接
		connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		pid = fork();
		if (pid < 0) {
			perror("call to fork");
			exit(1);
		} else if (pid == 0) {
			//子进程不需要listenfd,父进程在负责监听listenfd
			Close(listenfd);
			while (1) {
				//读取客户端发来的数据
				n = Read(connfd, buf, MAXLINE);
				if (n == 0) {
					printf("the other side has been closed.\n");
					break;
				} else {
					printf("received form %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
					//小写转大写处理
					for (i = 0; i < n; i++) {
						buf[i] = toupper(buf[i]);
					}
					//将处理完的数据发回
					Write(connfd, buf, n);
				}

			}
			Close(connfd);
			exit(0);
		} else {//父进程一直是同一个父进程
			//父进程不需要connfd，子进程在负责connfd接待客户端
			Close(connfd);
		}
	}
	Close(listenfd);
	return 0;
}
