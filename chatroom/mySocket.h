/*************************************************************************
  > File Name: mySocket.h
  > Author: fqwtt
  > Created Time: 2023年04月27日 星期四 08时52分29秒
 ************************************************************************/
//#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class MySocket{
	public:
		// 构造
		MySocket(int port, string ip = "0.0.0.0");

		// 获取套接字
		int& getSocket();

		// 获取端口号
		int getPort();

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
		int m_socket;
		string m_ip;
		int m_port;
};

