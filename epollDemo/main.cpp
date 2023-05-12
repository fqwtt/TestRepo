/*************************************************************************
  > File Name: main.cpp
  > Author: fqwtt
  > Created Time: 2023年04月28日 星期五 14时28分23秒
 ************************************************************************/

#include <iostream>
#include <sys/epoll.h>
#include <cstring>
#include "./mySocket.h"
using namespace std;

#define MAX_EVENTS 10

int main(){
	MySocket serv_sock(8080);
	int epfd=epoll_create(1);
	if(epfd==-1){
		cout<<"Epoll create error!"<<endl;
	}
	epoll_event event,events[MAX_EVENTS];
	event.data.fd=serv_sock.getSocket();
	event.events=EPOLLIN|EPOLLET;
	epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock.getSocket(),&event);
	while(1){
		int n=epoll_wait(epfd,events,10,-1);
		if(n==-1){
			cout<<"error"<<endl;
		}
		for(int i=0;i<n;i++){
			int fd=events[i].data.fd;
			if(fd==serv_sock.getSocket()){
				int client=accept(serv_sock.getSocket(),NULL,NULL);
				if (client==-1){
					cout<<"failed to accept client connection"<<endl;
				}
				event.data.fd=client;
				epoll_ctl(epfd,EPOLL_CTL_ADD,client,&event);
			}
			else{
				const char* response =
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/html\r\n"
					"\r\n"
					"<html><body><h1>Hello, world!</h1></body></html>\r\n";
				send(fd, response, strlen(response), 0);
			}
		}
	}
}

