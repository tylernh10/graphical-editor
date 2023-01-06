#include "../header-files/ECRealObserver.h"

// ECSpaceObserver
void ECSpaceObserver :: Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_SPACE) {
        ctrl.changeMode();
        ctrl.setMouseDownThisMode(0);
        ctrl.resetFandGAssertions(); // changes F and G asserted to false when switching modes
        view.SetRedraw(true); // needed for color change of selected becoming unselected
    }
}

//ECDrawObserver
void ECDrawObserver :: Update() {
    if (view.GetCurrEvent() == ECGV_EV_TIMER) {
        for (auto x : ctrl.getListShapes()) {
            x->Draw(view);
            view.SetRedraw(true);
        }
        menu->draw(); // draw menu buttons
        int x, y;
        view.GetCursorPosition(x, y);
        //cout << "(" << x << "," << y << ")" << endl;
        menu->detectMouse(x, y);
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

// ECGObserver
void ECGObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_G && ctrl.getMode() == 1) {
        ctrl.pressGKey();
    }
    else if (view.GetCurrEvent() == ECGV_EV_KEY_UP_G && ctrl.getMode() == 0) {
        ctrl.pressGKeyEditMode();
    }
}

// ECFObserver
void ECFObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_F) {
        ctrl.pressFKey();
    }
}

// ECCtrlObserver
void ECCtrlObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_CTRL || view.GetCurrEvent() == ECGV_EV_KEY_UP_CTRL) {
        ctrl.pressCtrlKey();
    }
}

// ECUpArrowObserver
void ECUpArrowObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_UP) {
        ctrl.pressUpArrow();
    }
}

// ECDownArrowObserver
void ECDownArrowObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_DOWN) {
        ctrl.pressDownArrow();
    }
}

// ECLeftArrowObserver
void ECLeftArrowObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_LEFT) {
        ctrl.pressLeftArrow();
    }
}

// ECRightArrowObserver
void ECRightArrowObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_RIGHT) {
        ctrl.pressRightArrow();
    }
}
