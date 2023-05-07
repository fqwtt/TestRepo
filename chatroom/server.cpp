/*************************************************************************
  > File Name: main.cpp
  > Author: fqwtt
  > Created Time: 2023年04月27日 星期四 09时49分42秒
 ************************************************************************/

#include <iostream>
#include "mySocket.h"

using namespace std;

vector<int> clientSockets;
void initwinsock();
void socket_recv_thread(MySocket clientSocket);

int main(){
	int port = 9900;
	vector<thread> recvThreads;
	vector<MySocket> mysockets;
	int socketNum = 10;
	for (int i = 0; i < socketNum; i++) {
		mysockets.emplace_back(MySocket(port + i));
	}
	for (MySocket& sock : mysockets) {
		recvThreads.emplace_back(thread(socket_recv_thread, sock));
	}
	for (auto& t : recvThreads) {
		t.join();
	}
	return 0;
}


void socket_recv_thread(MySocket serverSocket) {
	char recv_buf[1024];
	while (1) {
		int clientSocket = accept(serverSocket.getSocket(), NULL, NULL);
		if (clientSocket == -1) {
			cerr << "Failed to accept client connection" << endl;
			serverSocket.closeSocket();
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
			for (int sock : clientSockets) {
				if (sock == clientSocket) {
					continue;
				}
				int sendBytes = send(sock, send_str.c_str(), send_str.size() + 1, 0);
			}
		}
	}
}
