#ifndef CAMERA_H
#define CAMERA_H

#include "model.h"

typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
	double change_amount;
} Camera;

/*
* Converts degree to radian
*/
double degree_to_radian(double degree);

/**
 * Initialize the camera position and direction.
 */
void init_camera(struct Camera *camera);

/**
 * Transform the models into the view point of the camera.
 */
void set_view_point(const struct Camera *camera);

/**
 * Rotate the camera horizontally and vertically.
 */
void rotate_camera(struct Camera *camera, double horizontal, double vertical);

/**
 * Resets the vertical rotation of the camera.
 */
void set_clear_camera_rotation(struct Camera *camera);

/**
 * Move the camera forward or backward.
 */
void set_camera_hspeed(struct Camera *camera, double speed);

/**
 * Move the camera left or right.
 */
void set_camera_side_speed(struct Camera *camera, double speed);

/**
 * Move the camera vertically.
 */
void set_camera_vspeed(struct Camera *camera, double speed);

/**
 * Change the ambient light.
 */
void change_light(struct Camera *camera, double amount);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, double time);

#endif // CAMERA_H
