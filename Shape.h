#ifndef ECSHAPE_H
#define ECSHAPE_H

#include "ECGraphicViewImp.h"

class Shape {
public:
	Shape(int x1, int y1, int x2, int y2, int type=0): x1(x1), y1(y1), x2(x2), y2(y2), type(type) {}
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
	int getType() { return type; }
private:
	ECDrawiingContext attributes;
	int x1; // corner 1 x value
	int y1; // corner 1 y value
	int x2; // corner 2 x value
	int y2; // corner 2 y value
	int type; // type of shape --> 0 (rectangle) by default
};

class Rectangle : public Shape {
public:
	Rectangle(int x1, int y1, int x2, int y2, int type=0): Shape(x1, y1, x2, y2, type) {}
	virtual bool isPointInside(int px, int py) const override;
};
class FilledRectangle : public Rectangle {
public:
	FilledRectangle(int x1, int y1, int x2, int y2) : Rectangle(x1, y1, x2, y2, 2) {}
};

class Ellipse : public Shape {
public:
	Ellipse(int x1, int y1, int x2, int y2, int type=1);
	virtual bool isPointInside(int px, int py) const override;
	int getXCenter() const { return xCenter; }
	int getYCenter() const { return yCenter; }
	double getXRadius() const { return xRadius; }
	double getYRadius() const { return yRadius; }
	// when setters are updated: change redius and centers --> consider changing how setters work
private:
	int xCenter;
	int yCenter;
	double xRadius;
	double yRadius;
};

class FilledEllipse : public Ellipse {
public:
	FilledEllipse(int x1, int y1, int x2, int y2): Ellipse(x1, y1, x2, y2, 3) {}
};

#endif
