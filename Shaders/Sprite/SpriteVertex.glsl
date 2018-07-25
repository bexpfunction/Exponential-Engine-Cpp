#version 330 core

in vec3 aPos;

uniform vec2 worldPosition;

void main(){
	gl_Position = vec4(aPos.x+worldPosition.x, aPos.y+worldPosition.y, aPos.z , 1.0f);
}