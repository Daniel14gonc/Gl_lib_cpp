#include "render.h"

// Method that initialize the renderer.
void glInit();

// Method that creates the buffer with an specific 
// width and height from user.
void glCreateWindow(int, int);

//Method that sets the drawable space in the resulting image.
void glViewPort(int, int, int, int);

// Method that clears the window.
void glClear();

// Method that sets the color for when the window is cleared.
void glClearColor(float, float, float);

// Method that draws a point in the screen.
void glVertex(float, float);

// Method that sets a user specified color for
// drawing on screen.
void glColor(float, float, float);

// Method that writes everything to the resulting image.
void glFinish();

// Method that draws a line on screen.
void glLine(float, float, float, float);