#pragma once

#include "IShape.h"
#include "Point2d.h"

#include <Windows.h>
#include <cassert>
#include <functional>
#include <vector>
#include <memory>

constexpr int MAX_LOADSTRING = 100;

class GdiWindow {
public:
	GdiWindow();
	~GdiWindow();
	GdiWindow(const GdiWindow&) = delete; // no copy because then two window objects would operate on one physical window
	GdiWindow(GdiWindow&& other); // move is ok
	GdiWindow& operator=(const GdiWindow&) = delete; // no copy again
	GdiWindow& operator=(GdiWindow&&); // move is ok

	void show(std::vector<std::shared_ptr<IShape>> shapes);

private:

	HINSTANCE h_instance_;								// current instance
	HWND window_handle_;
	const TCHAR title_[MAX_LOADSTRING] = L"Shapes";
	const TCHAR window_class_[MAX_LOADSTRING] = L"ECE_Shapes";

	std::shared_ptr<Gdiplus::Pen> pen_;
	std::unique_ptr<Gdiplus::SolidBrush> bg_brush_;
	std::unique_ptr<Gdiplus::SolidBrush> font_brush_;
	std::unique_ptr<Gdiplus::Font> font_;
	ULONG_PTR gdi_token_;
	std::vector<std::shared_ptr<IShape>> shapes_;
	short last_x_pos_;
	short last_y_pos_;
	bool last_pos_valid_;

	ATOM					register_class(HINSTANCE instance);
	BOOL					init_instance(HINSTANCE, int);
	static LRESULT CALLBACK	wnd_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param);
	void					redraw_shapes();
	void					update_shapes(std::function<void(std::shared_ptr<IShape>)> func);
	void					draw_captions(std::shared_ptr<Gdiplus::Graphics> g) const;
	void					handle_mouse_move(bool is_button_down, LPARAM param);
	void					handle_button_down(WPARAM w_param);
};
