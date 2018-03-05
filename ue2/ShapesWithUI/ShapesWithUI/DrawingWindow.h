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

		Window(const Window&) = delete;

		Window& operator=(const Window&) = delete;

		void show(std::vector<std::shared_ptr<Circle>> shapes);

	private:

		HINSTANCE h_instance_;								// current instance
		TCHAR title_[MAX_LOADSTRING] = L"Shapes";					
		TCHAR window_class_[MAX_LOADSTRING] = L"ECE_Shapes";
		Gdiplus::Pen* pen_;
		Gdiplus::SolidBrush* bg_brush_;
		Gdiplus::SolidBrush* font_brush_;
		Gdiplus::Font* font_;
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
