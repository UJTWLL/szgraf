#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_

#include "camera.h"
#include "move.h"

#include <GL/glut.h>

int mouse_x, mouse_y;

struct Camera camera;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;


/**
 * Set the callbacks for GLUT.
 */
void set_callbacks();

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);


/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after key on keyboard backed up.
 */
void keyboardUp(unsigned char key, int x, int y);

/**
 * Call when special key on keyboard is pressed.
 */
void specialFunc(int key, int x, int y);

/**
 * Call after mouse event.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call when in motion
 */
void motion(int x, int y);

/**
 * Call when there is no other event.
 */
void idle();

/**
 * Returns the elapsed time since the program started.
 */
double calc_elapsed_time();

/**
 * Resets the objects to their default state.
 */
void reset_objects(World *world);

#endif /* INCLUDE_CALLBACKS_H_ */
