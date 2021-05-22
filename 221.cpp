#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define BUF_SIZE 1024
#define SERVER_PORT 50050
using namespace std;
int main(){
    int iPort=SERVER_PORT;
    WSADATA wsadata;
    SOCKET sListen,sAccept;
    int iLen;//客户地址长度
    int iSend;//发送数据长度
    char buf[]="I am a server!";
    struct sockaddr_in ser,cli;//服务器和客户地址
    cout<<"------------------"<<endl;
    cout<<"Server waiting"<<endl;
    cout<<"------------------"<<endl;
    if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
        cout<<"Faild to load Winsock!"<<endl;
        return 0;
    }
    sListen=socket(AF_INET,SOCK_STREAM,0);//创建套接字
    if(sListen==INVALID_SOCKET){
        cout<<"socket() faild:"<<WSAGetLastError();
        return 0;
    }
    ser.sin_family=AF_INET;
    ser.sin_port=htons(iPort);
    ser.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR){
        cout<<"bind() faild:"<<WSAGetLastError();
        return 0;
    }
    if(listen(sListen,5)==SOCKET_ERROR){
        cout<<"listen() failed:"<<WSAGetLastError();
        return 0;
    }
    iLen=sizeof(cli);//初始化客户地址长度

    while(1){
    	int p=0;
    	cin>>p;
    	if(p==0){
    		cout<<"结束！";
    		closesocket(sAccept);
    		break;
		}
    	cin>>buf;
        sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
        if(sAccept==INVALID_SOCKET){
            cout<<"accept() failed:"<<WSAGetLastError();
            break;
        }
        cout<<"Accepted client IP:"<<inet_ntoa(cli.sin_addr)<<" and port："<<ntohs(cli.sin_port);
        iSend=send(sAccept,buf,sizeof(buf),0);
        if(iSend==SOCKET_ERROR){
             cout<<"send() failed:"<<WSAGetLastError();
             break;
        }else if(iSend==0){
                break;
            }else{
                cout<<"send() byte:"<<iSend<<endl;
                cout<<"------------------"<<endl;

            }
//            closesocket(sAccept);
        
    }
    closesocket(sListen);
    WSACleanup();

}
