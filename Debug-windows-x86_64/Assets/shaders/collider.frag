#version 450 core

uniform vec3 tri_color;

layout (location=0) out vec4 fFragColor;		

void main () {
		fFragColor =  vec4(tri_color, 1.0);
}