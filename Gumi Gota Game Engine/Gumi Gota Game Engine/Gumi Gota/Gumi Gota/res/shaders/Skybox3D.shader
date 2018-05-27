#shader vertex
#version 330 core


/* In Variables */
layout(location = 0) in vec3 in_position;


/* Out Variables */
out vec3 pass_textureCoordinates;


/* Uniforms */
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

uniform vec4 u_clippingPlane;


/* Main Loop */
void main()
{
	/* CALCULATIONS */
	// Position Calculations
	vec4 transformedPosition = vec4(in_position, 1.0);
	vec4 newPosition = u_projectionMatrix * u_viewMatrix * transformedPosition;

	// Clipping Calculations
	gl_ClipDistance[0] = dot(transformedPosition, u_clippingPlane);

	/* PASSING */
	pass_textureCoordinates = in_position;

	/* POSITION SETTING */
	gl_Position = newPosition.xyww;
}






#shader fragment
#version 330 core


/* In Variables */
in vec3 pass_textureCoordinates;


/* Out Variables */
out vec4 out_color;


/* Uniforms */
uniform samplerCube u_skyboxSampler;


/* Main Loop */
void main()
{
	/* COLOR SETTING */
	out_color = texture(u_skyboxSampler, pass_textureCoordinates);

}