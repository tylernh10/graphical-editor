#ifndef ECSHAPE_H
#define ECSHAPE_H

#include "ECGraphicViewImp.h"

class Shape {
public:
	Shape(): x1(100), y1(100), x2(400), y2(400) {}
	Shape(int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {}
	~Shape() {}
	ECDrawiingContext getAttributes() { return attributes; }
	int x1;
	int y1;
	int x2;
	int y2;
private:
	ECDrawiingContext attributes;
};

#endif

// TODO: Rectangle class
