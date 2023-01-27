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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); // сокет 
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); // привязка адреса сокета
	listen(sListen, SOMAXCONN); // прослушивание

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &size_new_addr);

	if (newConnection == 0) {
		std::cout << "Error!" << std::endl;
	}
	else {
		std::cout << "Client Connected!" << std::endl;
		char msg[] = " ";
		std::cin >> msg;
		send(newConnection, msg, sizeof(msg), NULL);
	}

	system("pause");
	return 0;
}