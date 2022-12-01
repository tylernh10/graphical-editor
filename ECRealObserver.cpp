#include "ECRealObserver.h"

// ECSpaceObserver
void ECSpaceObserver :: Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_SPACE) {
        ctrl.changeMode();
        //ctrl.setMouseUp();
        ctrl.setMouseDownThisMode(0);
        view.SetRedraw(true); // needed for color change of selected becoming unselected
    }
}

//ECDrawObserver
void ECDrawObserver :: Update() {
    if (view.GetCurrEvent() == ECGV_EV_TIMER) {
        for (auto x : ctrl.getListShapes()) {
            view.DrawRectangle(x->getX1(), x->getY1(), x->getX2(), x->getY2(), 3, x->getAttributes().GetColor());
            view.SetRedraw(true);
        }
    }
}

// ECDObserver
void ECDObserver :: Update() {
    if (ctrl.getMode() == 0 && view.GetCurrEvent() == ECGV_EV_KEY_DOWN_D) {
        ctrl.deleteShape(); // deletes selected shape if in edit mode
        view.SetRedraw(true);
    }
}

// ECMouseObserver
void ECMouseObserver::Update() {
    if (ctrl.getMode() == observerModeType) {
        if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_UP) {
            mouseFunction.mouseUp();
        }
        if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN) {
            mouseFunction.mouseDown();
        }
        if (view.GetCurrEvent() == ECGV_EV_TIMER) {
            mouseFunction.timer();
        }
    }
}

// ECUndoRedoObserver
void ECUndoRedoObserver :: Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Z) {
        ctrl.Undo();
    }
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Y) {
        ctrl.Redo();
    }
    view.SetRedraw(true); // correct drawing for last undo
}

