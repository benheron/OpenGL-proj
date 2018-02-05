#version 330 core

in vec3 fragmentColour;
in vec3 vertPosCameraSpace;
in vec3 vertNormal;
in vec2 vertCol;

in vec3 interpColour;

out vec3 colour;



uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform vec3 lightDirCamera;
uniform vec3 lightIntensity;
uniform vec3 ambientIntensity;
uniform float lightAttenuation;


uniform vec3 lightPosCameraSpace;

uniform sampler2D textureSampler;


 vec3 ApplyLightIntensity(in vec3 cameraSpacePos, out vec3 lightDir)
 {
	vec3 lightDiff = lightPosCameraSpace - cameraSpacePos;
	float lightDistSq = dot(lightDiff, lightDiff);
	lightDir = lightDiff * inversesqrt(lightDistSq);

	float distFactor = sqrt(lightDistSq);
	
	//return vec3(1.0);

	return lightIntensity * (1 / (1.0 + lightAttenuation * distFactor));

 }


 void main() { 

	
	vec3 diffuseColour = texture(textureSampler, vertCol).rgb;

	//vec3 diffuseColour = vec3(0.6, 0.6, 0.6);

	
	float shininessFactor = 1;

	vec3 lightDir = vec3(0.0);

	vec3 attenIntensity = ApplyLightIntensity(vertPosCameraSpace, lightDir);

	vec3 surfaceNormal = normalize(vertNormal);

	float cosAngIncidence = dot(surfaceNormal, lightDir);
	float clampedCos = clamp(cosAngIncidence, 0 ,1);

	vec3 specularColour = vec3(0.3,0.3,0.3);


	vec3 viewDir = normalize(-vertPosCameraSpace);
	

	//blinn-phong
	vec3 halfAngle = normalize(lightDir + viewDir);
	float blinnTerm = dot(surfaceNormal, halfAngle);
	
	blinnTerm = clamp(blinnTerm, 0, 1);
	blinnTerm = cosAngIncidence != 0.0 ? blinnTerm : 0.0;
	blinnTerm = pow(blinnTerm, shininessFactor);

	//phong
	//vec3 reflectDir = reflect(-lightDir, surfaceNormal);
	//float phongTerm = dot(viewDir, reflectDir);
	//phongTerm = clamp(phongTerm, 0, 1);
	//phongTerm = cosAngIncidence != 0.0 ? phongTerm : 0.0;
	//phongTerm = pow(phongTerm, 4);

	float angleNormalHalf = acos(dot(halfAngle, surfaceNormal));
	float exponent = angleNormalHalf/shininessFactor;
	exponent = -(exponent*exponent);
	float gaussianTerm = exp(exponent);

	gaussianTerm = cosAngIncidence != 0.0 ? gaussianTerm : 0.0;





	colour = (diffuseColour *  attenIntensity  * clampedCos) +
			 (specularColour * attenIntensity * gaussianTerm) +
					(diffuseColour * ambientIntensity) ;


					
//	colour = vec3(1.0, 0, 0);
	
 }


