#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
        int server_socket,client_socket,flag=1,c;
        char buff[100],file[30];
        struct sockaddr_in server,other;
        socklen_t add;
        memset(&server,sizeof(server),0);
        memset(&other,sizeof(other),0);
        
        server_socket=socket(AF_INET,SOCK_STREAM,0);
        server.sin_family=AF_INET;
        server.sin_port=htons(9009);
        server.sin_addr.s_addr=INADDR_ANY;
        
        if(bind(server_socket,(struct sockaddr*)&server,sizeof(server))== -1)
        {
          printf("Connection failed \n");
          exit(0);
        }
        listen(server_socket,5);
        add =sizeof(other);
        
        client_socket = accept(server_socket,(struct sockaddr*)&other,&add);
        recv(client_socket,&flag,sizeof(flag),0);
        
        if(flag ==0)
        {
        printf("File transfer failed");
        exit(0);
            }
        else
        printf("file transfer started \n");
        recv(client_socket,file,sizeof(file),0);    
        FILE *fp;
        fp= fopen(file,"wb");
         read(client_socket,&c,sizeof(c));
        while(c!=EOF)
        {
         fputc(c,fp);
		// printf("%d\n",c);
        read(client_socket,&c,sizeof(c));
	}

    printf("file recieved successfully\n");
    printf("recieved file saved as %s\n",file);
    fclose(fp);
    close(server_socket);
    return 0;           
}
