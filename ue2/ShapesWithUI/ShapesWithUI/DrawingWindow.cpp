#include "stdafx.h"

#include "DrawingWindow.h"

#include "circle.h"
#include "Point2d.h"

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <string>

using namespace DrawingWindow;

Window::Window()
{
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&gdi_token_, &input, NULL);

	pen_ = new Gdiplus::Pen{ Gdiplus::Color{ 0, 0, 200 }, 2.0F };
	bg_brush_ = new Gdiplus::SolidBrush{ Gdiplus::Color{ 255, 255, 0 } };
	font_brush_ = new Gdiplus::SolidBrush{ Gdiplus::Color{ 0, 0, 0 } };
	font_ = new Gdiplus::Font{ L"Arial", 16 };
}

Window::~Window()
{
	delete font_;
	font_ = nullptr;

	delete bg_brush_;
	bg_brush_ = nullptr;

	delete font_brush_;
	font_brush_ = nullptr;

	delete pen_;
	pen_ = nullptr;

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

	ShowWindow(hWnd, cmd_show);
	UpdateWindow(hWnd);

	return TRUE;
}

void Window::redraw_shapes(HWND window_handle) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(window_handle, &ps);
	Gdiplus::Graphics window_graphics(window_handle);

	RECT clientRect;
	GetClientRect(window_handle, &clientRect);
	int width = clientRect.right - clientRect.left;
	int height = clientRect.bottom - clientRect.top;
	Gdiplus::Bitmap bmp(width, height);
	Gdiplus::Graphics *g = Gdiplus::Graphics::FromImage(&bmp);
	g->FillRectangle(bg_brush_, 0, 0, width, height);

	for (auto& c : shapes_) {
		c->draw(pen_, g);
	}

	draw_captions(g);
	window_graphics.DrawImage(&bmp, 0, 0, width, height);

	delete g;
	EndPaint(window_handle, &ps);
}

void Window::update_shapes(HWND window_handle, std::function<void(std::shared_ptr<Circle>)> func)
{
	for (auto& c : shapes_) {
		func(c);
	}

	RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
}

void DrawingWindow::Window::draw_captions(Gdiplus::Graphics* g) const
{
	double area = 0.0;
	double circumference = 0.0;

	for (auto& c : shapes_) {
		area += c->area();
		circumference += c->circumference();
	}

	std::wstring area_string = L"Total Area: " + std::to_wstring(area);
	std::wstring circumference_string = L"Total Circumference: " + std::to_wstring(circumference);
	g->DrawString(area_string.c_str(), static_cast<INT>(area_string.length()),
		font_, Gdiplus::PointF(3, 3), font_brush_);
	g->DrawString(circumference_string.c_str(), static_cast<INT>(circumference_string.length()),
		font_, Gdiplus::PointF(3, 35), font_brush_);
}



LRESULT CALLBACK Window::wnd_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
	Window* self = reinterpret_cast<Window*>(GetWindowLongPtrW(window_handle, 0));

	switch (message)
	{
	case WM_KEYDOWN:
		switch (w_param) {
		case VK_UP:
			self->update_shapes(window_handle, [](std::shared_ptr<Circle> c) { c->move(0, -5); });
			break;
		case VK_DOWN:
			self->update_shapes(window_handle, [](std::shared_ptr<Circle> c) { c->move(0, 5); });
			break;
		case VK_LEFT:
			self->update_shapes(window_handle, [](std::shared_ptr<Circle> c) { c->move(-5, 0); });
			break;
		case VK_RIGHT:
			self->update_shapes(window_handle, [](std::shared_ptr<Circle> c) { c->move(5, 0); });
			break;
		case VK_ADD:
			self->update_shapes(window_handle, 
				[](std::shared_ptr<Circle> c) { c->scale(1.1); });
			break;
		case VK_SUBTRACT:
			self->update_shapes(window_handle, 
				[](std::shared_ptr<Circle> c) { c->scale(0.9); });
			break;
		case 0x58: // 'X' key - quits
			PostQuitMessage(0);
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
	case WM_ERASEBKGND:
		return TRUE;
	default:
		return DefWindowProc(window_handle, message, w_param, l_param);
	}
	return 0;
}

