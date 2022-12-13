#ifndef ECSHAPE_H
#define ECSHAPE_H

#include "ECGraphicViewImp.h"
#include <vector>
using namespace std;

class ECGraphicViewImp;

class Shape {
public:
	Shape(int x1, int y1, int x2, int y2, ECGVColor color = ECGV_BLACK, int type=0): x1(x1), y1(y1), x2(x2), y2(y2), color(color), type(type) {
		attributes.SetColor(color);
	}
	~Shape() {}
	ECDrawiingContext getAttributes() const { return attributes; }
	int getX1() const { return x1; }
	int getY1() const { return y1; }
	int getX2() const { return x2; }
	int getY2() const { return y2; }
	virtual void setNewPosition(int translateX, int translateY);
	virtual bool isPointInside(int px, int py) const = 0;
	virtual void Draw(ECGraphicViewImp& view) const = 0;
	virtual void selectedColorChange() { attributes.SetColor(ECGV_BLUE); }
	virtual void unselectedColorChange() { attributes.SetColor(color); }
	int getType() { return type; }
private:
	ECDrawiingContext attributes;
	int x1; // corner 1 x value
	int y1; // corner 1 y value
	int x2; // corner 2 x value
	int y2; // corner 2 y value
	ECGVColor color; // holds color
	int type; // type of shape --> 0 (rectangle) by default
};

class Rectangle : public Shape {
public:
	Rectangle(int x1, int y1, int x2, int y2, ECGVColor color = ECGV_BLACK, int type=0): Shape(x1, y1, x2, y2, color, 0) {}
	virtual bool isPointInside(int px, int py) const override;
	virtual void Draw(ECGraphicViewImp& view) const override;
};
class FilledRectangle : public Rectangle {
public:
	FilledRectangle(int x1, int y1, int x2, int y2, ECGVColor color = ECGV_BLACK) : Rectangle(x1, y1, x2, y2, color, 2) {}
	virtual void Draw(ECGraphicViewImp& view) const override;
};

class Ellipse : public Shape {
public:
	Ellipse(int x1, int y1, int x2, int y2, ECGVColor color = ECGV_BLACK, int type=1);
	virtual bool isPointInside(int px, int py) const override;
	virtual void Draw(ECGraphicViewImp& view) const override;
	int getXCenter() const { return xCenter; }
	int getYCenter() const { return yCenter; }
	double getXRadius() const { return xRadius; }
	double getYRadius() const { return yRadius; }
	virtual void setNewPosition(int translateX, int translateY) override;
private:
	int xCenter;
	int yCenter;
	double xRadius;
	double yRadius;
};

class FilledEllipse : public Ellipse {
public:
	FilledEllipse(int x1, int y1, int x2, int y2, ECGVColor color = ECGV_BLACK): Ellipse(x1, y1, x2, y2, color, 3) {}
	virtual void Draw(ECGraphicViewImp& view) const override;
};

class CompositeShape : public Shape {
public:
	CompositeShape(vector<Shape *> s): Shape(0, 0, 0, 0, ECGV_BLACK, 4), s(s) {}
	vector<Shape*> getShapes() const { return s; }
	virtual bool isPointInside(int px, int py) const;
	virtual void Draw(ECGraphicViewImp& view) const override;
	void setNewPosition(int tranlateX, int translateY) override;
	void selectedColorChange() override;
	void unselectedColorChange() override;
private:
	vector<Shape*> s;
};

#endif
