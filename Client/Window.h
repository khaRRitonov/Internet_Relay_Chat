#include <string>
#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.h>


namespace Graph_lib {

#undef major
#undef minor
	//---------------------------------------------------------------------------

	typedef void* Address;
	typedef void(*Callback)(Address, Address);

	class Window;
	class Widget;

	int gui_main();


	//---------------------------------------------------------------------------

	struct Point {
		int x, y;
		Point(int xx, int yy) : x{xx}, y{yy} {}
		Point() : x{ 0 }, y{ 0 } {}
	};

	inline bool operator== (Point& a, Point& b) { return a.x == b.x && a.y == b.y; }

	inline bool operator!= (Point& a, Point& b) { return !(a == b); }

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
		Callback do_it;
	};

	struct Button : public Widget {
		Button(Point xy, int w, int h, const std::string& label, Callback cb) : Widget(xy, w, h, label, cb) {}
		void attach(Window&);
	};

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