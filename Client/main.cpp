#include "Window.h"

int main() {
	Graph_lib::Window win(500, 500, "Window");

	Graph_lib::Button b(Graph_lib::Point(100, 0), 20, 100, "Test", NULL);

	win.attach(b);
	
	return Graph_lib::gui_main();
}