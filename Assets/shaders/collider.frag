#version 450 core

uniform vec3 tri_color;
uniform float alpha_val;

layout (location=0) out vec4 fFragColor;		

void main () {
		fFragColor =  vec4(tri_color, alpha_val);
}