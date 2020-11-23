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
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char str[100];
	int i;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.20.44.26");
	address.sin_port = htons(4114);
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr*)&address, len);

	if( result == -1 )
	{
		perror("oops: client3");
		exit(1);
	}

	while(1)
	{
		printf(">>");
		scanf("%s",str);

		write(sockfd, str, strlen(str));

		if(strcmp(str,"quit") == 0)
		{
			close(sockfd);
			break;
		}
		
		memset(str, 0, strlen(str));
	}

	return 0;
}
		
