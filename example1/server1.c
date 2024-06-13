#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
WORD ver;
WSADATA wsaData;
int clientSocket;
int serverSocket;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
char response[5000];
char request[5000];
int successCode;
int len;

ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocket=socket(AF_INET,SOCK_STREAM,0);
if(serverSocket<0)
{
printf("unable to create socket");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocket,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("unable to bind socket\n");
WSACleanup();
return 0;
}
listen(serverSocket,10);
printf("Server is ready to accept connection on poert 5050.\n");
len=sizeof(clientSocketInformation);
clientSocket=accept(serverSocket,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocket<0)
{
printf("unable to accept client connection\n");
closesocket(serverSocket);
WSACleanup();
return 0;
}
successCode=recv(clientSocket,request,sizeof(request),0);
if(successCode>0)
{
printf("Request recieved.\n");
printf("%s\n",request);
}
strcpy(response,"Welcome to Thinking machines.\n");
send(clientSocket,response,strlen(response)+1,0);
if(successCode>0)
{
printf("Response sent.\n");
}
else 
{
printf("unabel to send response\n");
}
closesocket(serverSocket);
closesocket(clientSocket);
WSACleanup();
return 0;
}