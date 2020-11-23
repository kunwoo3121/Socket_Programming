#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	unlink("server_socket");
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(4114);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);

	listen(server_sockfd, 5);

	while(1)
	{
		char str[100];
		int i;

		printf("server waiting\n");

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
	
		while(1)
		{
			read(client_sockfd, str, 100);
		
			if(strcmp(str,"quit") == 0) 
			{
				close(client_sockfd);
				printf("종료합니다.\n");
				break;
			}

			printf("%s\n",str);

			memset(str,0,strlen(str));
		}

		close(server_sockfd);

		break;
	}
}
