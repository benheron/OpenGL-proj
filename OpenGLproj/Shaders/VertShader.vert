#version 330 core

layout(location = 0) in vec3 vertPosModelSpace;
layout(location = 1) in vec2 vertexColour;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragmentColour;


//out vec4 lightDirNormalCameraSpace;
//out vec4 vertexNormalCameraSpace;

out vec3 vertPosCameraSpace;
out vec3 vertNormal;
out vec2 vertCol;

out vec3 interpColour;
 
uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform vec3 lightDirCamera;
uniform vec3 lightIntensity;
uniform vec3 ambientIntensity;

uniform vec3 lightPosCameraSpace;


void main() {
	gl_Position = mvp * vec4(vertPosModelSpace, 1);

	
	vertPosCameraSpace = (v * m * vec4(vertPosModelSpace, 1)).xyz;
	vertNormal = (v * m * vec4(vertexNormal, 0)).xyz;
	vertCol = vertexColour;


	//diffuseColour = vec3( 0.6, 0.6, 0.6 );

	/*
	vec3 dirToLight = normalize(lightPosModelSpace - vertPosModelSpace);
    
    float cosAngIncidence = dot( vertexNormal, dirToLight);
    cosAngIncidence = clamp(cosAngIncidence, 0, 1);
    
    interpColour = (vec3(1.0,1.0,1.0) * cosAngIncidence * vec3(1.0,0.0,0.0)) +
        (ambientIntensity * vec3(1.0,0.0,0.0));
		*/


	
}