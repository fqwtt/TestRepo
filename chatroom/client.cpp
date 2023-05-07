/*************************************************************************
  > File Name: client.cpp
  > Author: fqwtt
  > Created Time: 2023年04月27日 星期四 10时13分02秒
 ************************************************************************/

#include <iostream>
#include "mySocket.h"
using namespace std;

void socket_recv_thread(int serverSocket) {
	char recv_buf[1024];
	while (true) {
		int recvBytes = recv(serverSocket, recv_buf, sizeof(recv_buf), 0);
		if (recvBytes < 0) {
			cout << "Receive failed" << endl;
			break;
		}
		else if(recvBytes == 0){
			cout << "线程结束" << endl;
			exit(-1);
		}
		cout << recv_buf << endl;
	}
}

void socket_send_thread(int serverSocket) {
	char send_buf[1024];
	while (true) {
		cin.getline(send_buf,sizeof(send_buf));
		int sendBytes = send(serverSocket, send_buf, sizeof(send_buf), 0);
		if (sendBytes < 0) {
			cout << "Send failed" << endl;
			break;
		}
	}
}

int main() {
	int port;
	int send_len = 0;
	cout << "port：";
	cin >> port;
	int s_server;
	// define server address
	sockaddr_in server_addr;
	// fill server information
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);
	server_addr.sin_port = htons(port);
	// create socket
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (sockaddr*)&server_addr, sizeof(sockaddr)) < 0) {
		cout << "Server connection failed!" << endl;
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
	close(s_server);
	// Release DLL resources
	return 0;
}
