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
        int client_socket,flag=1,c;
        char buff[100],send_file[30],save_file[30];
        struct sockaddr_in client;
        memset(&client,0,sizeof(client));
        
        clock_t start,end;
        double cpu_time;
        start = clock();
        
        client_socket=socket(AF_INET,SOCK_STREAM,0);
        client.sin_family=AF_INET;
        client.sin_port=htons(9009);
        client.sin_addr.s_addr=INADDR_ANY;
        
        if(connect(client_socket,(struct sockaddr*)&client,sizeof(client))==-1)
        {
        printf("Connection failed \n");
        exit(0);
        }
        else
        printf("The connection is established with server \n");
        
        printf("Enter the file to be sent :");
        scanf("%s",send_file);
        
        FILE *fp;
        fp = fopen(send_file,"rb");
        
        if(fp ==NULL)
        {
          printf("File does'nt exist \n");
          flag =0;
          send(client_socket,&flag,sizeof(flag),0);
          exit(0);
         }
         
       printf("Enter the name of file to be saved : ");
         scanf("%s",save_file);
         send(client_socket,&flag,sizeof(flag),0);
         send(client_socket,save_file,sizeof(save_file),0);
         
          while((c=fgetc(fp))!=EOF)
          {
           write(client_socket,&c,sizeof(c));
           }
           c= EOF;
           write(client_socket,&c,sizeof(c));

         printf("file sent successfully\n");
         cpu_time =(((double)(end - start))/CLOCKS_PER_SEC);
       //  printf(" Time taken for file transfer = %f \n",cpu_time);
         fclose(fp);
         close(client_socket);
         return 0;

}
