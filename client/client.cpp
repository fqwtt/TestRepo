#include <iostream>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

using std::cout; using std::endl;

void initialization();

int main() {
	// define length variable
	int send_len = 0;
	int recv_len = 0;
	// define send buffer and recieve buffer
	char send_buf[100];
	char recv_buf[100];
	// define server socket
	SOCKET s_server;
	// define server address 
	SOCKADDR_IN server_addr;
	initialization();
	// fill server information
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.70");
	server_addr.sin_port = htons(9999);
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
	while (1) {
		cout << "Please enter send message:";
		std::cin >> send_buf;
		send_len = send(s_server, send_buf, 100, 0);
		if (send_len < 0) {
			cout << "Send failed!" << endl;
			break;
		}
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "Receive failed" << endl;
			break;
		}
		else {
			cout << "Client message:" << recv_buf << endl;
		}
	}
	// close socket
	closesocket(s_server);
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