#include <iostream>
#include <thread>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <vector>
#include <map>
#include <mutex>
#include "mySocket.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

map<SOCKET, SOCKET> mp;
void initwinsock();
void socket_recv_thread(SOCKET clientSocket, int port);

int main() {

	initwinsock();
	int port = 9900;
	vector<thread> recvThreads;
	vector<MySocket> mysockets;

	while (true) {
		mysockets.emplace_back(MySocket(port));
		cout << "port " << port << " is listing" << endl;
		SOCKET clientSocket = accept(mysockets.back().getSocket(), NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			cerr << "Failed to accept client connection" << endl;
			mysockets.back().closeSocket();
			WSACleanup();
			break;
		}
		mp.insert(make_pair(mysockets.back().getSocket(), clientSocket));
		recvThreads.emplace_back(thread(socket_recv_thread, clientSocket, port));

		port += 1;
	}
	for (auto& t : recvThreads) {
		t.join();
	}
	system("pause");
	// �ر��׽���
	WSACleanup();
	return 0;
}


void initwinsock() {
	//��ʼ��winsock
	WORD w_req = MAKEWORD(2, 2); //w_req = 514; 0x0202 = 514(10)
	WSADATA wsadata;

	/*WSAStartup������Windows��ʹ��Winsock���ʱ������õ�һ�����������ڳ�ʼ��Winsock��̬���ӿⲢ���汾�š�
	������˵�������������߲���ϵͳ������Ҫʹ�õ�Winsock��İ汾�ţ�Ȼ�󽫸ÿ���ص��ڴ��У�ͬʱ�Ըÿ���г�ʼ����*/

	int err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cerr << "Failed to initialize Winsock" << endl;
		return;
	}
}

void socket_recv_thread(SOCKET clientSocket, int port) {
	char recv_buf[1024];
	while (true) {
		int recvBytes = recv(clientSocket, recv_buf, sizeof(recv_buf), 0);
		if (recvBytes < 0) {
			cout << "Receive failed" << endl;
			break;
		}
		string send_str = to_string(port) + " say: " + string(recv_buf) + "\0";

		for (auto& socket : mp) {
			if (socket.second == clientSocket) {
				continue;
			}
			int sendBytes = send(socket.second, send_str.c_str(), send_str.size()+1, 0);
		}
	}
	cout << port << "�˿��˳�" << endl;
}