#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Input.h>
#include <FL/Fl_Menu_Bar.h>
#include <FL/Fl_Menu_Item.h>

int main() {
	Fl_Window win(900, 500, "Window");
	Fl_Box box(0, 0, 200, 200, "Hello World!");

	Fl_Input iput(0, 465, 900, 30, "Enter");

	Fl_Menu_Bar menu(0, 0, 850, 30, NULL);
	Fl_Menu_Bar menu_exit(850, 0, 50, 30, NULL);
	menu.add("Name User");
	menu.add("Connect");
	menu_exit.add(" Exit");
	

	win.show();
	return Fl::run();
}