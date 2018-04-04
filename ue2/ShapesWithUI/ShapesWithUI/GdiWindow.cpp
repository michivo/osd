#include "stdafx.h"

#include "GdiWindow.h"
#include "GdiCanvas.h"

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <string>

GdiWindow::GdiWindow() : h_instance_{ nullptr },
window_handle_{ nullptr }, last_x_pos_{ 0 }, last_y_pos_{ 0 }, last_pos_valid_{ false }
{
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&gdi_token_, &input, nullptr);

	pen_ = std::make_shared<Gdiplus::Pen>(Gdiplus::Color{ 0, 0, 200 }, 2.0F);
	bg_brush_ = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color{ 255, 255, 255 });
	font_brush_ = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color{ 0, 0, 0 });
	font_ = std::make_unique<Gdiplus::Font>(L"Calibri", 16.0F);
}

GdiWindow::~GdiWindow()
{
	font_.reset(); // reset required before shutdown
	pen_.reset();
	bg_brush_.reset();
	font_brush_.reset();
	if (gdi_token_ != 0) {
		Gdiplus::GdiplusShutdown(gdi_token_);
		gdi_token_ = 0;
	}

	DeleteObject(h_instance_);
	h_instance_ = nullptr;

	DeleteObject(window_handle_);
	window_handle_ = nullptr;
}

GdiWindow::GdiWindow(GdiWindow && other) noexcept :
	pen_{ std::move(other.pen_) },
	bg_brush_{ std::move(other.bg_brush_) },
	font_brush_{ std::move(other.font_brush_) },
	font_{ std::move(other.font_) },
	shapes_{ std::move(other.shapes_) },
	last_x_pos_{ other.last_x_pos_ },
	last_y_pos_{ other.last_y_pos_ },
	last_pos_valid_{ other.last_pos_valid_ }
{
	gdi_token_ = other.gdi_token_;
	other.gdi_token_ = 0;

	h_instance_ = other.h_instance_;
	other.h_instance_ = nullptr;

	window_handle_ = other.window_handle_;
	other.window_handle_ = nullptr;

	SetWindowLongPtr(window_handle_, 0, reinterpret_cast<LONG_PTR>(this));
}

GdiWindow & GdiWindow::operator=(GdiWindow && other) noexcept
{
	pen_ = std::move(other.pen_);
	bg_brush_ = std::move(other.bg_brush_);
	font_brush_ = std::move(other.font_brush_);
	font_ = std::move(other.font_);
	shapes_ = std::move(other.shapes_);
	last_x_pos_ = other.last_x_pos_;
	last_y_pos_ = other.last_y_pos_;
	last_pos_valid_ = other.last_pos_valid_;

	gdi_token_ = other.gdi_token_;
	other.gdi_token_ = 0;

	h_instance_ = other.h_instance_;
	other.h_instance_ = nullptr;

	window_handle_ = other.window_handle_;
	other.window_handle_ = nullptr;

	SetWindowLongPtr(window_handle_, 0, reinterpret_cast<LONG_PTR>(this));
	return *this;
}

void GdiWindow::show(std::vector<std::shared_ptr<IDrawableShape>> shapes) {
	
	const auto instance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));
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

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void GdiWindow::register_class(HINSTANCE instance) const
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wnd_proc;
	wcex.cbClsExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = L"";
	wcex.lpszClassName = window_class_;
	wcex.hIconSm = nullptr;
	wcex.cbWndExtra = sizeof(GdiWindow*);

	RegisterClassEx(&wcex);
}


