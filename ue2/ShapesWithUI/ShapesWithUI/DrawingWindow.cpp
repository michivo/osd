#include "stdafx.h"

#include "DrawingWindow.h"

#include "circle.h"
#include "Point2d.h"

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace DrawingWindow;

Window::Window() {
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&gdi_token_, &input, NULL);
}

Window::~Window()
{
	delete pen_;
	pen_ = nullptr;

	delete brush_;
	brush_ = nullptr;
	
	Gdiplus::GdiplusShutdown(gdi_token_);
}

void Window::show(std::vector<std::shared_ptr<Circle>> shapes) {	

	HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));
	shapes_ = shapes;

	// Assert that the values returned are expected.
	assert(instance != nullptr);

	MSG msg;

	register_class(instance);

	// Perform application initialization:
	if (!init_instance(instance, SW_SHOWDEFAULT))
	{
		throw std::runtime_error("Initialization failed!");
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

ATOM Window::register_class(HINSTANCE instance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Window::wnd_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = 0; 
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = window_class_;
	wcex.hIconSm = NULL;
	wcex.cbWndExtra = sizeof(Window*);

	return RegisterClassEx(&wcex);
}


BOOL Window::init_instance(HINSTANCE h_instance, int cmd_show)
{
	HWND hWnd;

	h_instance_ = h_instance;

	hWnd = CreateWindow(window_class_, title_, WS_OVERLAPPED,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, h_instance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SetWindowLongPtr(hWnd, 0, reinterpret_cast<LONG_PTR>(this));


	pen_ = new Gdiplus::Pen{ Gdiplus::Color{ 0, 0, 200 }, 2.0F };
	brush_ = new Gdiplus::SolidBrush{ Gdiplus::Color{ 255, 255, 255 } };

	ShowWindow(hWnd, cmd_show);
	UpdateWindow(hWnd);

	return TRUE;
}

void Window::redraw_shapes(HWND window_handle) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(window_handle, &ps);

	Gdiplus::Graphics g{ window_handle, false };
	RECT clientRect;
	GetClientRect(window_handle, &clientRect);
	g.FillRectangle(brush_, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	for (auto& c : shapes_) {
		c->draw(pen_, g);
	}

	EndPaint(window_handle, &ps);
}

LRESULT CALLBACK Window::wnd_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
	int wmId;
	int wmEvent;
	Window* self = reinterpret_cast<Window*>(GetWindowLongPtrW(window_handle, 0));

	switch (message)
	{
	case WM_KEYDOWN:
		switch (w_param) {
		case VK_UP:
			for (auto& c : self->shapes_) {
				c->move(0, -5);
			}
			self->redraw_shapes(window_handle);
			break;
		case VK_DOWN:
			for (auto& c : self->shapes_) {
				c->move(0, 5);
			}
			self->redraw_shapes(window_handle);
			break;
		case VK_LEFT:
			for (auto& c : self->shapes_) {
				c->move(-5, 0);
			}
			self->redraw_shapes(window_handle);
			break;
		case VK_RIGHT:
			for (auto& c : self->shapes_) {
				c->move(5, 0);
			}
			self->redraw_shapes(window_handle);
			break;
		case VK_ADD:
			for (auto& c : self->shapes_) {
				c->scale(1.1);
			}
			self->redraw_shapes(window_handle);
			break;
		case VK_SUBTRACT:
			for (auto& c : self->shapes_) {
				c->scale(.9);
			}
			self->redraw_shapes(window_handle);
			break;
		default:
			break;
		}

		break;

	case WM_PAINT:
		self->redraw_shapes(window_handle);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message, w_param, l_param);
	}
	return 0;
}

