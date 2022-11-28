#include "Shape.h"
#include <cmath>
using namespace std;

bool Rectangle::isPointInside(int px, int py) const {
	int xl = max(getX1(), getX2());
	int xs = min(getX1(), getX2());
	int yl = max(getY1(), getY2());
	int ys = min(getY1(), getY2());

	return px >= xs && px <= xl && py >= ys && py <= yl;
}