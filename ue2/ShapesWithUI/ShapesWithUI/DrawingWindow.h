#pragma once

#include "circle.h"
#include "Point2d.h"

#include <Windows.h>
#include <cassert>
#include <functional>
#include <vector>
#include <memory>

namespace DrawingWindow {

	constexpr int MAX_LOADSTRING = 100;

	class Window {
	public:
		Window();
		~Window();
		Window(const Window&) = delete; // no copy because then two window objects would operate on one physical window
		Window(Window&&) = default; // move is ok
		Window& operator=(const Window&) = delete; // no copy again
		Window& operator=(Window&&) = default; // move is ok

		void show(std::vector<std::shared_ptr<Circle>> shapes);

	private:

		HINSTANCE h_instance_;								// current instance
		const TCHAR title_[MAX_LOADSTRING] = L"Shapes";					
		const TCHAR window_class_[MAX_LOADSTRING] = L"ECE_Shapes";

		std::unique_ptr<Gdiplus::Pen> pen_;
		std::unique_ptr<Gdiplus::SolidBrush> bg_brush_;
		std::unique_ptr<Gdiplus::SolidBrush> font_brush_;
		std::unique_ptr<Gdiplus::Font> font_;
		ULONG_PTR gdi_token_;
		std::vector<std::shared_ptr<Circle>> shapes_;
		
		ATOM					register_class(HINSTANCE instance);
		BOOL					init_instance(HINSTANCE, int);
		static LRESULT CALLBACK	wnd_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param);
		void					redraw_shapes(HWND window_handle);
		void					update_shapes(HWND window_handle, std::function<void(std::shared_ptr<Circle>)> func);
		void					draw_captions(Gdiplus::Graphics* g) const;
	};
}
