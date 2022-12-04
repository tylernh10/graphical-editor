#include "ShapesModel.h"


// Controller
Controller :: Controller(ShapesModel* model) : model(model), mode(0), gIsAsserted(false) {
	history = new ECCommandHistory;
}

void Controller :: insertRectangle(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model);
	history->ExecuteCmd(c);
	cout << "rectangle inserted" << endl;
}

void Controller::insertEllipse(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model, 1);
	history->ExecuteCmd(c);
	cout << "ellipse inserted" << endl;
}

void Controller::insertFilledRectangle(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model, 2);
	history->ExecuteCmd(c);
	cout << "filled rectangle inserted" << endl;
}

void Controller::insertFilledEllipse(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model, 3);
	history->ExecuteCmd(c);
	cout << "filled ellipse inserted" << endl;
}

void Controller::deleteShape() {
	Shape* s = model->getSelected();
	if (s != NULL) {
		DeleteShape* d = new DeleteShape(s, model);
		history->ExecuteCmd(d);
		cout << "shape deleted" << endl;
	}
	model->removeSelected();
}

void Controller::moveShape(int translateX, int translateY) {
	Shape* s = model->getSelected();
	if (s != NULL) {
		MoveShape* m = new MoveShape(translateX, translateY, s, model);
		history->ExecuteCmd(m);
		cout << "shape moved" << endl;
	}
}

void Controller::changeMode() {
	mode = !mode; // 0 is edit mode, 1 is insertion mode
	if (mode) model->removeSelected(); // removed when changing back to insertion mode
}

void Controller::Undo() {
	model->removeSelected();
	history->Undo();
}

void Controller::Redo() {
	model->removeSelected();
	history->Redo();
}

// ShapesModel
void ShapesModel::removeShape(Shape* x) {
	for (auto i = listShapes.begin(); i != listShapes.end(); i++) {
		if (x == *i) {
			listShapes.erase(i);
			break;
		}
	}
}

void ShapesModel::moveShape(int x1, int y1, int x2, int y2, Shape* x) {
	for (auto i = listShapes.begin(); i != listShapes.end(); i++) {
		if (x == *i) {
			(*i)->setX1(x1);
			(*i)->setY1(y1);
			(*i)->setX2(x2);
			(*i)->setY2(y2);
			break;
		}
	}
}

void ShapesModel::select(int px, int py) {
	if (selected != NULL) {
		selected->unselectedColorChange();
		selected = NULL;
	}
	for (auto i = listShapes.rbegin(); i != listShapes.rend(); i++) {
		if ((*i)->isPointInside(px, py)) {
			cout << "selected inside a rectangle" << endl;
			selected = *i;
			(*i)->selectedColorChange();
			return;
		}
	}
	cout << "selected outside of any shape" << endl;
}

Shape* ShapesModel::getSelected() {
	return selected;
}

void ShapesModel::removeSelected() {
	if (selected != NULL) {
		selected->unselectedColorChange();
		selected = NULL;
	}
}
