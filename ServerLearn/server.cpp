#include <iostream>
#include <thread>
#include <WS2tcpip.h>
#include <WinSock2.h>
//#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

class Person {
public:
	Person(const std::string& name, int age) : name_(name), age_(age) {}
	std::string name_;
	int age_;
};


int main() {
	//初始化winsock
	WORD w_req = MAKEWORD(2, 2); //w_req = 514; 0x0202 = 514(10)
	WSADATA wsadata;

	/*WSAStartup函数是Windows下使用Winsock编程时必须调用的一个函数，用于初始化Winsock动态链接库并检查版本号。
	具体来说，这个函数会告诉操作系统我们需要使用的Winsock库的版本号，然后将该库加载到内存中，同时对该库进行初始化。*/

	int err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cerr << "Failed to initialize Winsock" << endl;
		return -1;
	}

	// 创建服务器套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {  // INVALID_SOCKET = 18446744073709551615
		cerr << "Failed to create server socket" << endl;
		return -1;
	}

	// 绑定服务器套接字到本地IP和端口号
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9999);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.S_un.S_addr);
	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cerr << "Socket binding failed!" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		cerr << "Failed to listen to client connection requests" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	SOCKET clientSocket = accept(serverSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "Failed to accept client connection" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	char recvBuf[1024];
	int recvBytes = recv(clientSocket, recvBuf, sizeof(recvBuf), 0);
	cout << recvBuf << endl;

	system("pause");
	// 关闭套接字
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

