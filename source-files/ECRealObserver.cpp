#include "../header-files/ECRealObserver.h"

// ECModeObserver
void ECModeObserver :: Update() {
    // using spacebar to switch modes
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_SPACE ||
        view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(0) && ctrl.getMode() == 1 || // switching to edit with buttons
        view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(1) && ctrl.getMode() == 0) { // switching to insert with buttons
        ctrl.changeMode();
        if (ctrl.getMode() == 0) view.defaultCursor();
        if (ctrl.getMode() == 1) view.insertCursor();
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
        menu.timer(ctrl.getMode()); // draw menu buttons
        int x, y;
        view.GetCursorPosition(x, y);
        menu.detectMouse(x, y);
    }
}

// ECDelObserver
void ECDelObserver :: Update() {
    if (ctrl.getMode() == 0 && view.GetCurrEvent() == ECGV_EV_KEY_DOWN_D ||
        view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(4)) {
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
        // timer functionality moved to menu
    }
}

// ECUndoRedoObserver
void ECUndoRedoObserver :: Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Z ||
        view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(2)) {
        ctrl.Undo();
    }
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Y ||
        view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(3)) {
        ctrl.Redo();
    }
    view.SetRedraw(true); // correct drawing for last undo
}

// ECGroupObserver
void ECGroupObserver::Update() {
    // must be in edit mode, then check whether G is pressed or pressing the group button in menu
    if (ctrl.getMode() == 0 && 
        view.GetCurrEvent() == ECGV_EV_KEY_DOWN_G ||
        view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(5)) {
        ctrl.GroupShapes();
        ctrl.removeSelected();
    }
}

void ECTypeInsertObserver::Update() {
    if (ctrl.getMode() == 1) {
        if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_G) {
            ctrl.pressGKey();
        }
        else if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_F) {
            ctrl.pressFKey();
        }
        else if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN) {
            if (menu.checkOverButton(6)) {
                ctrl.setGKey(false);
                ctrl.setFKey(false);
            }
            if (menu.checkOverButton(7)) {
                ctrl.setGKey(true);
                ctrl.setFKey(false);
            }
            if (menu.checkOverButton(8)) {
                ctrl.setGKey(false);
                ctrl.setFKey(true);
            }
            if (menu.checkOverButton(9)) {
                ctrl.setGKey(true);
                ctrl.setFKey(true);
            }
        }
    }
}

// ECCtrlObserver
void ECCtrlObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_CTRL || view.GetCurrEvent() == ECGV_EV_KEY_UP_CTRL) {
        ctrl.pressCtrlKey();
    }
}

void ECColorObserver::Update() {
    if (ctrl.getMode() == 1 && view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN) {
        for (int i = 0; i < 8; i++) {
            if (menu.checkOverButton(i+10)) {
                ctrl.setColor(i);
            }
        }
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
