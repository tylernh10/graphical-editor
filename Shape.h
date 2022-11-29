#ifndef ECSHAPE_H
#define ECSHAPE_H

#include "ECGraphicViewImp.h"

class Shape {
public:
	Shape(int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {}
	~Shape() {}
	ECDrawiingContext getAttributes() { return attributes; }
	int getX1() const { return x1; }
	int getY1() const { return y1; }
	int getX2() const { return x2; }
	int getY2() const { return y2; }
	void setX1(int x) { x1 = x; }
	void setY1(int y) { y1 = y; }
	void setX2(int x) { x2 = x; }
	void setY2(int y) { y2 = y; }
	virtual bool isPointInside(int px, int py) const = 0;
	void selectedColorChange() { attributes.SetColor(ECGV_BLUE); }
	void unselectedColorChange() { attributes.SetColor(ECGV_BLACK); }
private:
	ECDrawiingContext attributes;
	int x1; // corner 1
	int y1;
	int x2; // corner 2
	int y2;
};

class Rectangle : public Shape {
public:
	Rectangle(int x1, int y1, int x2, int y2): Shape(x1, y1, x2, y2) {}
	virtual bool isPointInside(int px, int py) const override;
};

#endif

// TODO: Rectangle class
