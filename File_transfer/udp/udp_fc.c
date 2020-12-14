#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int client_socket,flag=1,c;
    char buffer[100],send_file[30],save[30];
    struct sockaddr_in client;

    client_socket=socket(AF_INET,SOCK_DGRAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;
    
    printf("Enter the file to be sent: ");
    scanf("%s",send_file);
    FILE *fp;
    fp=fopen(send_file,"rb");
    
    if(fp==NULL)
    {
        printf("File doesnt exist\n");
        flag=0;
        sendto(client_socket,&flag,sizeof(flag),0,(struct sockaddr*) &client,sizeof(client));

        exit(1);
    }

    printf("Enter new file name to save the sent file as: ");
    scanf("%s",save);

    sendto(client_socket,&flag,sizeof(flag),0,(struct sockaddr*) &client,sizeof(client));
    sendto(client_socket,save,sizeof(save),0,(struct sockaddr*) &client,sizeof(client));

	while((c=fgetc(fp))!=EOF)
    {
        sleep(0);
        sendto(client_socket,&c,sizeof(c),0,(struct sockaddr*) &client,sizeof(client));
	}
	c=EOF;
    sendto(client_socket,&c,sizeof(c),0,(struct sockaddr*) &client,sizeof(client));

    flag=0;
    sendto(client_socket,&flag,sizeof(flag),0,(struct sockaddr*) &client,sizeof(client));

    printf("file sent successfully\n");
    fclose(fp);
    close(client_socket);
    return 0;
}
