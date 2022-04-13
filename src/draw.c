#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "draw.h"
#include "model.h"
#include "callbacks.h"

double sizeOfRoom = 2000;

void draw_content(World *world) {
    Room roomToDraw = world->room;
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    draw_walls(roomToDraw);
    draw_ground(roomToDraw);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(world->object.position.x, world->object.position.y, world->object.position.z);
	
    glMaterialfv(GL_FRONT, GL_AMBIENT, world->object.material_ambient); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, world->object.material_diffuse); 	
    glMaterialfv(GL_FRONT, GL_SPECULAR, world->object.material_specular); 	
    glMaterialf(GL_FRONT, GL_SHININESS, world->object.material_shine);		
    glBindTexture(GL_TEXTURE_2D, world->object.texture);
    glScalef(3.5f, 3.5f, 3.5f);
    draw_model(&world->object.model);
    glPopMatrix();
}

void draw_ground(Room room) {
    glBindTexture(GL_TEXTURE_2D, room.ground);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBegin(GL_QUADS);
    int x, z;
    for (x = -sizeOfRoom; x < sizeOfRoom; x += 50) {
        for (z = -sizeOfRoom; z < sizeOfRoom; z += 50) {
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x, 0, z);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x + 50, 0, z);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x + 50, 0, z + 50);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x, 0, z + 50);
        }
    }
    glEnd();
}

void draw_walls(Room room) {
    glBindTexture(GL_TEXTURE_2D, room.left);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-sizeOfRoom, 0, -sizeOfRoom);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-sizeOfRoom, 0, sizeOfRoom);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.right);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(sizeOfRoom, 0, sizeOfRoom);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(sizeOfRoom, 0, -sizeOfRoom);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.front);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-sizeOfRoom, 0, -sizeOfRoom);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(sizeOfRoom, 0, -sizeOfRoom);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.back);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-sizeOfRoom, 0, sizeOfRoom);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(sizeOfRoom, 0, sizeOfRoom);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, room.top);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
    glEnd();
}

void draw_triangles(const struct Model *model) {
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, normal_x, normal_y, normal_z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {
            normal_index = model->triangles[i].points[k].normal_index;
            normal_x = model->normals[normal_index].x;
            normal_y = model->normals[normal_index].y;
            normal_z = model->normals[normal_index].z;
            glNormal3d(normal_x, normal_y, normal_z);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            switch (k) {
                case 0:
                    glTexCoord2f(0, 0);
                    break;
                case 1:
                    glTexCoord2f(0.1 * z, 0);
                    break;
                case 2:
                    glTexCoord2f(0, 0.01);
                    break;
            }
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_quads(const struct Model *model) {
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

    glBegin(GL_QUADS);
    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;

            glTexCoord2f(u, 1 - v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }
    glEnd();
}

void draw_normals(const struct Model *model, double length) {
    int i;
    double x1, y1, z1, x2, y2, z2;

    glColor3f(0, 0, 1);

    glBegin(GL_LINES);
    for (i = 0; i < model->n_vertices; ++i) {
        x1 = model->vertices[i].x;
        y1 = model->vertices[i].y;
        z1 = model->vertices[i].z;
        x2 = x1 + model->normals[i].x * length;
        y2 = y1 + model->normals[i].y * length;
        z2 = z1 + model->normals[i].z * length;
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
    }
    glEnd();
}

void draw_model(const struct Model *model) {
    draw_triangles(model);
    draw_quads(model);
}

void draw_help(int texture) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1, 0);
    glVertex3f(WINDOW_WIDTH, 0, 0);

    glTexCoord2f(1, 1);
    glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glTexCoord2f(0, 1);
    glVertex3f(0, WINDOW_HEIGHT, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
