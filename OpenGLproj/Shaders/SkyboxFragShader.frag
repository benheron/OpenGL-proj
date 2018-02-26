#version 330 core

in vec3 vertPosCameraSpace;
in vec3 vertNormal;
in vec2 vertCol;

out vec3 colour;

uniform sampler2D textureSampler;




 void main() { 
	colour = texture(textureSampler, vertCol).rgb;
 }


