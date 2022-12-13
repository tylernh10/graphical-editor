#include "Shape.h"
#include <cmath>
#include <fstream>
using namespace std;

// shape
void Shape::setNewPosition(int translateX, int translateY) {
	x1 += translateX;
	y1 += translateY;
	x2 += translateX;
	y2 += translateY;
}

// rectangle
bool Rectangle::isPointInside(int px, int py) const {
	int xl = max(getX1(), getX2());
	int xs = min(getX1(), getX2());
	int yl = max(getY1(), getY2());
	int ys = min(getY1(), getY2());

	return px >= xs && px <= xl && py >= ys && py <= yl;
}

void Rectangle::Draw(ECGraphicViewImp& view) const {
	view.DrawRectangle(getX1(), getY1(), getX2(), getY2(), 3, getAttributes().GetColor());
}

// ellipse
Ellipse::Ellipse(int x1, int y1, int x2, int y2, ECGVColor color, int type): Shape(x1, y1, x2, y2, color, 1) {
	xCenter = (x1 + x2) / 2;
	yCenter = (y1 + y2) / 2;
	xRadius = (double)fabs(x1 - x2) / 2.0;
	yRadius = (double)fabs(y2 - y1) / 2.0;
}

bool Ellipse::isPointInside(int px, int py) const {
	double x = (double)px;
	double y = (double)py;
	return (pow(x - xCenter, 2) / (xRadius * xRadius) + pow(y - yCenter, 2) / (yRadius * yRadius)) <= 1;
}

void Ellipse::Draw(ECGraphicViewImp& view) const {
	view.DrawEllipse(getXCenter(), getYCenter(), getXRadius(), getYRadius(), 3, getAttributes().GetColor());
}

void Ellipse::setNewPosition(int translateX, int translateY) {
	Shape::setNewPosition(translateX, translateY);
	xCenter = (getX1() + getX2()) / 2;
	yCenter = (getY1() + getY2()) / 2;
}

// filled rectangle
void FilledRectangle::Draw(ECGraphicViewImp& view) const {
	view.DrawFilledRectangle(getX1(), getY1(), getX2(), getY2(), getAttributes().GetColor());
}

// filled ellipse
void FilledEllipse::Draw(ECGraphicViewImp& view) const {
	view.DrawFilledEllipse(getXCenter(), getYCenter(), getXRadius(), getYRadius(), getAttributes().GetColor());
}

// composite shape
bool CompositeShape::isPointInside(int px, int py) const {
	for (auto i : s) {
		if (i->isPointInside(px, py)) {
			return true;
		}
	}
	return false;
}

void CompositeShape::setNewPosition(int translateX, int translateY) {
	for (auto i : s) {
		i->setNewPosition(translateX, translateY);
	}
}

void CompositeShape::selectedColorChange() {
	for (auto i : s) {
		i->selectedColorChange();
	}
}

void CompositeShape::unselectedColorChange() {
	for (auto i : s) {
		i->unselectedColorChange();
	}
}

void CompositeShape::Draw(ECGraphicViewImp& view) const {
	for (auto i : s) {
		i->Draw(view);
	}
}

// writing to file
void Rectangle::writeShape(ofstream& f) const {
	f << 0 << " ";
	f << 4 << " ";
	f << getX1() << " " << getY1() << " ";
	f << getX1() << " " << getY2() << " ";
	f << getX2() << " " << getY2() << " ";
	f << getX2() << " " << getY1() << " ";
	f << getColor() << endl;
}

void FilledRectangle::writeShape(ofstream& f) const {
	f << 2 << " ";
	f << 4 << " ";
	f << getX1() << " " << getY1() << " ";
	f << getX1() << " " << getY2() << " ";
	f << getX2() << " " << getY2() << " ";
	f << getX2() << " " << getY1() << " ";
	f << getColor() << endl;
}

void Ellipse::writeShape(ofstream& f) const {
	f << 1 << " ";
	f << xCenter << " ";
	f << yCenter << " ";
	f << (int)xRadius << " ";
	f << (int)yRadius << " ";
	f << getColor() << endl;
}

void FilledEllipse::writeShape(ofstream& f) const {
	f << 3 << " ";
	f << xCenter << " ";
	f << yCenter << " ";
	f << (int)xRadius << " ";
	f << (int)yRadius << " ";
	f << getColor() << endl;
}
 
void CompositeShape::writeShape(ofstream& f) const {
	f << "4 " << getShapes().size() << endl;
	for (auto i: getShapes()) {
		i->writeShape(f);
	}
}
