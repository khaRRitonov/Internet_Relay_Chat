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

	std::string In_Box::get_string() {
		Fl_Input& pi = reference_to<Fl_Input>(pw);
		return std::string(pi.value());
	}

	//----------------- Out_Box ----------------------------------------------------------

	void Out_Box::attach(Window& win) {
		pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win);
		own = &win;
	}

	void Out_Box::put_string(const std::string& s) {
		reference_to<Fl_Output>(pw).value(s.c_str());
	}
}