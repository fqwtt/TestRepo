#include <iostream>
#include <thread>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <vector>
#include <map>
#include <mutex>
#include "mySocket.h"
//#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
void initwinsock();

void socket_recv_thread(SOCKET serverSocket) {
	char recv_buf[1024];
	while (true) {
		int recvBytes = recv(serverSocket, recv_buf, sizeof(recv_buf), 0);
		if (recvBytes < 0) {
			cout << "Receive failed" << endl;
			break;
		}
		cout << recv_buf << endl;
	}
	cout << "Ïß³Ì½áÊø" << endl;
}

void socket_send_thread(SOCKET serverSocket) {
	char send_buf[1024];
	while (true) {
		cout << "please enter the reply message:";
		cin >> send_buf;
		int sendBytes = send(serverSocket, send_buf, sizeof(send_buf), 0);
		if (sendBytes < 0) {
			cout << "Send failed" << endl;
			break;
		}
	}
}

int main() {
	initwinsock();
	int port;
	int send_len = 0;
	cout << "port£º";
	std::cin >> port;
	SOCKET s_server;
	// define server address 
	SOCKADDR_IN server_addr;
	// fill server information
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.S_un.S_addr);
	server_addr.sin_port = htons(port);
	// create socket
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "Server connection failed!" << endl;
		WSACleanup();
	}
	else {
		cout << "Server connection successed!" << endl;
	}

	// send and receive data
	thread sendThread(socket_send_thread, s_server);
	thread recvThread(socket_recv_thread, s_server);
	sendThread.join();
	recvThread.join();
	// close socket
	closesocket(s_server);
	// Release DLL resources
	WSACleanup();
	return 0;
}


void initwinsock() {
	WORD w_req = MAKEWORD(2, 2); //w_req = 514; 0x0202 = 514(10)
	WSADATA wsadata;
	int err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cerr << "Failed to initialize Winsock" << endl;
		return;
	}
}