#version 450 core

layout(location=0) in vec2 aVertexPosition;	

uniform mat3 uModelToNDC;

void main() {
	gl_Position = vec4(vec2(uModelToNDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
}