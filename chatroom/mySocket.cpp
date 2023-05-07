/*************************************************************************
  > File Name: mySocket.cpp
  > Author: fqwtt
  > Created Time: 2023年04月27日 星期四 08时57分21秒
 ************************************************************************/

#include<iostream>
#include "mySocket.h"
using namespace std;

// 构造
MySocket::MySocket(int port, string ip) {
	this->m_ip = ip;
	this->m_port = port;
	this->initSocket();
}

// 获取套接字
int& MySocket::getSocket() {
	return this->m_socket;
}

// 获取端口号
int MySocket::getPort() {
	return this->m_port;
}

// 关闭套接字
void MySocket::closeSocket() {
	close(this->m_socket);
}

// 初始化
void MySocket::initSocket() {
	this->socketCreat();
	this->socketBind();
	this->socketListen();
}

// 创建套接字
void MySocket::socketCreat() {
	this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_socket == -1) {  // INVALID_SOCKET = 18446744073709551615
		cerr << "Failed to create server socket" << endl;
		return;
	}
}

// 绑定服务器套接字
void MySocket::socketBind() {
	sockaddr_in socketAddr;
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(this->m_port);
	if (this->m_ip == "0.0.0.0") {
		socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else {
		inet_pton(AF_INET, this->m_ip.c_str(), &socketAddr.sin_addr.s_addr);
	}
	if (bind(this->m_socket, (sockaddr*)&socketAddr, sizeof(sockaddr)) == -1) {
		cerr << "Socket binding failed!" << endl;
		close(this->m_socket);
		return;
	}
}

// 监听
void MySocket::socketListen() {
	if (listen(this->m_socket, 5) == -1) {
		cerr << "Failed to listen to client connection requests" << endl;
		close(this->m_socket);
		return;
	}
}
