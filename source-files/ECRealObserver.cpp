#include "../header-files/ECRealObserver.h"
#include <allegro5/allegro_native_dialog.h>

// ECModeObserver
void ECModeObserver :: Update() {
    // using spacebar to switch modes
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_SPACE ||
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(0) && ctrl.getMode() == 1) || // switching to edit with buttons
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(1) && ctrl.getMode() == 0)) { // switching to insert with buttons
        ctrl.changeMode();
        if (ctrl.getMode() == 0) view.defaultCursor();
        if (ctrl.getMode() == 1) view.insertCursor();
        ctrl.setMouseDownThisMode(0);
        //ctrl.resetFandGAssertions(); // changes F and G asserted to false when switching modes
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
    if ((ctrl.getMode() == 0 && view.GetCurrEvent() == ECGV_EV_KEY_DOWN_D) ||
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(4))) {
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
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(2))) {
        ctrl.Undo();
    }
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Y ||
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(3))) {
        ctrl.Redo();
    }
    view.SetRedraw(true); // correct drawing for last undo
}

// ECGroupObserver
void ECGroupObserver::Update() {
    // must be in edit mode, then check whether G is pressed or pressing the group button in menu
    if (ctrl.getMode() == 0 && 
        (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_G) ||
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(5))) {
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

void ECSaveObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_S ||
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(18))) {
        ctrl.save();
    }
}

void ECHelpObserver::Update() {
    if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_H ||
        (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN && menu.checkOverButton(19))) {
        al_show_native_message_box(view.getDisplay(), "Help", "Graphical Editor Help Information", 
            "Use the mouse to draw, select, and move shapes.\n"
            "Hover over a button in the menu at the top of the screen to see what it does.\n\n"
            "The keyboard can also be used for menu operations.\n"
            "Press the spacebar to switch modes (edit and insert).\n"
            "Press S to save.\n"
            "Press H to open the Help Dialog (this message).\n"
            "Press Z to undo an action.\n"
            "Press Y to redo an action.\n\n"
            "Insert Mode Only:\n"
            "Press F to toggle filled and unfilled shapes.\n"
            "Press G to toggle inserting a rectangle and ellipse.\n\n"
            "Edit Mode Only:\n"
            "Press D to delete a shape.\n"
            "Press G to group multiple shapes or ungroup a singular grouped shape.\n"
            "Hold down CTRL to select and move multiple shapes.\n"
            "Use arrow keys to move shapes (can also use mouse to move).\n\n"
            "For more information, please visit github.com/tylernh10/graphical-editor or refer to the README.md for this repository.\n\n"
            "Thanks for checking out this project! :)"
            ,
            NULL, ALLEGRO_MESSAGEBOX_QUESTION);
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
