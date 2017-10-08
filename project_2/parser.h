#ifndef PARSER_H
#define PARSER_H

typedef struct{
	int kind;  // 0-Camera, 1-sphere, 2-plane
	double width;  // Of
	double position[3];
	double color[3];
	double radius;
	double normal[3]; // plane
	double cam_width;
	double cam_height;
}scene_object;

scene_object parse_type(scene_object obj, char *argv[]);

scene_object parse_field(scene_object obj);

scene_object parse_field(scene_object obj);

#endif /* PARSER_H */
