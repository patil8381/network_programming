#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
WORD ver;
WSADATA wsaData;
int serverSocket;
int clientSocket;
struct sockaddr_in serverSocketInformation;
char request[5000];
char response[5000];
int successCode;

ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocket=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("192.168.1.2");

connect(clientSocket,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"Hello Thinking Machines I have done C++ course");
successCode=send(clientSocket,request,strlen(request)+1,0);
if(successCode<0)
{
printf("cannot sent data\n");
return 0;
}
successCode=recv(clientSocket,response,sizeof(response),0);
if(successCode<0)
{
printf("cannot recv data\n");
return 0;
}
printf("Response recieved\n");
printf("%s\n",response);
closesocket(clientSocket);
WSACleanup();
return 0;
}