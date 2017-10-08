#include <stdio.h>
#include <stdlib.h>
#include "math3D.h"

V3 V3_add(V3 c, V3 a, V3 b){
	c.V0 = a.V0 + b.V0;
	c.V1 = a.V1 + b.V1;
	c.V2 = a.V2 + b.V2;
	return c;
}

void V3_subtract(V3 c, V3 a, V3 b){
	c.V0 = a.V0 - b.V0;
	c.V1 = a.V1 - b.V1;
	c.V2 = a.V2 - b.V2;
}

// Vector Scaling
void V3_multiply(V3 c, V3 a, double b){
	c.V0 = a.V0 * b;
	c.V1 = a.V1 * b;
	c.V2 = a.V2 * b;
}

double V3_dot(V3 a, V3 b, double c){
	c = a.V0 * b.V0 + a.V1 * b.V1 + a.V2 * b.V2;
	return c;
}

void V3_cross(V3 c, V3 a, V3 b){
	c.V0 = a.V1 * b.V2 - a.V2 * b.V1;
	c.V1 = a.V2 * b.V0 - a.V0 * b.V2;
	c.V2 = a.V0 * b.V1 - a.V1 * b.V0;
}
