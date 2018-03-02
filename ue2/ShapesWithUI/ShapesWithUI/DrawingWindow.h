#pragma once

#include "circle.h"
#include "Point2d.h"

#include <Windows.h>
#include <cassert>
#include <vector>
#include <memory>

namespace DrawingWindow {

	constexpr int MAX_LOADSTRING = 100;

	class Window {
	public:
		Window();

		~Window();

		void show(std::vector<std::shared_ptr<Circle>> shapes);

	private:

		HINSTANCE h_instance_;								// current instance
		TCHAR title_[MAX_LOADSTRING] = L"Shapes";					
		TCHAR window_class_[MAX_LOADSTRING] = L"ECE_Shapes";
		Gdiplus::Pen *pen_;
		Gdiplus::Brush *brush_;
		ULONG_PTR gdi_token_;
		std::vector<std::shared_ptr<Circle>> shapes_;
		
		ATOM					register_class(HINSTANCE hInstance);
		BOOL					init_instance(HINSTANCE, int);
		static LRESULT CALLBACK	wnd_proc(HWND, UINT, WPARAM, LPARAM);
		void					redraw_shapes(HWND hWnd);
	};
}
