#ifndef INCLUDE_MOVE_H_
#define INCLUDE_MOVE_H_

#define FALSE 0
#define TRUE 1

#include "model.h"

void reset_objects(World *world);

void apply_physics(World *world, double time);

int check_collisions(World *world);

#endif /* INCLUDE_MOVE_H_ */
