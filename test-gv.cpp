//
//  Created by Yufeng Wu on 3/2/22.
//
#include "ECGraphicViewImp.h"
#include "ECSpaceObserver.h"
#include "Controller.h"
#include <iostream>
using namespace std;

// Test graphical view code
int real_main(int argc, char **argv)
{
  const int widthWin = 1000, heightWin = 1000;
  ECGraphicViewImp view(widthWin, heightWin);
  ShapesModel * model = new ShapesModel;
  Controller ctrl(model);
  
  // Creating observers
  ECSpaceObserver * test = new ECSpaceObserver(view, ctrl);
  ECDrawObserver* testDraw = new ECDrawObserver(view, ctrl);
  ECDObserver* testDel = new ECDObserver(view, ctrl);
  ECMouseObserver* testMouse = new ECMouseObserver(view, ctrl);

  // Attaching observers
  view.Attach(test);
  view.Attach(testDraw);
  view.Attach(testDel);
  view.Attach(testMouse);

  // Run application
  view.Show();
  
  return 0;
}

int main(int argc, char **argv)
{
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

