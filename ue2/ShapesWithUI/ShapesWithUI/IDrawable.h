#pragma once

#include "ICanvas.h"

class IDrawable
{
public:
	virtual ~IDrawable() = 0;

	virtual void draw(ICanvas& canvas) const = 0;
};
