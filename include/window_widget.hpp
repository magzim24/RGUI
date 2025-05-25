#include "error_codes.hpp"

#include <limits.h>
#include <string>

#ifndef WINDOW_WIDGET_HPP
#define WINDOW_WIDGET_HPP

#define RGUIEmptyArg ULLONG_MAX

struct SizeRect{
	int width, height;
};

struct Pos{
	int X, Y;
};

class App;

class RGUI_Rect{
    protected:
	SizeRect *size;
	Pos *position;
	public:
		RGUI_Rect():size(nullptr), position(nullptr){}
		virtual ~RGUI_Rect(){
			if(size) delete size;
			if(position) delete position;
		}
        virtual RGUI_Error setSize(size_t width, size_t height);
        virtual RGUI_Error setPos(size_t left, size_t top);
};

class AbstractWindow: public RGUI_Rect{
	private:
	protected:
		virtual RGUI_Error init(App *app) = 0;
        virtual RGUI_Error update() = 0;
	public:
		virtual RGUI_Error display() = 0;
        virtual RGUI_Error setSize(size_t width, size_t height) = 0;
        virtual RGUI_Error setPos(size_t left, size_t top) = 0;
};

typedef AbstractWindow ABCWindow;


#ifdef PLATFORM_WINDOWS

	#include <windows.h>
	
	class App{
	protected:
		HINSTANCE hInst;
	public:
		App();
		virtual ~App(){};
        HINSTANCE getHINST(){ return hInst; }
	};

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	class Win32ImpWindow: public ABCWindow{
		HWND handle;
		App *app;
		protected:
			RGUI_Error init(App *app);
            RGUI_Error update();
			RGUI_Error run();
		public:
			Win32ImpWindow(App *app);
			virtual ~Win32ImpWindow();
			virtual RGUI_Error display();
            RGUI_Error setSize(size_t width, size_t height);
            RGUI_Error setPos(size_t left, size_t top);
	};

#elif PLATFORM_LINUX

	class LinuxImpWindow: public ABCWindow{
		public:
			LinuxImpWindow();
			virtual ~LinuxImpWindow();
			virtual RGUI_Error display();
	};

#endif

class RGUIWindow{
	ABCWindow *windowImp;
    public:
        RGUIWindow(App *app);
        RGUI_Error display() const ;
        RGUI_Error setWindowSize(size_t width, size_t height);
        RGUI_Error setWindowPos(size_t left, size_t top);
};


#endif
