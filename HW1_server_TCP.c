#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#define PortNumber 5555

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr, client_addr;
    struct  timeval start;
    struct  timeval end;

    int sock, byte_recv, byte_sent, recfd;
    char buffer[50];
    char buffer_response[50] = "Welcome!\n";
    unsigned int server_addr_length = sizeof(server_addr), client_addr_length = sizeof(client_addr);

	bzero(&server_addr, server_addr_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PortNumber);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
		  printf("Error creating socket\n");
    else
		  printf("Socket creating successfully\n");

    if (bind(sock, (struct sockaddr*)&server_addr, server_addr_length) == -1)
    {
	    printf("Bind error!\n");
		close(sock);
		exit(-1);
    }
    else
       printf("Bind successfully.\n");

	if ( listen(sock, 20) == -1)
	{
		printf("Listen failed\n");
		close(sock);
	}
	else 
		printf("Listen successfully.\n");

	if((recfd = accept(sock, (struct sockaddr *)&client_addr, &client_addr_length)) == -1)
	{
		printf("accept failed\n");
		close(sock);
		//break;
	}
	else printf("accept successfully\n");
	
	/* Receive */
	byte_recv = recv(recfd, buffer, sizeof(buffer), 0);

	/* time start */
	gettimeofday(&start,NULL);

	if (byte_recv < 0)
		printf("Receive Failed\n");

	printf("Data:%s\n", buffer);
		  
	byte_sent = send(recfd, buffer_response, sizeof(buffer_response), 0);
	
	if (byte_sent < 0) 
		printf("Error sending packet\n");

	gettimeofday(&end, NULL);

    printf("Client send completed!\n");

		
  	close(recfd);
    close(sock);
    return 0;
};
