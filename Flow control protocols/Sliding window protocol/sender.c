#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

//In this protocol, the sender has a buffer called the sending window and the receiver has buffer called the receiving window.
//The size of the sending window determines the sequence number of the outbound frames. 
//If the sequence number of the frames is an n-bit field, then the range of sequence numbers that can be assigned is 0 to 2𝑛−1. 
//Consequently, the size of the sending window is 2𝑛−1. Thus in order to accommodate a sending window size of 2𝑛−1, a n-bit sequence number is chosen.

int main()
{
	
	int c_sock;
	c_sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9000);
	client.sin_addr.s_addr=INADDR_ANY;

	if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
	{
			printf("Connection failure");
			return 0;
	}

	char buff[2];
	buff[1]='\0';
	char message[50];
	int window_size;
	printf("\nEnter window size:\n");
	scanf("%d",&window_size);
	
	char ch;
	scanf("%c",&ch);
	int ws[]={window_size};
	send(c_sock, ws, sizeof(ws), 0);
	printf("\nEnter the message to be sent:\n");
	gets(message);
	char flag[2];
	flag[0]='0';//this flag is for checking the string end i.e whether the message is sent or not  
	flag[1]='\0';
	
	for(int i=0;i<strlen(message);++i)
	{
		
		send(c_sock, flag, sizeof(flag), 0);
				for(int j=0;j<window_size;j++)
				{
					printf("Sending: %c\n", message[i+j]);
					buff[0] = message[i+j];
					send(c_sock, buff, sizeof(buff), 0);//sending data packets
				}
				int check_ackg = -1;
				char ackg[2];
				for(int j=0;j<window_size;j++)
				{
					recv(c_sock, ackg, sizeof(ackg), 0);//receiving the acknowledgement from server
					printf("Acknowledgement: %s\n", ackg);
					if(ackg[0] == '0')//if the acknowledgement is 0 ,means the data is not received at the receiver side and needs to be sent again
					{				  // if the frame size is 3 ,first we send data packets at place 0,1,2 and if 2 is unsent,the resend from 2 to 5
						check_ackg = j;
						j=window_size;
					}
				}
				if(check_ackg == -1) i = i + window_size-1;
				else i = i + check_ackg-1;
	}
	flag[0]='1';//if flag is 1 means the whole data packets are sent 
	send(c_sock,flag,sizeof(flag),0);
	printf("\nmessage sent\n");
	close(c_sock);
	return 0;
}
