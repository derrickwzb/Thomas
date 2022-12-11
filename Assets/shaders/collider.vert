#version 450 core

layout(location=0) in vec2 aVertexPosition;	

uniform mat3 uModelToNDC;
uniform mat3 uWorldToNDC;
uniform float z_axis;

void main() {
	gl_Position = vec4(vec2(uWorldToNDC * uModelToNDC * vec3(aVertexPosition, 1.f)), z_axis, 1.0);
}