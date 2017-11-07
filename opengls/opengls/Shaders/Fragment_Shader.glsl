#version 430 core

layout(location = 0) out vec4 out_color;

uniform sampler2D texture1;
in vec2 texture_coord;
in vec4 color;

void main(){
	out_color = color * texture(texture1, texture_coord);	
}