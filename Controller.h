#ifndef ECCONTROLLER_H
#define ECCONTROLLER_H

#include "Shape.h"
#include <vector>
using namespace std;

class ShapesModel {
public:
	ShapesModel() {}
	vector<Shape*> getListShapes() { return listShapes; }
	void addShape(Shape* x) { listShapes.push_back(x); }
	void removeShape(Shape* x) { /** TODO */ }
private:
	vector<Shape*> listShapes;
	//int mouseDownX; // saves x position of mouse down event
	//int mouseDownY; // saves y position of mouse down event
	//int mouseEvents; // keeps track of how many mouse up and mouse down events have occurred
};

class Controller {
public:
	Controller(ShapesModel * model): model(model) {}
	vector<Shape*> getListShapes() { return model->getListShapes(); }
	void updateX(int x) { mouseDownX = x; }
	void updateY(int y) { mouseDownY = y; }
	int getX() { return mouseDownX; }
	int getY() { return mouseDownY; }
	void incMouseEvents() { mouseEvents++; }
	int getMouseEvents() { return mouseEvents; }

	void insertRectangle(int x2, int y2) {
		Shape* x = new Shape(mouseDownX, mouseDownY, x2, y2);
		model->addShape(x);
	}
	/*vector<Shape *> getTempModel() { return TempShapeModel; }
	void addShape() {
		Shape* x = new Shape();
		TempShapeModel.push_back(x);
	}
	void addShape(int x1, int y1, int x2, int y2) {
		Shape* x = new Shape(x1, y1, x2, y2);
		TempShapeModel.push_back(x);
	}
	void clearModel() {
		for (auto x : TempShapeModel) {
			delete x;
		}
		TempShapeModel.clear();
	}*/

private:
	ShapesModel* model;
	int mouseDownX;
	int mouseDownY;
	int mouseEvents;
};

#endif // !
