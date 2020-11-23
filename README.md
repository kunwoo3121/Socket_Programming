# Socket_Programming

* Socket Programming을 이용하여 client와 server 프로그램을 만든다.  
  
* 조건
```
1) Client 프로그램에서 문자열을 입력하면 Server 프로그램에서 그 문자열을 출력한다.
2) Client 프로그램에서 quit을 입력하면 client와 server 프로그램 모두 종료한다.
```

## client 프로그램
```.c
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
```

## server 프로그램
```.c
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
```

## 실행 결과 
* Client의 화면  
![client](https://user-images.githubusercontent.com/28796089/100019368-41f05500-2e21-11eb-8390-d208b05335bc.JPG)  
  
* Server의 화면  
![server](https://user-images.githubusercontent.com/28796089/100019371-4288eb80-2e21-11eb-9788-30581c469604.JPG)  
  
```
Client에서 입력한 문자열이 Server에서 잘 출력되는 모습을 볼 수 있고 quit를 입력하면 둘 다 종료되는 모습을 볼 수 있다.

Client에서 입력할 수 있는 문자열의 길이를 100으로 해두었기 때문에 그보다 긴 문자열을 입력할 수는 없다.

```
