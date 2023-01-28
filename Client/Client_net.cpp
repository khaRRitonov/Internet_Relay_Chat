#include <iostream>
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996);

SOCKET connected;

void client_hendler() {
	int msg_size;
	while (true) {
		recv(connected, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(connected, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
	}
}

int main2() {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); // верси€ библиотеки WinSock
	if (WSAStartup(DLLVersion, &wsaData) != 0) { // «агружаем библиотеку
		std::cout << "Error!" << std::endl;
		return 1;
	}

	SOCKADDR_IN addr; // структура хранени€ адреса
	int size_new_addr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	connected = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connected, (SOCKADDR*)&addr, sizeof(addr)) != 0) { // присоединение к серверу
		std::cout << "Error: failed connect to server!" << std::endl;
		return 1;
	}

	std::cout << "Connected!" << std::endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_hendler, NULL, NULL, NULL);

	std::string msg1;
	while (true) {
		std::getline(std::cin, msg1);
		int msg_size = msg1.size();
		send(connected, (char*)&msg_size, sizeof(int), NULL); // отправл€ем размер строки 
		send(connected, msg1.c_str(), msg_size, NULL); // отпарвл€ем саму строку
		Sleep(10);
	}

	system("pause");
	return 0;
}