BOOL GdiWindow::init_instance(HINSTANCE h_instance, int cmd_show)
{
	h_instance_ = h_instance;

	window_handle_ = CreateWindow(window_class_, title_, WS_OVERLAPPED,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, h_instance, NULL);

	if (!window_handle_)
	{
		return FALSE;
	}

	SetWindowLongPtr(window_handle_, 0, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(window_handle_, cmd_show);
	UpdateWindow(window_handle_);

	return TRUE;
}

void GdiWindow::redraw_shapes() {
	PAINTSTRUCT ps;
	BeginPaint(window_handle_, &ps);
	Gdiplus::Graphics window_graphics(window_handle_);

	RECT client_rect;
	GetClientRect(window_handle_, &client_rect);
	const int width = client_rect.right - client_rect.left;
	const int height = client_rect.bottom - client_rect.top;
	Gdiplus::Bitmap bmp(width, height);

	auto g = std::shared_ptr<Gdiplus::Graphics>{ Gdiplus::Graphics::FromImage(&bmp) };

	g->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
	g->FillRectangle(bg_brush_.get(), 0, 0, width, height);
	Gdi_canvas canvas{ g, pen_ };

	for (auto& c : shapes_) {
		c->draw(canvas);
	}

	draw_captions(g);
	window_graphics.DrawImage(&bmp, 0, 0, width, height);

	EndPaint(window_handle_, &ps);
}

void GdiWindow::update_shapes(std::function<void(std::shared_ptr<IDrawableShape>)> func)
{
	for (auto& c : shapes_) {
		func(c);
	}

	RedrawWindow(window_handle_, nullptr, nullptr, RDW_INVALIDATE);
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

void GdiWindow::handle_mouse_move(bool is_button_down, const LPARAM param)
{
	if (is_button_down) {
		const auto new_x_pos = static_cast<short>(LOWORD(param));
		const auto new_y_pos = static_cast<short>(HIWORD(param));
		if (last_pos_valid_) {
			auto d_x = new_x_pos - last_x_pos_;
			auto d_y = new_y_pos - last_y_pos_;
			update_shapes([d_x, d_y](std::shared_ptr<IDrawableShape> c) { c->move(d_x, d_y); });
		}
		last_x_pos_ = new_x_pos;
		last_y_pos_ = new_y_pos;
		last_pos_valid_ = true;
	}
	else {
		last_pos_valid_ = false;
	}
}

void GdiWindow::handle_button_down(const WPARAM w_param)
{
	switch (w_param) {
	case VK_UP:
		update_shapes([](std::shared_ptr<IDrawableShape> c) { c->move(0, -5); });
		break;
	case VK_DOWN:
		update_shapes([](std::shared_ptr<IDrawableShape> c) { c->move(0, 5); });
		break;
	case VK_LEFT:
		update_shapes([](std::shared_ptr<IDrawableShape> c) { c->move(-5, 0); });
		break;
	case VK_RIGHT:
		update_shapes([](std::shared_ptr<IDrawableShape> c) { c->move(5, 0); });
		break;
	case VK_ADD:
		update_shapes([](std::shared_ptr<IDrawableShape> c) { c->scale(1.1); });
		break;
	case VK_SUBTRACT:
		update_shapes([](std::shared_ptr<IDrawableShape> c) { c->scale(1.0 / 1.1); });
		break;
	case 'X': // x quits
		PostQuitMessage(0);
		break;
	default:
		break;
	}
}



LRESULT CALLBACK GdiWindow::wnd_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
{
	GdiWindow* self = reinterpret_cast<GdiWindow*>(GetWindowLongPtrW(window_handle, 0));

	if (self == nullptr)
		return DefWindowProc(window_handle, message, w_param, l_param);

	switch (message)
	{
	case WM_KEYDOWN:
		self->handle_button_down(w_param);
		break;

	case WM_MOUSEWHEEL:
		self->update_shapes([w_param](std::shared_ptr<IDrawableShape> c) 
			{ c->scale(static_cast<short>(HIWORD(w_param)) < 0 ? 1.1 : 1.0 / 1.1); });
		break;

	case WM_MOUSEMOVE:
		self->handle_mouse_move((w_param & MK_LBUTTON) == MK_LBUTTON, l_param);
		break;

	case WM_PAINT:
		self->redraw_shapes();
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

