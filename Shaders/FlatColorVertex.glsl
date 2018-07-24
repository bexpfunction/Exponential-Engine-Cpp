#version 330 core

in vec3 aPos;

uniform int test;
uniform float offset;

void main(){
	gl_Position = vec4(aPos.x, aPos.y+offset, aPos.z , 1.0f);
}