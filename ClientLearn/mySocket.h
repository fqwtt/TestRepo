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
	// ����
	MySocket(int port, string ip = "0.0.0.0");

	// ��ȡ�׽���
	SOCKET& getSocket();

	// �ر��׽���
	void closeSocket();
private:
	// ��ʼ��
	void initSocket();

	// �����׽���
	void socketCreat();

	// �󶨷������׽���
	void socketBind();

	// ����
	void socketListen();

private:
	SOCKET m_socket;
	string m_ip;
	int m_port;
};
