#shader vertex
#version 330 core


/* In Variables */
layout(location = 0) in vec2 in_data;

in mat4 in_modelViewMatrix;
in vec2 in_textureOffset;


/* Out Variables */
out vec2 pass_textureCoordinates;


/* Uniforms */
uniform mat4 u_projectionMatrix;

uniform float u_textureAtlasRows;

uniform vec4 u_clippingPlane;


/* Main Loop */
void main()
{
	/* CALCULATIONS */
	// Position Calculations
	vec4 worldPosition = in_modelViewMatrix * vec4(in_data, 0.0, 1.0);

	// Texture Coordinates Calculations
	vec2 textureCoordinates = in_data + vec2(0.5, 0.5);
	textureCoordinates /= u_textureAtlasRows;
	pass_textureCoordinates = textureCoordinates + in_textureOffset;

	// Clipping Calculations
	gl_ClipDistance[0] = dot(worldPosition, u_clippingPlane);

	/* POSITION SETTING */
	gl_Position = u_projectionMatrix * worldPosition;
}






#shader fragment
#version 330 core


/* In Variables */
in vec2 pass_textureCoordinates;


/* Out Variables */
out vec4 out_color;


/* Uniforms */
uniform sampler2D u_textureSampler;


/* Main Loop */
void main()
{
	// Color Setting
	out_color = texture(u_textureSampler, pass_textureCoordinates);
	///out_color = vec4(1.0);
}