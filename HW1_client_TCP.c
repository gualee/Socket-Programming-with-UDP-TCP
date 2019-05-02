#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define Server_PortNumber 5555
#define Server_Address "140.120.14.113"

int main(int argc, char *argv[])
{
    struct sockaddr_in address;
    struct  timeval start;
    struct  timeval end;

    int address_length = sizeof(address);
    int sock, byte_sent, byte_recv;
    char buffer[50];
	char buffer1[50];
	
    float throughput = 0;
	long int runtime = 0;
	
    bzero(&address, address_length);
    address.sin_family = AF_INET;
    address.sin_port = htons(Server_PortNumber);
    address.sin_addr.s_addr = inet_addr(Server_Address);

    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    printf("This is Client.\n");
	fgets(buffer, sizeof buffer, stdin);
    
    if(sock < 0)
        printf("Error creating socket\n");
    else
        printf("Socket create successfully!\n");

    
	if(connect(sock, (struct sockaddr *)&address, address_length) == -1)
	{
		printf("connect failed!\n");
		close(sock);
	}

    gettimeofday(&start,NULL);
      
    byte_sent = send(sock, buffer, sizeof(buffer), 0);

    if(byte_sent == -1)
		printf("Error sending packet\n");

	byte_recv = recv(sock, buffer1, sizeof(buffer1), 0);
	
	if (byte_recv < 0)
		printf("Receive Failed\n");
		
	printf("%s\n",buffer1);

    gettimeofday(&end, NULL);

    runtime = (1000000 * (end.tv_sec - start.tv_sec)) + (end.tv_usec - start.tv_usec);
    throughput = (sizeof(buffer)+sizeof(buffer1)) * 8000 / runtime;
    
    printf("Server IP: %s\n", Server_Address);
    printf("Time Interval : %ld (us)\n", runtime);
    printf("Throughput : %5.4lf Kbps\n", throughput);

    close(sock);
    return 0;
}
                                                          
