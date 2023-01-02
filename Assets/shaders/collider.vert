#version 450 core

layout(location=0) in vec2 aVertexPosition;	

uniform mat3 uModelToNDC;
uniform mat3 uWorldToNDC;

void main() {
	gl_Position = vec4(vec2(uWorldToNDC * uModelToNDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
}