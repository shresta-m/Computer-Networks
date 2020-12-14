#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

//The size of the receiving window is the maximum number of frames that the receiver can accept at a time. 
//It determines the maximum number of frames that the sender can send before receiving acknowledgment.
int main()
{
	int s_sock,c_client;
	s_sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server,other;
	memset(&server,0,sizeof(server));
	memset(&other,0,sizeof(other));
	server.sin_family=AF_INET;
	server.sin_port=htons(9000);
	server.sin_addr.s_addr=INADDR_ANY;
	socklen_t addr_size;
	bind(s_sock,(struct sockaddr*)&server,sizeof(server));
	listen(s_sock,5);
	addr_size=sizeof(other);
	c_client=accept(s_sock,(struct sockaddr*)&other,&addr_size);

	char message[50];
	char flag[2],buff[2],ack[2];
	int window_size=2;

	int window_s[1];
	recv(c_client,window_s,sizeof(window_s),0);
	window_size=window_s[0];
	printf("The message packets are :\n");
	int msglen=0;
	recv(c_client,flag,sizeof(flag),0);
	while(flag[0]=='0')
	{
		for(int i=0;i<window_size;i++)
					{
						recv(c_client, buff, sizeof(buff), 0);//receive the data packets from sender 
						printf("buff: %s\n", buff);
						message[msglen] = buff[0];
						msglen++;
					}
					
					char ack_temp[2];
					for(int i=0;i<window_size;i++)
					{
						printf("Acknowledgement: ");
						gets(ack_temp);//get the acknowledgemnt and send this to the sender
						ack[0] = ack_temp[0];
						
						send(c_client, ack, sizeof(ack), 0);
						if(ack[0] == '0')
						{
							msglen = msglen - window_size + i;
							i = window_size;
						}
					}
		recv(c_client,flag,sizeof(flag),0);
	}
	message[msglen++]='\0';
	printf("\nThe received message :\n");
	for(int i=0;i<msglen;++i)
	printf("%c",message[i]);
	printf("\n");
	close(s_sock);
	close(c_client);
	return 0;
}
