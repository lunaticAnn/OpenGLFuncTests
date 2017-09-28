//vertex shader
#version 430 core 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

out vec4 color;

void main(){
	color = (in_position.x + 0.5) * vec4(1.0,0.0,0.0,0.0);
	gl_Position = vec4(in_position, 1);
}