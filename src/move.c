#include <math.h>
#include "model.h"
#include "callbacks.h"
#include "move.h"

void reset_objects(World *world) {
	world->object.position.x = 0;
	world->object.position.y = 1000;
	world->object.position.z = 0;
	world->object.velocity.x = 0.01;
	world->object.velocity.y = 0.01;
	world->object.velocity.z = 0.01;
}

/*int check_collisions(World *world){
	int is_colliding = false;
	
	if(world->object.position.y < 220){
		is_colliding = true;
	}
	
	return is_colliding;
}*/

void apply_physics(World *world, double time){
	double vx = world->object.velocity.x;
	double vy = world->object.velocity.y;
	double vz = world->object.velocity.z;
	double g = 9.81;
	double yvalue = vy * 0.5 * g * time * time;
	double xvalue = vx * 0.95 * time;
	double zvalue = vz * 0.95 * time;
	
	//1/2g*t^2
	//g=9,81;
	
	world->object.position.x -= xvalue;
	world->object.position.y -= yvalue;
	world->object.position.z -= zvalue;
	
	if(world->object.position.y < 220){
		world->object.velocity.y += world->object.position.y;
		world->object.velocity.y *= -0.55;
	}
	else{
		world->object.velocity.y += world->object.position.y;
	}
	
	/*if(world->object.position.x < 1000){
		world->object.velocity.x += world->object.position.x;
		world->object.velocity.x *= -0.95;
	}
	else{
		world->object.velocity.x += world->object.position.x;
	}
	
	if(world->object.position.z < 1000){
		world->object.velocity.z += world->object.position.z;
		world->object.velocity.z *= -0.95;
	}
	else{
		world->object.velocity.z += world->object.position.z;
	}*/
}
