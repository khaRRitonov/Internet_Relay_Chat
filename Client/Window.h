#include <string>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>

//------------------ Point ------------------------------------------------------------

#ifndef POINT_GUARD
#define POINT_GUARD

struct Point {
	int x, y;
	Point(int xx, int yy) : x{ xx }, y{ yy } {}
	Point() : x{ 0 }, y{ 0 } {}
};

inline bool operator== (Point& a, Point& b) { return a.x == b.x && a.y == b.y; }

inline bool operator!= (Point& a, Point& b) { return !(a == b); }

#endif

//------------------ Point end ---------------------------------------------------------

#ifndef WINDOW_GUARD
#define WINDOW_GUARD

namespace Graph_lib {

#undef major
#undef minor

	//-----------------------------------------------------------------------------------

	class Window;
	class Widget;

	int gui_main();

	//----------------- Window ----------------------------------------------------------

	class Window : public Fl_Window {
	private:
		int w, h; // размер окна
		void init();
	protected:
		void draw();
	public:
		Window(int w, int h, const std::string& title);
		Window(Point xy, int w, int h, const std::string& title);

		virtual ~Window() {}

		int x_max() const { return w; }
		int y_max() const { return h; }

		void resize(int ww, int hh) { w = ww, h = hh; size(ww, hh); }

		void set_label(const std::string& s) { label(s.c_str()); }
		
		void attach(Widget&); // добавить элемент окна
		void detach(Widget&); // убирает элемент из окна
	};
}

#endif