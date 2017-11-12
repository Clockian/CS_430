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

char * remove_brackets_whitespace(char *str);

char * parse(char *str);

char * cut_string(char *str);

scene_object * determine_type(char *str);

scene_object * parse_camera(char *str);

scene_object * parse_sphere(char *str);

scene_object * parse_plane(char *str);

scene_object parse_radius_width_height(scene_object obj, char *str);

scene_object parse_color_position_normal(scene_object obj);

int get_num_lines(FILE *fr);

//scene_object ** read_csv_file(FILE *fr);
void read_csv_file(FILE *fr, scene_object result[]);

#endif /* PARSER_H */
