#include "Window.h"
#include <FL/Fl.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Input.h>
#include <FL/Fl_Output.h>

#ifndef GUI_GUARD
#define GUI_GUARD

namespace Graph_lib {

	typedef void* Address;
	typedef void(*Callback)(Address, Address);

	//-----------------------------------------------------------------------------------

	template<typename W> W& reference_to(Address pw) {
		return *static_cast<W*>(pw);
	}

	//----------------- Widget ----------------------------------------------------------

	class Widget {
	private:
		Widget& operator= (const Window&);
		Widget(const Widget&);
	protected:
		Window* own;
		Fl_Widget* pw;
	public:
		Widget(Point xy, int w, int h, const std::string& s, Callback cd) : loc{ xy }, width{ w }, height{ h }, label{ s }, do_it{ cd } {}
		virtual ~Widget() { }

		virtual void move(int dx, int dy) { hide(); pw->position(loc.x += dx, loc.y += dy); show(); }
		virtual void hide() { pw->hide(); }
		virtual void show() { pw->show(); }
		virtual void attach(Window&) = 0; // каждый объект Widget определ€ет хот€бы одно действие над окном

		Point loc;
		int width;
		int height;
		std::string label;
		Callback do_it; // выполн€ет действие пользовател€
	};

	//----------------- Widget  end -----------------------------------------------------
	// 
	//----------------- Button ----------------------------------------------------------

	struct Button : public Widget {
		Button(Point xy, int w, int h, const std::string& label, Callback cb) : Widget(xy, w, h, label, cb) {}
		void attach(Window&);
	};

	//----------------- In_Box ----------------------------------------------------------

	struct In_Box : public Widget {
		In_Box(Point xy, int w, int h, const std::string& s) : Widget(xy, w, h, s, NULL) {}
		void attach(Window&);
		std::string get_string();
	};

	//----------------- Out_Box ----------------------------------------------------------

	struct Out_Box : public Widget {
		Out_Box(Point xy, int w, int h, const std::string& s) : Widget(xy, w, h, s, NULL) {}
		void attach(Window&);
		void put_string(const std::string& s);
	};
}

#endif GUI_GUARD