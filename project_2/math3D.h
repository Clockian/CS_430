#ifndef MATH3D_H
#define MATH3D_H

typedef struct{
	double V0;
	double V1;
	double V2;
} V3;

V3 V3_add(V3 c, V3 a, V3 b);

void V3_subtract(V3 c, V3 a, V3 b);

// Vector Scaling
void V3_multiply(V3 c, V3 a, double b);

double V3_dot(V3 a, V3 b, double c);

void V3_cross(V3 c, V3 a, V3 b);

#endif /* MATH3D_H */
