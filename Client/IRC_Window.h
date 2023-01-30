#include "GUI.h"

using namespace Graph_lib;

struct IRC_Window : public Window {
	IRC_Window(Point xy, int w, int h, const std::string& title);

	Button* name_b;
	Button* connect_b;
	Button* exit_b;

	In_Box* in1;

	Out_Box* out1;

	void guit(); // действия
	void name_user();
	void connect();
private:
	static void exit_c(Address, Address); // обратные вызовы
	static void name_c(Address, Address);
	static void connect_c(Address, Address);
};