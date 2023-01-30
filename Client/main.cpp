#include "IRC_Window.h"

int main() {
	IRC_Window win(Point(100, 100), 600, 400, "IRC");
	
	return Graph_lib::gui_main();
}