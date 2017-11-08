/*
** client.c -- a stream socket client demo
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


/*********************************************
 Read the README for what define ACTUAL does
**********************************************/
	
	//#define ACTUAL


#include <arpa/inet.h>

#define PORT "3602" // the port client will be connecting to 

#define MAXDATASIZE 500 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	
	char file_name[MAXDATASIZE];
	#ifdef ACTUAL
		char temp[MAXDATASIZE];
	#endif
	FILE *fp;
	
	char download[MAXDATASIZE];
	char r;
	
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	

	if (argc != 2) {
	    fprintf(stderr,"usage: client hostname\n");
	    exit(1);
	}
while(1) {

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	//while(1) {
	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure
	
	printf("ENTER_CMD:\n");
	#ifdef ACTUAL	
		scanf("%s",temp);
	#else
		scanf("%s",buf);
	#endif
	#ifdef ACTUAL
		int i,j,k,flag,test;
		i=0;
		j=0;
		test=0;
		flag=0;
		while(flag!=1){
			if(temp[i]=='<'){
				buf[i]='\0';
				test=1;
			}
			else{
				buf[i]=temp[i];
			}
			if(test==1){
				file_name[j]=temp[i+1];
				if(file_name[j]=='>'){
					file_name[j]='\0';
				}
				j++;
			}
			if(temp[i]=='\n' || temp[i]=='>'){
				flag=1;
			}
			i++;
		}
		printf("'%s'|'%s'\n",buf,file_name);
	#endif
	
	if(strcmp(buf,"list")==0) {
		send(sockfd,buf,strlen(buf),0);
		numbytes=recv(sockfd,buf,200,0);
		buf[numbytes]='\0';
		printf("%s",buf);
	}
	else if(strcmp(buf,"check")==0){
		send(sockfd,buf,strlen(buf),0);
		#ifdef ACTUAL
			printf("checking\n");
			sleep(2);
		#else
			printf("Enter File Name: \n");
			scanf("%s",file_name);
		#endif
		send(sockfd,file_name,strlen(file_name),0);
		numbytes=recv(sockfd,buf,200,0);
		buf[numbytes]='\0';
		printf("%s",buf);
	}
	else if(strcmp(buf,"display")==0) {
		send(sockfd,"get",3,0);
		#ifdef ACTUAL
			printf("checking\n");
			sleep(2);
		#else
			printf("Enter File Name: \n");
			scanf("%s",file_name);
		#endif
		send(sockfd,file_name,strlen(file_name),0);
		while(numbytes=recv(sockfd,buf,MAXDATASIZE-1,0)) {
			buf[numbytes]='\0';
			printf("%s",buf);
		}
	}
	else if(strcmp(buf,"download")==0) {
		send(sockfd,"get",3,0);
		#ifdef ACTUAL
			printf("checking\n");
			sleep(2);
		#else
			printf("Enter File Name:\n");
			scanf("%s",file_name);
		#endif
		send(sockfd,file_name,strlen(file_name),0);
		numbytes=recv(sockfd,buf,200,0);
		buf[numbytes]='\0';
		strcpy(download,"File '");
		strcat(download,file_name);
		strcat(download,"' is not found");
		if(strcmp(download,buf)==0)
			printf("%s",buf);
		else if(fopen(file_name,"r")!=NULL) {
			while(getchar() != '\n');
			printf("File '%s' exists. Overwrite it? (y/n)", file_name);
			r = getchar();
			if(r == 'y') {
				fp = fopen(file_name,"w");
				fprintf(fp,"%s",buf);
				while(numbytes=recv(sockfd,buf,200,0)) {
					buf[numbytes] = '\0';
					fprintf(fp,"%s",buf);
				}
				fclose(fp);
				printf("'%s' download completed\n",file_name);
			}	
			else printf("Download Failed\n");
		}
		else {
			fp = fopen(file_name,"w");
                        fprintf(fp,"%s",buf);
                        while(numbytes=recv(sockfd,buf,200,0)) {
                        buf[numbytes] = '\0';
                        fprintf(fp,"%s",buf);
			}
                        fclose(fp);
                        printf("'%s' download completed\n",file_name);

		}
	}

	else if(strcmp(buf,"help")==0) {
		printf("HELP MENU\n"
			"\t'list'		: lists the contents of the server\n"
			"\t'check<file name>'	: checks if the file is on the server\n"
			"\t'display<file name>'	: displays the contents of a file on the server\n"
			"\t'download<file name>': downloads the file to the client from the server\n"
			"\t'quit'		:	closes the client\n"); 
	}
	else if(strcmp(buf,"quit")==0){
		 exit(0);
	}
	else{
		 printf("Invalid CMD. 'help' for the list of available commands.\n");
	}
}
	close(sockfd);
}

