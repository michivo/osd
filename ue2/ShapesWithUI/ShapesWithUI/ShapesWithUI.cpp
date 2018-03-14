// ShapesWithUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GdiWindow.h"
#include "Circle.h"
#include "IShape.h"
#include "Rect.h"

#include <vector>
#include <memory>
#include <math.h>

int main()
{
	std::vector<std::shared_ptr<IShape>> shapes; // create list of IShape
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ 100, {300, 300} }}); // add some shapes
	shapes.push_back(std::shared_ptr<IShape> { new Rect{ 200, 200,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Rect{ sqrt(2)*100, sqrt(2) * 100,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ sqrt(2) * 50,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ sqrt(2) * 100,{ 300, 300 } }});
	
	GdiWindow w; // create window
	w.show(shapes); // show window

	return 0;
}

