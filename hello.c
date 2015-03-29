#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int listenfd,connfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	pid_t childpid;
	char mesg[1000];
	char resp[1024];
	int rn;


	listenfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,1024);

	
	for(;;) {

		clilen=sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

		if ((childpid = fork()) == 0) {
			close (listenfd);

			for(;;) {
				n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
				printf("-------------------------------------------------------\n");
				mesg[n] = 0;
				printf("Received the following:\n");
				printf("%s",mesg);
				printf("-------------------------------------------------------\n");
				
				rn = sprintf(resp, "Hello %s!\n", mesg);
				
				printf("response: \n");
				printf(resp);
				printf("\n-------------------------------------------------------\n");
				sendto(connfd,resp, rn ,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
			}
		}
		close(connfd);
	}
}

