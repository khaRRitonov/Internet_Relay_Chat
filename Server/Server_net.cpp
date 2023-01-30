#include <iostream>
#include <winsock2.h>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996);

std::vector<SOCKET> connection; // коллекция подключений
//SOCKET connection[100];
int counter = 0;

void client_handler(int index) {
	int msg_size;
	while (true) {
		recv(connection[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(connection[index], msg, msg_size, NULL);
		for (int i = 0; i < counter; i++) {
			//if (i == index) {
			//	continue;
			//}
			send(connection[i], (char*)&msg_size, sizeof(int), NULL);
			send(connection[i], msg, msg_size, NULL);
		}
		delete[] msg;
	}
}

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

	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &size_new_addr);

		if (newConnection == 0) {
			std::cout << "Error!" << std::endl;
		}
		else {
			std::cout << "Client Connected!" << std::endl;
			std::string msg = "Hello, It`s my first network program!";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);

			connection.push_back(newConnection);
			counter++;

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_handler, (LPVOID)(i), NULL, NULL); // новый поток
		}
	}

	system("pause");
	return 0;
}