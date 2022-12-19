#version 450 core

uniform vec3 tri_color;
uniform int TEXT_tog;
uniform sampler2D uTex2d;
uniform float alpha_val;

layout(location=0) in vec2 txt_coord;
layout (location=0) out vec4 fFragColor;		

void main () {

	if (TEXT_tog != 0 )
		fFragColor = texture(uTex2d, txt_coord) * vec4(1.0, 1.0, 1.0, alpha_val);	
	else
		fFragColor =  vec4(tri_color, alpha_val);

}