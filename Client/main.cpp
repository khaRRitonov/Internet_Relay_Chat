#include <string>
#include <iostream>
#include <winsock2.h>
#include "IRC_Window.h"

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996);

SOCKET connected;
IRC_Window win(Point(100, 100), 600, 400, "IRC");

void client_hendler() {
	int msg_size;
	while (true) {
		recv(connected, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(connected, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		win.output_text->put_string(msg); // выводим строку в поле вывода
		delete[] msg;
	}
}

void connect_net() {

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); // версия библиотеки WinSock
	if (WSAStartup(DLLVersion, &wsaData) != 0) { // Загружаем библиотеку
		std::cout << "Error!" << std::endl;
		//return 1;
	}

	SOCKADDR_IN addr; // структура хранения адреса
	int size_new_addr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	connected = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connected, (SOCKADDR*)&addr, sizeof(addr)) != 0) { // присоединение к серверу
		std::cout << "Error: failed connect to server!" << std::endl;
		//return 1;
	}

	std::cout << "Connected!" << std::endl;

	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_hendler, NULL, NULL, NULL);
	client_hendler();

	std::string msg1;                        
	while (true) {
		//std::getline(std::cin, msg1);
		
		msg1 = win.input_text->get_string(); // вводим строку в полe ввода

		int msg_size = msg1.size();
		send(connected, (char*)&msg_size, sizeof(int), NULL); // отправляем размер строки 
		send(connected, msg1.c_str(), msg_size, NULL); // отпарвляем саму строку
		Sleep(10);
	}

	system("pause");
}

int main() {

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)connect_net, NULL, NULL, NULL);

	return Graph_lib::gui_main();
}