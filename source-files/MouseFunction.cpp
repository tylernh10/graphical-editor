#include "../header-files/MouseFunction.h"

// ECAbstractMouseFunction
void ECAbstractMouseFunction::saveCursorPosition()  {
    int x, y;
    view.GetCursorPosition(x, y);
    // saving position where clicked
    ctrl.updateX(x);
    ctrl.updateY(y);
}

// EditModeMouseFunction
void EditModeMouseFunction::mouseDown() {
    if (!ctrl.getMouseDown()) {
        ctrl.setMouseDown();
        ctrl.setMouseDownThisMode(1);
        saveCursorPosition();
        ctrl.select(ctrl.getX(), ctrl.getY());
        view.SetRedraw(true);
    }
}
void EditModeMouseFunction::mouseUp() {
    ctrl.setMouseUp();
    int curX, curY;
    view.GetCursorPosition(curX, curY);
    int translateX = curX - ctrl.getX();
    int translateY = curY - ctrl.getY();
    if (fabs(translateX) > 0 || fabs(translateY) > 0) {
        ctrl.moveShape(translateX, translateY);
    }
    view.SetRedraw(true);
}
void EditModeMouseFunction::timer() {
    // if the mouse is down: show all selected items in a cyan color as they move
    if (ctrl.getMouseDown()) {
        int curX, curY;
        view.GetCursorPosition(curX, curY);
        int translateX = curX - ctrl.getX();
        int translateY = curY - ctrl.getY();
        vector <Shape*> s = ctrl.getSelected();
        if (!s.empty()) {
            mouseDownDrawWhileMoving(translateX, translateY, s);
        }
        view.SetRedraw(true);
    }
}

void EditModeMouseFunction::mouseDownDrawWhileMoving(int translateX, int translateY, vector<Shape*> s) {
    for (auto i : s) {
        if (i->getType() == 0 || i->getType() == 2) {
            view.DrawRectangle(i->getX1() + translateX, i->getY1() + translateY, i->getX2() + translateX, i->getY2() + translateY, 3, ECGV_CYAN);
        }
        else if (i->getType() == 1 || i->getType() == 3) {
            Ellipse* e = dynamic_cast<Ellipse*>(i);
            view.DrawEllipse(e->getXCenter() + translateX, e->getYCenter() + translateY, e->getXRadius(), e->getYRadius(), 3, ECGV_CYAN);
        }
        else {
            CompositeShape* c = dynamic_cast<CompositeShape*>(i);
            mouseDownDrawWhileMoving(translateX, translateY, c->getShapes()); // if composite shape, recursively call this function on its children
        }
    }
}

// InsertModeMouseFunction
void InsertModeMouseFunction::mouseDown() {
    if (!ctrl.getMouseDown()) {
        ctrl.setMouseDown();
        ctrl.setMouseDownThisMode(1);
        saveCursorPosition();
    }
}
void InsertModeMouseFunction::mouseUp() {
    ctrl.setMouseUp();
    // insert with controller
    if (ctrl.getMouseDownThisMode()) {
        int curX, curY;
        view.GetCursorPosition(curX, curY);
        // check for mode and insert ellipse when necessary
        if (!ctrl.isGAsserted() && !ctrl.isFAsserted()) ctrl.insertRectangle(curX, curY);
        else if (!ctrl.isGAsserted() && ctrl.isFAsserted()) ctrl.insertFilledRectangle(curX, curY);
        else if (ctrl.isGAsserted() && !ctrl.isFAsserted()) ctrl.insertEllipse(curX, curY);
        else if (ctrl.isGAsserted() && ctrl.isFAsserted()) ctrl.insertFilledEllipse(curX, curY);
        view.SetRedraw(true);
    }
}
void InsertModeMouseFunction::timer() {
    if (ctrl.getMouseDown() && ctrl.getMouseDownThisMode()) {
        int curX, curY;
        view.GetCursorPosition(curX, curY);
        // stays the same for now if we are keeping a rectangle
        view.DrawRectangle(ctrl.getX(), ctrl.getY(), curX, curY, 3, ECGV_PURPLE);
        view.SetRedraw(true);
    }
}
