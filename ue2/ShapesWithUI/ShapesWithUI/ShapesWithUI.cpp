// ShapesWithUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GdiWindow.h"
#include "Circle.h"
#include "Rect.h"

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "SvgCanvas.h"


int main()
{
	std::vector<std::shared_ptr<IDrawableShape>> shapes; // create list of IShape
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Circle{ 100, {300, 300} }}); // add some shapes
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Rect{ sqrt(2) * 100, sqrt(2) * 100,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Circle{ sqrt(2) * 50,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IDrawableShape> { new Circle{ sqrt(2) * 100,{ 300, 300 } }});

	//GdiWindow w; // create window
	//w.show(shapes); // show window

	std::ofstream output{ "test.html", std::ofstream::out | std::ofstream::trunc };

	Svg_canvas c{ output };
	c.write_header(1000, 1000);
	for(const auto shape : shapes)
	{
		shape->draw(c);
	}
	c.write_footer();

	output.close();

	return 0;
}
