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
	// 关闭套接字
	WSACleanup();
	return 0;
}


void initwinsock() {
	//初始化winsock
	WORD w_req = MAKEWORD(2, 2); //w_req = 514; 0x0202 = 514(10)
	WSADATA wsadata;

	/*WSAStartup函数是Windows下使用Winsock编程时必须调用的一个函数，用于初始化Winsock动态链接库并检查版本号。
	具体来说，这个函数会告诉操作系统我们需要使用的Winsock库的版本号，然后将该库加载到内存中，同时对该库进行初始化。*/

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
	cout << port << "端口退出" << endl;
}