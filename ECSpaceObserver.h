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
            //// view.DrawRectangle(100, 100, 400, 400);
            //// view.SetRedraw(true);
            //tempController.addShape();
            //cout << "Adding new shape" << endl;
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
            // view.DrawRectangle(100, 100, 400, 400);
            // cout << "Model Length: " << tempController.getTempModel().size() << endl;
            for (auto x : tempController.getListShapes()) {
                // cout << "rectangle" << endl;
                view.DrawRectangle(x->x1, x->y1, x->x2, x->y2);
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
        if (view.GetCurrEvent() == ECGV_EV_KEY_DOWN_D) {
            /*cout << "deleting all shapes" << endl;
            tempController.clearModel();
            view.SetRedraw(true);*/
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
        if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_UP) {
            tempController.incMouseEvents();
        }
        if (view.GetCurrEvent() == ECGV_EV_MOUSE_BUTTON_DOWN) {
            // cout << "mouse placed" << endl;
            tempController.incMouseEvents();
            int x, y;
            view.GetCursorPosition(x, y);
            cout << "Rectangle placed at: " << x << ", " << y << endl;
            tempController.updateX(x);
            tempController.updateY(y);
            
            // redrawing
            // tempController.addShape(x, y, x + 300, y + 300);
            // view.SetRedraw(true);
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
private:
    ECGraphicViewImp& view;
    Controller& tempController;
};

#endif