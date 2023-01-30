#include "GUI.h"

namespace Graph_lib {
	//----------------- Widget ----------------------------------------------------------
	// 
	//----------------- Button ----------------------------------------------------------

	void Button::attach(Window& win) {
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win);
		own = &win;
	}

	//----------------- In_Box ----------------------------------------------------------

	void In_Box::attach(Window& win) {
		pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win);
		own = &win;
	}

	//----------------- Out_Box ----------------------------------------------------------

	void Out_Box::attach(Window& win) {
		pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win);
		own = &win;
	}
}