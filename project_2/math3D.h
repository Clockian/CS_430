#ifndef MATH3D_H
#define MATH3D_H

//#include "raycast.h"

V3 V3_add(V3 c, V3 a, V3 b);

void V3_subtract(V3 c, V3 a, V3 b);

void V3_multiply(V3 c, V3 a, double b);

double V3_dot(V3 a, V3 b);

void V3_cross(V3 c, V3 a, V3 b);

#endif /* MATH3D_H */
