#version 450 core

layout (location = 0) in vec4 vertex;
layout (location = 0) out vec2 TexCoords;

uniform mat4 projection;
uniform float z_axis;

void main(){
	gl_Position = projection * vec4(vertex.xy, -z_axis, 1.0);
	TexCoords = vertex.zw;
}