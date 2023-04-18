#include "mySocket.h"

// 构造
MySocket::MySocket(int port, string ip) {
	this->m_ip = ip;
	this->m_port = port;
	this->initSocket();
}

// 获取套接字
SOCKET& MySocket::getSocket() {
	return this->m_socket;
}

// 关闭套接字
void MySocket::closeSocket() {
	closesocket(this->m_socket);
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
	if (this->m_socket == INVALID_SOCKET) {  // INVALID_SOCKET = 18446744073709551615
		cerr << "Failed to create server socket" << endl;
		return;
	}
}

// 绑定服务器套接字
void MySocket::socketBind() {
	SOCKADDR_IN socketAddr;
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(this->m_port);
	if (this->m_ip == "0.0.0.0") {
		socketAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	}
	else {
		inet_pton(AF_INET, this->m_ip.c_str(), &socketAddr.sin_addr.S_un.S_addr);
	}
	if (bind(this->m_socket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cerr << "Socket binding failed!" << endl;
		closesocket(this->m_socket);
		WSACleanup();
		return;
	}
}

// 监听
void MySocket::socketListen() {
	if (listen(this->m_socket, SOMAXCONN) == SOCKET_ERROR) {
		cerr << "Failed to listen to client connection requests" << endl;
		closesocket(this->m_socket);
		WSACleanup();
	}
}


