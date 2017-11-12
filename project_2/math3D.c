#include <stdio.h>
#include <stdlib.h>

//#include "math3D.h"
#include "raycast.h"

V3 * V3_add(V3 *c, V3 *a, V3 *b){
	c->i = a->i + b->i;
	c->j = a->j + b->j;
	c->z = a->z + b->z;
	return c;
}

void V3_subtract(V3 *c, V3 *a, V3 *b){
	c->i = a->i - b->i;
	c->j = a->j - b->j;
	c->z = a->z - b->z;
}

void V3_multiply(V3 *c, V3 *a, double b){
	c->i = a->i * b;
	c->j = a->j * b;
	c->z = a->z * b;
}

double V3_dot(V3 *a, V3 *b){
	double c = a->i * b->i + a->j * b->j + a->z * b->z;
	return c;
}

void V3_cross(V3 *c, V3 *a, V3 *b) {
	c->i = a->j * b->z - a->z * b->j;
	c->j = a->z * b->i - a->i * b->z;
	c->z = a->i * b->j - a->j * b->i;
}
