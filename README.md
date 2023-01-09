## Graphical Editor

This is a Graphical Editor written in C++ using the game engine Allegro as the basis for the GUI.

### To Compile:
g++ source-files/ECGraphicViewImp.cpp source-files/test-gv.cpp source-files/Command.cpp source-files/ShapesModel.cpp source-files/Shape.cpp source-files/ECRealObserver.cpp source-files/MouseFunction.cpp source-file/Menu.cpp -lallegro -lallegro_font -lallegro_primitives -lallegro_main -lallegro_image -lallegro_main -lallegro_dialog -lallegro_ttf -o editor

**Note:** Allegro must be installed. If you are on Mac or Linux, Allegro can be installed directly. If you are on Windows, you can run Allegro5 applications through visual studio. Please refer to [this video](https://www.youtube.com/watch?v=UgGKBW_kU20) for instructions.

### To Run:
./editor [\<filename\>.dat/.txt]\
The above filename is optional. If included, it will attempt to load from the file. When the editor is closed, it will save to the filename that was provided. If no file is provided, the editor can still be run, but it will be blank upon opening and will not save once closed.

### Edit Mode:
This is the default mode when the editor is opened.\
**To switch modes, press the spacebar or click on the respective mode button in the menu.**\
In this mode, the user can select and manipulate shapes.\
**Selecting:** To select a shape, simply click within the shape's area. If there are multiple shapes in the same area, the one added most recently is selected. The selected shape will show up in blue.\
**Deselecting**: To deselect a shape, click outside any shapes.\
**Deleting:** To delete a shape, select it and then press the "D" key or press the delete button in the menu.\
**Moving:** To move a shape, select it, and while the mouse is pressed, move the mouse to a different location. Note that when moving a shape, a light blue trace shape follows the user's mouse. It will become a real shape once the user releases the mouse.\
**Multiple Select:** By holding ctrl, multiple shapes can be selected at the same time. As with individual shapes,
clicking outside of any shape will unselect all shapes. All selected shapes will be colored blue.
When multiple (or individual) shapes are selected, any amount of shapes can be moved by
holding the mouse down and dragging the shape to a new location, or using the arrow keys to
move the selected shapes.\
**Grouping:** When multiple shapes are selected, by pressing G or by pressing the group button in the menu, the shapes will become grouped to become a composite shape. Note that recursive grouping is possible (i.e., a composite shape can be a member of another composite shape, etc.)\
**Ungrouping:** If only a single shape is selected, if it is a composite shape, pressing G or pressing the group button in menu will ungroup the shape. There
can be multiple levels of composition.

### Insert Mode:
By pressing the mouse down and dragging, a pink rectangle will be drawn onscreen showing the area in which a new shape will be inserted. A shape will be inserted when the user releases the mouse.
There are four types of shapes that can be inserted:
* Unfilled Rectangle
* Filled Rectangle
* Unfilled Ellipse
* Filled Ellipse

The Unfilled Rectangle is the default shape. Pressing the "F" key once allows a filled shape to be pressed, and pressing it again goes back to unfilled mode. Pressing "G" once switches to inserting Ellipses. Pressing "G" again goes back to inserting Rectangles. Also, by pressing the corresponding shape buttons in menu, the insert shape will be changed.

The color of the insert shape can be changed by clicking the color buttons in the menu.

### Undo/Redo:
The following actions can be undone/redone using the "Z" key for Undo and the "Y" key for redo or the corresponding undo and redo buttons in the menu:
* Inserting a shape
* Deleting a shape
* Moving a shape
* Grouping shapes
* Ungrouping shapes

Note that whenever a new action is completed (inserting, moving, etc.), all pending Redo operations are cleared. This is common convention for graphical editors using the command pattern.

### File I/O:
The editor can be used to save and load graphical images. The editor uses a file scheme that saves all information about the shapes of a graphical image into a text file in the format of .txt or .dat.

The file scheme is as follows:
* The first line of every document is the number of shapes.
* Every line that follows gives information on an individual shape.
* The first number in each line specifies the type of shape.
    * 0 - Unfilled Rectangle
    * 1 - Unfilled Ellipse
    * 2 - Filled Rectangle
    * 3 - Filled Ellipse
    * 4 - Composite Shape
* Rectangles (both unfilled and filled): the second number is the number of sides and the next eight numbers after that are (x, y) coordinate pairs of the corners of the shape.
* Ellipses (both unfilled and filled): the following two numbers are the (x, y) coordinates of the center point, with the next two following numbers are the x radius and y radius of the ellipse.
* Composite shape: this is what a shape is called if it has been grouped. There are only two numbers on this line, the first specifying that the shape is composite, and the next number *n* being the number of shapes in the composite shape. **Note: within the *n* shapes contained within each composite shape there can be nested composite shapes.**
* The last number of every shape (every atomic shape, so excluding composite shapes) specifies the color of the shape.

By running the executable with a file name as the first argument, the editor will attempt to load from the file, putting all of the shapes in the model and on screen if the file can be parsed. If the file does not exist in the specified directory, an empty file will be created with the given name. The editor will appear blank apart from the menu.
 
After the editor is closed, every shape in the model will be saved to the file, and can be loaded at a later time.

### Other Important Features
Users can save to the document they specified on the command line by pressing the S key or by clicking the save button in the menu.

Users can get help information in-application by pressing the H key or by clicking the help button in the menu.

### Future Features:
* ~~Documentation on shape scheme~~ *(Complete)*
* ~~Menu onscreen allowing users to change colors of shapes, changes modes, etc.~~ *(Complete)*
* Makefile for easier compilation
* Add support for users to add onscreen text
* Allowing users to specify which file to open in the application instead of only via command line
* Detailed documentation on design patterns used
* Detailed description on how to install Allegro

### Copyright Info

This project was developed as an extension of the final project for CSE 3150 at UConn in the Fall 2022 semester taught by [Dr. Yufeng Wu](https://yufeng-wu.uconn.edu/).

Prof. Wu developed some of the starter code for this project, as well as the general guidelines (including the shape scheme). Please refer to the [first commit](https://github.com/tylernh10/graphical-editor/commit/a6a3f97ce2edbd855a279af5db7a5f096f67467b) of this repository to see the starter code he developed. This mainly included Allegro5 initialization. All other code is original.

Version 2.0.0 includes a fully funtional menu, the ability to save the document (other than on application close), the addition of a help dialog, the ability to change the color of shape inserted, as well as general improvements to the code as well as improved organization and documentation. Note that I have written all documentation in this file (README.md).

All icons provided by  [Icons8](https://icons8.com/).

&copy; Tyler Hinrichs 2022
