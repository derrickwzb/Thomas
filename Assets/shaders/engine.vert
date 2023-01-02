#version 450 core

layout(location=0) in vec2 aVertexPosition;	
layout(location=1) in vec2 atxt_coord_in;

layout(location=0) out vec2 txt_coord_out;

uniform mat3 uModelToNDC;
uniform mat3 uWorldToNDC;
uniform float z_axis;

void main() {
	gl_Position = vec4(vec2(uWorldToNDC * uModelToNDC * vec3(aVertexPosition, 1.f)), z_axis, 1.f);
	txt_coord_out = atxt_coord_in;
}