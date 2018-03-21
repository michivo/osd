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

void write_svg_file();

int main()
{
	std::vector<std::shared_ptr<IShape>> shapes; // create list of IShape
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ 100, {300, 300} }}); // add some shapes
	shapes.push_back(std::shared_ptr<IShape> { new Rect{ sqrt(2)*100, sqrt(2) * 100,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ sqrt(2) * 50,{ 300, 300 } }});
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ sqrt(2) * 100,{ 300, 300 } }});
	
	write_svg_file();

	GdiWindow w; // create window
	w.show(shapes); // show window

	return 0;
}


void write_svg_file() {
	std::ofstream svg_file;
	svg_file.open("test.html", std::ios::out | std::ios::trunc);
	SvgCanvas canvas{ svg_file };
	canvas.start_drawing();

	std::vector<std::shared_ptr<IShape>> shapes;
	shapes.push_back(std::shared_ptr<IShape> { new Circle{ 500,{ 500, 500 } }}); // add some shapes
	shapes.push_back(std::shared_ptr<IShape> { new Rect{ 1000, 1000,{ 500, 500 } }});
	double scale_factor = 1/sqrt(2);
	for (int i = 0; i < 15; i++) {
		for (auto shape : shapes) {
			shape->draw(canvas);
			shape->scale(scale_factor);
		}
	}
	canvas.finish_drawing();
	svg_file.close();
}
