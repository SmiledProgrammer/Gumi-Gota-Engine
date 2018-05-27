#shader vertex
#version 330 core

/*
*	MAX_RENDERED_LIGHTS = 16
*/


/* In Variables */
layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec2 in_textureCoordinates;
layout(location = 2) in vec3 in_normal;


/* Out Variables */
out vec2 pass_textureCoordinates;

out vec3 pass_toLightVector[16];
out vec3 pass_surfaceNormal;
out vec3 pass_toCameraVector;

out float pass_visibility;


/* Uniforms */
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

uniform vec3 u_lightPosition[16];

uniform float u_hasFakeLighting;

uniform float u_fogDensity;
uniform float u_fogGradient;

uniform float u_textureRows;
uniform vec2 u_textureCoordinatesOffset;

uniform vec4 u_clippingPlane;


/* Main Loop */
void main()
{
	/* CALCULATIONS */
	// Calculating World Position
	vec4 worldPosition = u_modelMatrix * vec4(in_vertex, 1.0);

	// Calculating Position Relative to Camera
	vec4 positionRelativeToCamera = u_viewMatrix * worldPosition;

	// Transformating Normal
	vec3 actualNormal = in_normal;
	if (u_hasFakeLighting > 0.5)
	{
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	// Light Calculations
	pass_surfaceNormal = (u_modelMatrix * vec4(actualNormal, 0.0)).xyz;

	for (int i = 0; i < 16; i++)
	{
		pass_toLightVector[i] = u_lightPosition[i] - worldPosition.xyz;
	}

	pass_toCameraVector = (inverse(u_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	// Clipping Calculations
	gl_ClipDistance[0] = dot(worldPosition, u_clippingPlane);

	// Fog Calculations
	float distance = length(positionRelativeToCamera.xyz);
	pass_visibility = exp(-pow((distance * u_fogDensity), u_fogGradient));
	pass_visibility = clamp(pass_visibility, 0.0, 1.0);
	
	// Texture Coordinates Calculations
	pass_textureCoordinates = (in_textureCoordinates / u_textureRows) + u_textureCoordinatesOffset;

	/* POSITION SETTING */
	gl_Position = u_projectionMatrix * positionRelativeToCamera;
}






#shader fragment
#version 330 core


/* In Variables */
in vec2 pass_textureCoordinates;

in vec3 pass_toLightVector[16];
in vec3 pass_surfaceNormal;
in vec3 pass_toCameraVector;

in float pass_visibility;


/* Out Variables */
out vec4 out_color;


/* Uniforms */
uniform sampler2D u_textureSampler;

uniform vec3 u_lightColor[16];
uniform vec3 u_lightAttenuation[16];
uniform float u_shineDamper;
uniform float u_reflectivity;

uniform vec3 u_skyColor;


/* Main Loop */
void main()
{
	/* CALCULATIONS */
	// Light Calculations
	vec3 unitNormal = normalize(pass_surfaceNormal);
	vec3 unitVectorToCamera = normalize(pass_toCameraVector);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for (int i = 0; i < 16; i++)
	{
		if (u_lightAttenuation[i] == vec3(0.0) && u_lightColor[i] == vec3(0.0))
		{
			break;
		}


		float lightDistance = length(pass_toLightVector[i]);
		float attenuationFactor = u_lightAttenuation[i].x + (u_lightAttenuation[i].y * lightDistance) + (u_lightAttenuation[i].z * lightDistance * lightDistance);

		vec3 unitLightVector = normalize(pass_toLightVector[i]);

		float normalDot = dot(unitNormal, unitLightVector);
		float brightness = max(normalDot, 0.0);

		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0);
		float dampedFactor = pow(specularFactor, u_shineDamper);
		totalDiffuse = totalDiffuse + (brightness * u_lightColor[i]) / attenuationFactor;
		totalSpecular = totalSpecular + (dampedFactor * u_reflectivity * u_lightColor[i]) / attenuationFactor;
	}

	totalDiffuse = max(totalDiffuse, 0.2);

	// Texture Calculations
	vec4 textureColor = texture2D(u_textureSampler, pass_textureCoordinates);
	if (textureColor.a < 0.5)
	{
		discard;
	}

	/* COLOR SETTING */
	out_color = vec4(totalDiffuse, 1.0) * textureColor + vec4(totalSpecular, 1.0);
	out_color = mix(vec4(u_skyColor, 1.0), out_color, pass_visibility);

}