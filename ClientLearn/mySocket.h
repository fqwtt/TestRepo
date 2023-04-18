#pragma once
#include <iostream>
#include <thread>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <vector>
#include <string>

using namespace std;
class MySocket {
public:
	// 构造
	MySocket(int port, string ip = "0.0.0.0");

	// 获取套接字
	SOCKET& getSocket();

	// 关闭套接字
	void closeSocket();
private:
	// 初始化
	void initSocket();

	// 创建套接字
	void socketCreat();

	// 绑定服务器套接字
	void socketBind();

	// 监听
	void socketListen();

private:
	SOCKET m_socket;
	string m_ip;
	int m_port;
};
