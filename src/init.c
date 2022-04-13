#include <GL/glut.h>

#include "callbacks.h"

GLfloat light_position[] = {100, 100, 100, 100};
GLfloat light_ambient[] = {8, 8, 8, 8};
GLfloat light_diffuse[] = {5, 5, 5, 5};
GLfloat light_specular[] = {1.1, 1.1, 1.1, 1.1};

void init() {
    set_callbacks();

    init_camera(&camera);
    init_entities(&world);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
}
