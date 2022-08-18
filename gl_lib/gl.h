#include "render.h"
#include <string>

void glInit();
void glCreateWindow(int, int);
void glViewPort(int, int, int, int);
void glClear();
void glClearColor(float, float, float);
void glVertex(float, float);
void glColor(float, float, float);
void glFinish();
void glLine(float, float, float, float);
void glLine(Vector3, Vector3);
void glObject(string);
void glTriangle(Vector3, Vector3, Vector3);
void glMap(string);
void glTexture(string);