#include <iostream>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

using std::cout; using std::endl;

void initialization();

int main() {
	// define length variable
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	// define send buffer and recieve buffer
	char send_buf[100];
	char recv_buf[100];
	// define server socket and accept socket
	SOCKET s_server;
	SOCKET s_accept;
	// define server address and accept address
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	// fill server information
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9999);
	// create socket
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR){
		cout << "Socket binding failed!" << endl;
		WSACleanup();
	}
	else {
		cout << "Socket binding successed!" << endl;
	}
	// Set socket to listening state
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "Set socket to listening state failed" << endl;
		WSACleanup();
	}
	else {
		cout << "Set socket to listening state successed" << endl;
	}
	cout << "The server is listening for connections, please wait..." << endl;
	// Accept connection request
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "Connect failed!" << endl;
		WSACleanup();
		return 0;
	}
	cout << "Connection established, ready to receive data" << endl;
	// Receive data
	while (1) {
		recv_len = recv(s_accept, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "Receive failed" << endl;
			break;
		}
		else {
			cout << "Client message:" << recv_buf << endl;
		}
		cout << "please enter the reply message:";
		std::cin >> send_buf;
		send_len = send(s_accept, send_buf, 100, 0);
		if (send_len < 0) {
			cout << "Send failed!" << endl;
			break;
		}
	}
	// close socket
	closesocket(s_server);
	closesocket(s_accept);
	// Release DLL resources
	WSACleanup();
	return 0;
}

void initialization() {
	WORD w_req = MAKEWORD(2, 2);
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "initial socket failed!" << endl;
	}
	else {
		cout << "initial socket successed!" << endl;
	}
	// check version
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "The version number of the socket library does not match!" << endl;
		WSACleanup();
	}
	else {
		cout << "The socket library version is correct!" << endl;
	}
}