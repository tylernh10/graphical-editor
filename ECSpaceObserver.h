#ifndef ECOBSERVERSPACE_H
#define ECOBSERVERSPACE_H

#include "ECObserver.h"
#include "ECGraphicViewImp.h"
#include "Controller.h"

#include <iostream>
using namespace std;

// test observer to see if can attach to spacebar click
class ECSpaceObserver : public ECObserver
{
public:
    ECSpaceObserver(ECGraphicViewImp& view, Controller& tempController) : view(view), tempController(tempController) {}
    virtual ~ECSpaceObserver() {}
    virtual void Update() {
        if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_SPACE) {
            tempController.changeMode();
            tempController.resetMouseEvents();
            view.SetRedraw(true); // needed for color change of selected becoming unselected
        }
    }
private:
    ECGraphicViewImp& view;
    Controller& tempController;
};

class ECDrawObserver : public ECObserver
{
public:
    ECDrawObserver(ECGraphicViewImp& view, Controller& tempController): view(view), tempController(tempController) {}
    virtual ~ECDrawObserver() {}
    virtual void Update() {
        if (view.GetCurrEvent() == ECGV_EV_TIMER) {
            for (auto x : tempController.getListShapes()) {
                //cout << x->getAttributes().GetColor() << endl;
                view.DrawRectangle(x->getX1(), x->getY1(), x->getX2(), x->getY2(), 3, x->getAttributes().GetColor());
                view.SetRedraw(true);
            }
        }
    }
private:
    ECGraphicViewImp& view;
    Controller& tempController;
};

class ECDObserver : public ECObserver
{
public:
    ECDObserver(ECGraphicViewImp& view, Controller& tempController) : view(view), tempController(tempController) {}
    virtual ~ECDObserver() {}
    virtual void Update() {
        if (tempController.getMode() == 1 && view.GetCurrEvent() == ECGV_EV_KEY_DOWN_D) {
            /*cout << "deleting all shapes" << endl;
            tempController.clearModel();
            view.SetRedraw(true);*/
            tempController.deleteShape(); // deletes selected shape if in edit mode
            view.SetRedraw(true);
        }
    }
private:
    ECGraphicViewImp& view;
    Controller& tempController;
};

class ECMouseObserver : public ECObserver
{
public:
    ECMouseObserver(ECGraphicViewImp& view, Controller& tempController) : view(view), tempController(tempController) {}
    virtual ~ECMouseObserver() {}
    virtual void Update() {
        // insertion mode
        if (tempController.getMode() == 0) {
            if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_UP) {
                tempController.incMouseEvents();
            }
            if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN) {
                tempController.incMouseEvents();
                int x, y;
                view.GetCursorPosition(x, y);
                cout << "Rectangle placed at: " << x << ", " << y << endl;
                
                // saving position where clicked
                tempController.updateX(x);
                tempController.updateY(y);
            }
            if (view.GetCurrEvent() == ECGV_EV_TIMER && tempController.getMouseEvents() % 2 == 1) {
                int curX, curY;
                view.GetCursorPosition(curX, curY);
                view.DrawRectangle(tempController.getX(), tempController.getY(), curX, curY, 3, ECGV_PURPLE);
                view.SetRedraw(true);
            }
            if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_UP && tempController.getMouseEvents() % 2 == 0) {
                // insert with controller
                int curX, curY;
                view.GetCursorPosition(curX, curY);
                tempController.insertRectangle(curX, curY);
                view.SetRedraw(true);
            }
        }
        // edit mode
        else {
            if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_UP) {
                tempController.incMouseEvents();
            }
            if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN) {
                tempController.incMouseEvents();
                int x, y;
                view.GetCursorPosition(x, y);

                // saving position where clicked
                tempController.updateX(x);
                tempController.updateY(y);

                tempController.select(x, y);
                view.SetRedraw(true);
            }
            if (view.GetCurrEvent() == ECGV_EV_TIMER && tempController.getMouseEvents() % 2 == 1) {
                // draw with dimensions of selected at the position of the cursor
                int curX, curY;
                view.GetCursorPosition(curX, curY);
                int translateX = curX - tempController.getX();
                int translateY = curY - tempController.getY();
                Shape* s = tempController.getSelected();
                if (s != NULL) {
                    view.DrawRectangle(s->getX1() + translateX, s->getY1() + translateY, s->getX2() + translateX, s->getY2() + translateY, 3, ECGV_CYAN);
                }
                view.SetRedraw(true);
            }
            if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_UP) {
                int curX, curY;
                view.GetCursorPosition(curX, curY);
                int translateX = curX - tempController.getX();
                int translateY = curY - tempController.getY();
                tempController.moveShape(translateX, translateY);
                view.SetRedraw(true);
            }
        }
    }
private:
    ECGraphicViewImp& view;
    Controller& tempController;
};

class ECUndoRedoObserver : public ECObserver
{
public:
    ECUndoRedoObserver(ECGraphicViewImp& view, Controller& tempController) : view(view), tempController(tempController) {}
    virtual ~ECUndoRedoObserver() {}
    virtual void Update() {
        if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Z) {
            tempController.Undo();
        }
        if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_Y) {
            tempController.Redo();
        }
        view.SetRedraw(true); // needed for last undo
    }
private:
    ECGraphicViewImp& view;
    Controller& tempController;
};

#endif
