#include "Shape.h"
#include <cmath>
using namespace std;

// rectangle
bool Rectangle::isPointInside(int px, int py) const {
	int xl = max(getX1(), getX2());
	int xs = min(getX1(), getX2());
	int yl = max(getY1(), getY2());
	int ys = min(getY1(), getY2());

	return px >= xs && px <= xl && py >= ys && py <= yl;
}

Ellipse::Ellipse(int x1, int y1, int x2, int y2, int type): Shape(x1, y1, x2, y2, type) {
	xCenter = (x1 + x2) / 2;
	yCenter = (y1 + y2) / 2;
	xRadius = (double)fabs(x1 - x2) / 2.0;
	yRadius = (double)fabs(y2 - y1) / 2.0;
}

bool Ellipse::isPointInside(int px, int py) const {
	return true;
}
