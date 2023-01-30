#include "Window.h"
#include "GUI.h"

namespace Graph_lib {
	//----------------- Window ----------------------------------------------------------

	Window::Window(int ww, int hh, const std::string& title) : Fl_Window(ww, hh, title.c_str()), w{ ww }, h{ hh } {
		init();
	}

	Window::Window(Point xy, int ww, int hh, const std::string& title) : Fl_Window(xy.x, xy.y, ww, hh, title.c_str()), w{ ww }, h{ hh } {
		init();
	}

	void Window::init() {
		resizable(this); // изменение размера окна
		show();
	}

	void Window::draw() {
		Fl_Window::draw();
	}

	void Window::attach(Widget& w) {
		begin();
		w.attach(*this);
		end();
	}

	void Window::detach(Widget& w) {
		w.hide();
	}

	//---------------------------------------------------------------------------

	int gui_main() {
		return Fl::run();
	}
}