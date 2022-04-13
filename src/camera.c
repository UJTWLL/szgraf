#include "camera.h"
#include "init.h"
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define size 2000

double degree_to_radian(double degree) {
    return degree * M_PI / 180.0;
}

void init_camera(struct Camera *camera) {
	camera->position.x = 0.0;
    camera->position.y = 900.0;
    camera->position.z = -1250.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 180.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
	camera->change_amount = 0.0;
}

void set_view_point(const struct Camera *camera) {
    glRotatef(-(camera->rotation.x), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z), 0, 1.0, 0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);

}

void rotate_camera(struct Camera *camera, double horizontal, double vertical) {
    double fallbackRotationOfX;

    // Vertical, with rollover protection
    if (camera->rotation.x >= 0 && camera->rotation.x <= 90) {
        fallbackRotationOfX = 90;
    } else {
        fallbackRotationOfX = 270;
    }

    if (camera->rotation.x + vertical > 90 && camera->rotation.x + vertical < 270) {
        camera->rotation.x = fallbackRotationOfX;
    } else {
        camera->rotation.x += vertical;
    }

    if (camera->rotation.x > 90 && camera->rotation.x < 270) {
        set_clear_camera_rotation(camera);
    }


    // Horizontal
    camera->rotation.z += horizontal;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_clear_camera_rotation(struct Camera *camera) {
    camera->rotation.x = 0;
}

void set_camera_hspeed(struct Camera *camera, double speed) {
	camera->speed.x = speed;
}

void set_camera_side_speed(struct Camera *camera, double speed) {
	camera->speed.y = speed;
}

void set_camera_vspeed(struct Camera *camera, double speed) {
	camera->speed.z = speed;
}

void change_light(struct Camera *camera, double amount){
	camera->change_amount = amount;
}

void update_camera(Camera* camera, double time)
{
    double hangle;
    double side_angle;

    hangle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z+90);

    camera->position.x += sin(hangle) * camera->speed.x * time;
    camera->position.z += cos(hangle) * camera->speed.x * time;
    camera->position.x += sin(side_angle) * camera->speed.y * time;
    camera->position.z += cos(side_angle) * camera->speed.y * time;
	camera->position.y += camera->speed.z * time;
	camera->position.y += camera->speed.z * time;
	
	if (light_ambient[0] <= 0.5){
		light_ambient[0] = light_ambient[1] = light_ambient[2] = light_ambient[3] += 0.04;
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
	else if(light_ambient[0] >= 20){
		light_ambient[0] = light_ambient[1] = light_ambient[2] = light_ambient[3] -= 0.04;
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
	else{
		light_ambient[0] = light_ambient[1] = light_ambient[2] = light_ambient[3] += camera->change_amount;
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
}