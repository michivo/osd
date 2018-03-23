// ShapesWithUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GdiWindow.h"
#include "Circle.h"
#include "IShape.h"
#include "Rect.h"

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>


int main()
{
	std::vector<std::shared_ptr<IDrawableShape>> shapes; // create list of IShape
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Circle{ 100, {300, 300} }}); // add some shapes
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Rect{ sqrt(2)*100, sqrt(2) * 100,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Circle{ sqrt(2) * 50,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Circle{ sqrt(2) * 100,{ 300, 300 } }});

	GdiWindow w; // create window
	w.show(shapes); // show window

	return 0;
}