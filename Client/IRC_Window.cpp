#include "IRC_Window.h"

using namespace Graph_lib;

IRC_Window::IRC_Window(Point xy, int w, int h, const std::string& title) : Window(xy, w, h, title.c_str()) {
	name_b = new Button(Point(0, 0), 100, 30, "Enter Name", name_c);
	connect_b = new Button(Point(100, 0), 100, 30, "Connect", NULL);
	exit_b = new Button(Point(x_max() - 100, 0), 100, 30, "Exit", exit_c);
	attach(*name_b);
	attach(*connect_b);
	attach(*exit_b);

	input_text = new In_Box(Point(0, y_max() - 30), x_max() - 100, 30, "Text"); // строка ввода
	attach(*input_text);
	input_button = new Button(Point(x_max() - 100, y_max() - 30), 100, 30, "Send", input_c);
	attach(*input_button);

	output_text = new Out_Box(Point(0, 30), x_max(), y_max() - 60, "Text"); // поле вывода
	attach(*output_text);
}

//------------------------------------------------------------------------------

void IRC_Window::exit_c(Address, Address pw) {
	reference_to<IRC_Window>(pw).guit();
}

void IRC_Window::guit() {
	hide();
}

//------------------------------------------------------------------------------

void IRC_Window::name_c(Address, Address pw) {
	reference_to<IRC_Window>(pw).name_user();
}

void IRC_Window::name_user() {
	Window win(Point((x_max()/2) - 80, (y_max()/2) + 20), 350, 40, "Enter Name");
	In_Box in(Point(90, 5), 150, 30, "Enter Name:");
	Button b(Point(240, 5), 100, 30, "Ok", NULL);
	win.attach(b);
	win.attach(in);
	gui_main();
}

//------------------------------------------------------------------------------

void IRC_Window::connect_c(Address, Address pw) {
	reference_to<IRC_Window>(pw).connect();
}

void IRC_Window::connect() {

}

//------------------------------------------------------------------------------

void IRC_Window::input_c(Address, Address pw) {
	reference_to<IRC_Window>(pw).input_t();
}

void IRC_Window::input_t() {

	output_text->put_string(input_text->get_string());
}

//------------------------------------------------------------------------------