#include "stdafx.h"

#include "GdiWindow.h"

#include "circle.h"
#include "Point2d.h"
#include "GdiCanvas.h"
#include "ICanvas.h"

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <string>

GdiWindow::GdiWindow()
{
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&gdi_token_, &input, NULL);

	pen_ = std::make_shared<Gdiplus::Pen>(Gdiplus::Color{ 0, 0, 200 }, 2.0F);
	bg_brush_ = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color{ 255, 255, 255 });
	font_brush_ = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color{ 0, 0, 0 });
	font_ = std::make_unique<Gdiplus::Font>( L"Calibri", 16.0F );
}

GdiWindow::~GdiWindow()
{
	font_.reset(); // reset required before shutdown
	pen_.reset();
	bg_brush_.reset();
	font_brush_.reset();
	Gdiplus::GdiplusShutdown(gdi_token_);
}

void GdiWindow::show(std::vector<std::shared_ptr<Circle>> shapes) {

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

ATOM GdiWindow::register_class(HINSTANCE instance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GdiWindow::wnd_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = window_class_;
	wcex.hIconSm = NULL;
	wcex.cbWndExtra = sizeof(GdiWindow*);

	return RegisterClassEx(&wcex);
}


BOOL GdiWindow::init_instance(HINSTANCE h_instance, int cmd_show)
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

void GdiWindow::redraw_shapes(HWND window_handle) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(window_handle, &ps);
	Gdiplus::Graphics window_graphics(window_handle);

	RECT client_rect;
	GetClientRect(window_handle, &client_rect);
	int width = client_rect.right - client_rect.left;
	int height = client_rect.bottom - client_rect.top;
	Gdiplus::Bitmap bmp(width, height);

	auto g = std::shared_ptr<Gdiplus::Graphics> { Gdiplus::Graphics::FromImage(&bmp) };

	g->FillRectangle(bg_brush_.get(), 0, 0, width, height);
	Gdi_canvas canvas{ g, pen_ };

	for (auto& c : shapes_) {
		c->draw(canvas);
	}

	draw_captions(g);
	window_graphics.DrawImage(&bmp, 0, 0, width, height);

	EndPaint(window_handle, &ps);
}

void GdiWindow::update_shapes(HWND window_handle, std::function<void(std::shared_ptr<Circle>)> func)
{
	for (auto& c : shapes_) {
		func(c);
	}

	RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
}

void GdiWindow::draw_captions(std::shared_ptr<Gdiplus::Graphics> g) const
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
		font_.get(), Gdiplus::PointF(3, 3), font_brush_.get());
	g->DrawString(circumference_string.c_str(), static_cast<INT>(circumference_string.length()),
		font_.get(), Gdiplus::PointF(3, 35), font_brush_.get());
}



LRESULT CALLBACK GdiWindow::wnd_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
	GdiWindow* self = reinterpret_cast<GdiWindow*>(GetWindowLongPtrW(window_handle, 0));

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
			self->update_shapes(window_handle, [](std::shared_ptr<Circle> c) { c->scale(1.1); });
			break;
		case VK_SUBTRACT:
			self->update_shapes(window_handle, [](std::shared_ptr<Circle> c) { c->scale(1.0/1.1); });
			break;
		case 'X': // x quits
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

