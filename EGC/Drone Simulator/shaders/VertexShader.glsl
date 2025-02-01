#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main() {

	vec3 modified_position = v_position;
    modified_position.y += 1. * sin(.05 * v_position.x + .03 * v_position.z);

	if (modified_position.y < 0) modified_position.y = 0;
	
	// send to fragment shader
	frag_position	= modified_position;
	frag_normal		= v_normal;
	frag_texture	= v_texture;
	frag_color		= v_color;

	vec3 v_pos_final = v_position;
	gl_Position = Projection * View * Model * vec4(modified_position, 1.0);
}