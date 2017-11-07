//vertex shader
#version 430 core 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;


uniform mat4 model_matrix, projection_matrix, view_matrix;

out vec2 texture_coord;
out vec4 color;

void main(){
	vec3 light_dir = vec3(0, 0, 1);
	vec4 light_color = vec4(1.0);
	texture_coord = in_uv;
	color = light_color * max(dot(normalize(mat3(model_matrix) * in_normal), light_dir), 0);
	gl_Position = projection_matrix * view_matrix *
		model_matrix * vec4(in_position, 1);
}