// Parser CSV
// Take in by line and break up, or accept term by term. Problably latter

// Have one for plane, sphere, camera
// Poor man's polymorphism
// Cheat, put everything into one struct



// problably need obj as parameter
scene_object parse_type(scene_object obj, FILE *fr){
	// read till you get a comma
	printf("working so far?");
	//if(string is == to strcmp(str, "camera"{
	//	obj -> kind = camera;
	//}
	//... each type
	//
	return obj;
}

scene_object parse_field(scene_object obj){
	// Read till colon
	// ster = read until colon
	// if strcmp(str, "position")
	// parse_position;
	// ... each field type
	//}
	//
	return obj;
}

scene_object parse_radius(scene_object obj){
	// skip_ws(); skip whitespace
	// fscanf("%"..., &value);
	// obj-radius = value;
	// for each of the field types
	//
	return obj;
}
