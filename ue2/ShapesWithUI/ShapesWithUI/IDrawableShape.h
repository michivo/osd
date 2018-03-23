#pragma once

#include "IDrawable.h"
#include "IShape.h"

class IDrawableShape : public IDrawable, public IShape
{
};
