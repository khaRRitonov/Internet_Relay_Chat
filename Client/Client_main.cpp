#include <iostream>
#include <winsock2.h>


#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996);

int main() {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); // версия библиотеки WinSock
	if (WSAStartup(DLLVersion, &wsaData) != 0) { // Загружаем библиотеку
		std::cout << "Error!" << std::endl;
		return 1;
	}

	SOCKADDR_IN addr; // структура хранения адреса
	int size_new_addr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET connected = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connected, (SOCKADDR*)&addr, sizeof(addr)) != 0) { // присоединение к серверу
		std::cout << "Error: failed connect to server!" << std::endl;
		return 1;
	}

	std::cout << "Connected!" << std::endl;
	char msg[256];
	recv(connected, msg, sizeof(msg), NULL);

	std::cout << msg << std::endl;

	system("pause");
	return 0;
}