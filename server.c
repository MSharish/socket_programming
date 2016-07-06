#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
//#include <netinet/in.h>

int main(int argc, char *argv[]) {
	
    int sd, fsd,clilen, bytes_sent,ch, length;
    char * msg = "Hi you are connected to the server... how can I help you today?";
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t len1 = sizeof(serv_addr);
	socklen_t len2 = sizeof(cli_addr);
	char * msg_from_client = malloc (200);
	
	
	sd = socket(AF_INET,SOCK_STREAM,0);
	if ( sd == -1){
		
		printf("Error in establishing connection\n");
		exit(1);
	}
	else{
		/*if (getsockname(sd, (struct sockaddr *)&serv_addr, &len) == -1 )
		  printf("cannt get socket name\n");
		else {
			printf("port number = %d\n",ntohs(serv_addr.sin_port));
		}*/
		printf("Socket created successfully\n");
		
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(8887);
		
		if (bind(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
			perror("ERROR on binding");
			exit(1);
		   }
		printf("binding done successfully\n");
		
	    if (listen(sd,5) <0 ){
		   printf("Error listening\n");
		   exit(1);
		
	    }
		
		printf("listening........\n");
		fsd = accept(sd,(struct sockaddr *) &cli_addr,&len2);
		
		if ( fsd == -1){
			
			printf("Cannot accept\n");
			exit(1);
		}
		
		printf ("Accepting.......\n");
		
	
	  msg = "Hi, I can do following things for you\n1.Tell you today's date\n2.Tell you the string lenght you will send me\n        Please enter your choice in terms of 1 and 2 only\n";
		  
		//bytes_sent = send(sd,msg,strlen(msg),0);
		
		bytes_sent =  write(fsd,msg,200);
		
		if ( bytes_sent < 0){
			
		  printf("Not able to send message from server. Bye\n");
		  exit(1);
		
		}
		
		
		while ( read(fsd, msg_from_client, 200)){
			
			ch = atoi(msg_from_client);
			
			switch (ch){
				
				case 1:msg="Todays date is 13 March 2016\n";
				       bytes_sent =  write(fsd,msg,strlen(msg));
				       break;
				
				case 2: msg="Wait for a while\n";
				     bytes_sent =  write(fsd,msg,strlen(msg));
				       break;
				
			}
			  
			
			
		}
		
		
	}


}
