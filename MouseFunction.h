#ifndef ECMOUSEFUNCTION_H
#define ECMOUSEFUNCTION_H

#include "ECRealObserver.h"

class ECGraphicViewImp;
class Controller;

// Defines functionality of the mouse based on the mode the editor is in
class ECAbstractMouseFunction {
public: 
	ECAbstractMouseFunction(ECGraphicViewImp& view, Controller& ctrl): view(view), ctrl(ctrl) {}
	virtual ~ECAbstractMouseFunction() {}
	virtual void mouseDown() = 0;
	virtual void mouseUp() = 0;
	virtual void timer() = 0;
	void saveCursorPosition();
protected:
	ECGraphicViewImp& view;
	Controller& ctrl;
};

// Functionality of mouse when in edit mode
class EditModeMouseFunction : public ECAbstractMouseFunction {
public:
	EditModeMouseFunction(ECGraphicViewImp& view, Controller& ctrl) : ECAbstractMouseFunction(view, ctrl) {}
	virtual ~EditModeMouseFunction() {}
	virtual void mouseDown();
	virtual void mouseUp();
	virtual void timer();
};

// Functionality of mouse when in insert mode
class InsertModeMouseFunction : public ECAbstractMouseFunction {
public:
	InsertModeMouseFunction(ECGraphicViewImp& view, Controller& ctrl) : ECAbstractMouseFunction(view, ctrl) {}
	virtual ~InsertModeMouseFunction() {}
	virtual void mouseDown();
	virtual void mouseUp();
	virtual void timer();
};



#endif
