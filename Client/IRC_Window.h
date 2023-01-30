#include "GUI.h"

#ifndef IRC_WINDOW_GUARD
#define IRC_WINDOW_GUARD

using namespace Graph_lib;

struct IRC_Window : public Window {
	IRC_Window(Point xy, int w, int h, const std::string& title);

	Button* name_b;
	Button* connect_b;
	Button* exit_b;

	In_Box* input_text;
	Button* input_button;

	Out_Box* output_text;

	void guit(); // действия
	void name_user();
	void connect();
	void input_t();
private:
	static void exit_c(Address, Address); // обратные вызовы
	static void name_c(Address, Address);
	static void connect_c(Address, Address);
	static void input_c(Address, Address);
};

#endif IRC_WINDOW_GUARD