#include "window_widget.hpp"

#ifdef PLATFORM_WINDOWS
    RGUI_Error RGUI_Rect::setSize(size_t width, size_t height){
        return RGUI_NO_ERROR;
    }
    RGUI_Error RGUI_Rect::setPos(size_t left, size_t top){
        return RGUI_NO_ERROR;
    }

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
        switch (msg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            // Обработка других сообщений
            case WM_PAINT: {
            PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
                EndPaint(hwnd, &ps);
                return 0;
            }
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    RGUI_Error Win32ImpWindow::setSize(size_t width, size_t height){
        if(width == RGUIEmptyArg) width = this->size->width;
        if(height == RGUIEmptyArg) height = this->size->height;
        BOOL err = SetWindowPos(handle, NULL, 0, 0, width, height, SWP_NOZORDER);
        this->update();
        if(!err)
            return RGUI_WINDOW_RESIZE_ERROR;
        return RGUI_NO_ERROR;
    }

    RGUI_Error Win32ImpWindow::setPos(size_t left, size_t top){
        return RGUI_NO_ERROR;
    }

    RGUI_Error Win32ImpWindow::init(App *app){
        this->app = app;
        LPCSTR CLASS_NAME = "Sample Window Class";
        WNDCLASS wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = app->getHINST();
        wc.lpszClassName = CLASS_NAME;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

        RegisterClass(&wc);

        // Создание окна
        handle = CreateWindowExA(
        0,                              // Расширенные стили (0 для стандартного окна)
        CLASS_NAME,                     // Имя класса окна
        "Sample Window",               // Заголовок окна
        WS_POPUP,            // Стили окна
        CW_USEDEFAULT, CW_USEDEFAULT,   // Позиция (x, y)
        800, 600,                       // Размер (ширина, высота)
        nullptr,                        // Родительское окно
        nullptr,                        // Меню
        app->getHINST(),                      // Экземпляр приложения
        nullptr                         // Дополнительные данные
        );
        if(handle == NULL) return RGUI_WINDOW_INITIALIZATION_ERROR;
        return RGUI_NO_ERROR;
    }
    #include <iostream>
    Win32ImpWindow::Win32ImpWindow(App *app){
        RGUI_Error err = init(app);
        if(err) std::cout << err;
    }

    Win32ImpWindow::~Win32ImpWindow(){

    }

    RGUI_Error Win32ImpWindow::update(){
        UpdateWindow(handle);
        return RGUI_NO_ERROR;
    }

    RGUI_Error Win32ImpWindow::display(){
        ShowWindow(handle, SW_SHOWNORMAL);
        this->update();
        //run();
        return RGUI_NO_ERROR;
    }

    RGUI_Error Win32ImpWindow::run(){
        HACCEL hAccel = LoadAccelerators(app->getHINST(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
        BOOL bRet = 0;
        MSG msg;
        while ((bRet = GetMessage(&msg, nullptr, 0, 0)))
        {
            if ( -1 == bRet ) break;
            if ( !TranslateAccelerator(handle, hAccel, &msg) )
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
                }
        }
        return RGUI_NO_ERROR;
    }

    App::App(){
        hInst = GetModuleHandle(NULL);
    }

    RGUIWindow::RGUIWindow(App *app){
        windowImp = new Win32ImpWindow(app);
    }

    RGUI_Error RGUIWindow::display() const{
        return windowImp->display();
    }

    RGUI_Error RGUIWindow::setWindowSize(size_t width, size_t height){
        return windowImp->setSize(width, height);
        
    }
    RGUI_Error RGUIWindow::setWindowPos(size_t left, size_t top){
        return windowImp->setPos(left, top);
    }

#elif PLATFORM_LINUX

    LinuxImpWindow::LinuxImpWindow(){

    }

    LinuxImpWindow::~LinuxImpWindow(){

    }

    RGUI_Error LinuxImpWindow::display(){
        return RGUI_NO_ERROR;
    }

#endif
