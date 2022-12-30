## Graphical Editor

This is a Graphical Editor written in C++ using the game engine Allegro as the basis for the GUI.

### To Compile:
g++ source-files/ECGraphicViewImp.cpp source-files/test-gv.cpp source-files/Command.cpp source-files/ShapesModel.cpp source-files/Shape.cpp source-files/ECRealObserver.cpp source-files/MouseFunction.cpp -lallegro -lallegro_font -lallegro_primitives -lallegro_main -lallegro_image -lallegro_main -o editor\
**Note:** Allegro must be installed.

### To Run:
./editor [filename.dat/.txt]\
The above filename is optional. If included, it will attempt to load from the file. When the editor is closed, it will save to the filename that was provided. If no file is provided, the editor can still be run, but it will be blank upon opening and will not save once closed.

### Edit Mode:
This is the default mode when the editor is opened.\
**To switch modes, press the spacebar.**\
In this mode, the user can select and manipulate shapes.\
**Selecting:** To select a shape, simply click within the shape's area. If there are multiple shapes in the same area, the one added most recently is selected. The selected shape will show up in blue.\
**Deselecting**: To deselect a shape, click outside any shapes.\
**Deleting:** To delete a shape, select it and then press the "D" key.\
**Moving:** To move a shape, select it, and while the mouse is pressed, move the mouse to a different location. Note that when moving a shape, a light blue trace shape follows the user's mouse. It will become a real shape once the user releases the mouse.\
**Multiple Select:** By holding ctrl, multiple shapes can be selected at the same time. As with individual shapes,
clicking outside of any shape will unselect all shapes. All selected shapes will be colored blue.
When multiple (or individual) shapes are selected, any amount of shapes can be moved by
holding the mouse down and dragging the shape to a new location, or using the arrow keys to
move the selected shapes.\
**Grouping:** When multiple shapes are selected, by pressing G, the shapes will become grouped to become a composite shape. Note that recursive grouping is possible (i.e., a composite shape can be a member of another composite shape, etc.)\
**Ungrouping:** If only a single shape is selected, if it is a composite shape, pressing G will ungroup the shape. There
can be multiple levels of composition.

### Insert Mode:
By pressing the mouse down and dragging, a pink rectangle will be drawn onscreen showing the area in which a new shape will be inserted. A shape will be inserted when the user releases the mouse.
There are four types of shapes that can be inserted:
* Unfilled Rectangle
* Filled Rectangle
* Unfilled Ellipse
* Filled Ellipse

The Unfilled Rectangle is the default shape. Pressing the "F" key once allows a filled shape to be pressed, and pressing it again goes back to unfilled mode. Pressing "G" once switches to inserting Ellipses. Pressing "G" again goes back to inserting Rectangles.

### Undo/Redo:
The following actions can be undone/redone using the "Z" key for Undo and the "Y" key for redo:
* Inserting a shape
* Deleting a shape
* Moving a shape
* Grouping shapes
* Ungrouping shapes

Note that whenever a new action is completed (inserting, moving, etc.), all pending Redo operations are cleared. This is common convention for graphical editors using the command pattern.

### File I/O:
By running the executable with a file as the first argument, the editor will attempt to
load from the file, putting all of the shapes in the model and on screen if the file can be parsed.
After the editor is closed, every shape in the model will be saved to the file, and can be loaded
at a later time. The file will be created if it does not exist.

### Future Features:
* Documentation on shape scheme
* Makefile for easier compilation
* Menu onscreen allowing users to change colors of shapes, changes modes, etc.
* Add support for users to add onscreen text
* Allowing users to specify which file to open in the application instead of only via command line
* Detailed documentation on design patterns used
* Detailed description on how to install Allegro

&copy; Tyler Hinrichs 2022