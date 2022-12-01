#include "MouseFunction.h"

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
    if (ctrl.getMouseDown()) {
        int curX, curY;
        view.GetCursorPosition(curX, curY);
        int translateX = curX - ctrl.getX();
        int translateY = curY - ctrl.getY();
        Shape* s = ctrl.getSelected();
        if (s != NULL) {
            view.DrawRectangle(s->getX1() + translateX, s->getY1() + translateY, s->getX2() + translateX, s->getY2() + translateY, 3, ECGV_CYAN);
        }
        view.SetRedraw(true);
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
        ctrl.insertRectangle(curX, curY);
        view.SetRedraw(true);
    }
}
void InsertModeMouseFunction::timer() {
    if (ctrl.getMouseDown() && ctrl.getMouseDownThisMode()) {
        int curX, curY;
        view.GetCursorPosition(curX, curY);
        view.DrawRectangle(ctrl.getX(), ctrl.getY(), curX, curY, 3, ECGV_PURPLE);
        view.SetRedraw(true);
    }
}
