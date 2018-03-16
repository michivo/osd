// ShapesWithUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GdiWindow.h"
#include "Circle.h"
#include "IShape.h"
#include "Rect.h"
#include "SvgCanvas.h"

#include <vector>
#include <memory>
#include <math.h>
#include <iostream>
#include <fstream>

void write_svg_file(const std::vector<std::shared_ptr<IShape>>& shapes);

int main()
{
	std::vector<std::shared_ptr<IShape>> shapes; // create list of IShape
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ 100, {300, 300} }}); // add some shapes
	shapes.push_back(std::shared_ptr<IShape> { new Rect{ sqrt(2)*100, sqrt(2) * 100,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ sqrt(2) * 50,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ sqrt(2) * 100,{ 300, 300 } }});
	
	//write_svg_file(shapes);

	GdiWindow w; // create window
	w.show(shapes); // show window

	return 0;
}


void write_svg_file(const std::vector<std::shared_ptr<IShape>>& shapes) {
	std::ofstream svg_file;
	svg_file.open("test.html", std::ios::out | std::ios::trunc);
	SvgCanvas canvas{ svg_file };
	canvas.start_drawing();
	for (auto shape : shapes) {
		shape->draw(canvas);
	}
	canvas.finish_drawing();
	svg_file.close();
}
