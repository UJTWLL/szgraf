#include "callbacks.h"
#include "init.h"
#include "model.h"

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Grafika Beadando (Ivancso Dorina Anett)");

    init();

    glutMainLoop();

    return 0;
}

/**
 * Sets the callbacks for GLUT.
 */
void set_callbacks() {
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
}
