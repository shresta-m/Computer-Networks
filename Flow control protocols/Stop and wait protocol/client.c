#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
//Here stop and wait means, whatever the data that sender wants to send, he sends the data to the receiver.
// After sending the data, he stops and waits until he receives the acknowledgment from the receiver. 
//The stop and wait protocol is a flow control protocol where flow control is one of the services of the data link layer.

//It is a data-link layer protocol which is used for transmitting the data over the noiseless channels. 
//It provides unidirectional data transmission which means that either sending or receiving of data will take place at a time. 
//It provides flow-control mechanism but does not provide any error control mechanism.
int main()
{
    int c_sock;
    char buff[2],flag[2];
    struct sockaddr_in client;
    c_sock = socket(AF_INET,SOCK_STREAM,0);
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9009);
    client.sin_addr.s_addr = INADDR_ANY;    
    if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
    {
        printf("Connection declined \n");
        return 0;
    }
    buff[1] = '\0';
    flag[0] = '\0';
    //flag variable is used to check whether all the data packets are sent or not
    char message[100];
    char ackg[2];
    printf("Enter the message to sent :\n");
    gets(message);
    for(int i=0;i<strlen(message);++i)
    {
        buff[0]=message[i];
        flag[1] = '0';
        send(c_sock,flag,sizeof(flag),0);
        send(c_sock,buff,sizeof(buff),0);
        recv(c_sock,ackg,sizeof(ackg),0);
        printf("Acknowledgement : %c\n",ackg[0]);
        if(ackg[0] == '0')
        {
        --i;//if acknowledgement is 0 ,then the data has not been received at the receiver side,the data packet needs to be resent
        }
    }
    flag[0]=1;
    send(c_sock,flag,sizeof(flag),0);
    printf("The message is sent \n");
    close(c_sock);
    return 0;
}
