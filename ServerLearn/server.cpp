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

vector<SOCKET> clientSockets;
void initwinsock();
void socket_recv_thread(MySocket clientSocket);

int main() {

	initwinsock();
	int port = 9900;
	vector<thread> recvThreads;
	vector<MySocket> mysockets;
	int socketNum = 10;
	for (int i = 0; i < socketNum; i++) {
		mysockets.emplace_back(MySocket(port + i));
	}
	for (MySocket& socket : mysockets) {
		recvThreads.emplace_back(thread(socket_recv_thread, socket));
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

void socket_recv_thread(MySocket serverSocket) {
	char recv_buf[1024];
	while (1) {
		SOCKET clientSocket = accept(serverSocket.getSocket(), NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			cerr << "Failed to accept client connection" << endl;
			serverSocket.closeSocket();
			WSACleanup();
			break;
		}
		clientSockets.push_back(clientSocket);
		while (1) {
			int recvBytes = recv(clientSocket, recv_buf, sizeof(recv_buf), 0);
			if (recvBytes < 0) {
				for (auto it = clientSockets.begin(); it != clientSockets.end(); it++) {
					if (*it == clientSocket) {
						clientSockets.erase(it);
						break;
					}
				}
				break;
			}
			string send_str = to_string(serverSocket.getPort()) + " say: " + string(recv_buf) + "\0";
			for (SOCKET socket : clientSockets) {
				if (socket == clientSocket) {
					continue;
				}
				int sendBytes = send(socket, send_str.c_str(), send_str.size() + 1, 0);
			}
		}
	}
}