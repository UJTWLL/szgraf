#include <math.h>
#include "callbacks.h"
#include "init.h"
#include "draw.h"
#include "model.h"
#include "move.h"

#include <stdlib.h>

int isHelpOn = 0;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

void display() {
    double elapsed_time = calc_elapsed_time();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    update_camera(&camera, elapsed_time);
    draw_content(&world);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble) WINDOW_WIDTH / (GLdouble) WINDOW_HEIGHT, 0.1, 20000.0);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    set_view_point(&camera);

    if (isHelpOn) {
        GLfloat torchForHelp[] = {0.8, 0.8, 0.8, 0.8};
        glLightfv(GL_LIGHT1, GL_AMBIENT, torchForHelp);

        glLoadIdentity();
        gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

        draw_help(world.helpTexture);

        glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;


    set_clear_camera_rotation(&camera);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            set_camera_hspeed(&camera, -250.0);
            break;
        case 's':
            set_camera_hspeed(&camera, 250.0);
            break;
        case 'a':
            set_camera_side_speed(&camera, -250.0);
            break;
        case 'd':
            set_camera_side_speed(&camera, 250.0);
            break;
        case 'e':
            set_camera_vspeed(&camera, 100.0);
            break;
        case 'q':
            set_camera_vspeed(&camera, -100.0);
            break;
        case 'r':
            change_light(&camera, 0.02);
            break;
        case 'f':
            change_light(&camera, -0.02);
            break;
        case 32:
            reset_objects(&world);
            break;
        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 's':
            set_camera_hspeed(&camera, 0.0);
            break;
        case 'a':
        case 'd':
            set_camera_side_speed(&camera, 0.0);
            break;
        case 'e':
        case 'q':
            set_camera_vspeed(&camera, 0.0);
            break;
		case 'r':
		case 'f':
			change_light(&camera, 0);
			break;
    }

    glutPostRedisplay();
}

void specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            if (isHelpOn == 1) {
                isHelpOn = 0;
            } else isHelpOn = 1;
    }
}

void mouse(int button, int state, int x, int y) {
    mouse_x = x;
    mouse_y = y;
}

void motion(int x, int y) {
    double horizontal, vertical;

    horizontal = mouse_x - x;
    vertical = mouse_y - y;

    rotate_camera(&camera, horizontal, vertical);

    mouse_x = x;
    mouse_y = y;

    glutPostRedisplay();
}

double calc_elapsed_time() {
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;

    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double) (current_time - last_frame_time) / 1000.0;
    last_frame_time = current_time;


    return elapsed_time;
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);
	apply_physics(&world, elapsed_time);

    glutPostRedisplay();
}