#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	int sd, bytes_read;
	int srvport = 8888;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char * response_buffer = malloc(100);
	
	sd = socket(AF_INET,SOCK_STREAM,0);
	if ( sd == -1){
		
		printf("Socket was not created successfully\n");
		exit(1);
	}
    
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(srvport);
	
	
	if ( connect(sd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
		printf("Connection not successfull\n");
		exit(1);
		
		
	}
	
	
	bytes_read = read(sd, response_buffer, 100);
	
	if ( bytes_read == -1)
	  printf("Error in receiving message from server\n");
	
	printf ("%s\n",response_buffer);

}
