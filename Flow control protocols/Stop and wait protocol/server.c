#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
int main()
{
    int s_sock,client;
    struct sockaddr_in server ,other;
    memset(&server,sizeof(server),0);
    memset(&other,sizeof(other),0);
    s_sock = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port = htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;
    socklen_t addr_size;
    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    listen(s_sock,5);
    addr_size=sizeof(other);
    client=accept(s_sock,(struct sockaddr*)&other,&addr_size);

    char message[100],flag[2],buff[2];
    char ackg[2];
    int msg_len =0;
    recv(client,flag,sizeof(flag),0);
    while(flag[0] == 0)
    {
        recv(client,buff,sizeof(buff),0);//receive the data packet
        printf("\n%c",buff[0]);
        char ackg1[2];
        printf("\nEnter the acknowledgemnt [0/1] :");
        gets(ackg1);
        ackg[0] = ackg1[0];
        send(client,ackg,sizeof(ackg),0);//send the acknowledgement
        if(ackg[0]=='1')
		{
			message[msg_len++]=buff[0];
		}
		recv(client,flag,sizeof(flag),0);
	}
	message[msg_len++]='\0';
	printf("\nReceived message :\n");
	for(int i=0;i<msg_len;++i)
	printf("%c",message[i]);
	printf("\n");
	close(s_sock);
	close(client);
	return 0;
}
