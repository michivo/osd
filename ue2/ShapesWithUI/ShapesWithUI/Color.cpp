#include "stdafx.h"

#include "Color.h"

namespace drawing {
	Color::Color() : R{ 0 }, G{ 0 }, B{ 0 }, A{ 0 } 
	{
	}

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R{ r }, G{ g }, B{ b }, A{ a }
	{
	}
}