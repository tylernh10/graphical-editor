#include "Controller.h"


// controller
Controller :: Controller(ShapesModel* model) : model(model) {
	history = new ECCommandHistory;
}

void Controller :: insertRectangle(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model);
	history->ExecuteCmd(c);
}

void Controller::deleteShape() {
	Shape* s = model->getSelected();
	if (s != NULL) {
		DeleteShape* d = new DeleteShape(s, model);
		history->ExecuteCmd(d);
		//cout << "successful delete" << endl;
	}
	//else cout << "nothing is selected";
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
	mode = !mode;
	if (mode) cout << "mode changed to edit" << endl;
	else {
		model->removeSelected(); // removed when changing back to insertion mode
		cout << "mode changed to insert" << endl;
	}
}

void Controller::Undo() {
	model->removeSelected();
	history->Undo();
}

void Controller::Redo() {
	model->removeSelected();
	history->Redo();
}

// model
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
	cout << "selecting in model" << endl;
	if (selected != NULL) {
		selected->unselectedColorChange();
		selected = NULL;
	}
	for (auto i = listShapes.rbegin(); i != listShapes.rend(); i++) {
		if ((*i)->isPointInside(px, py)) {
			cout << "point is inside a rectangle" << endl;
			selected = *i;
			(*i)->selectedColorChange();
			return;
		}
	}
	cout << selected << endl;
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
