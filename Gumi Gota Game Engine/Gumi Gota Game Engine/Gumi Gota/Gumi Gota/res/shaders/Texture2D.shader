#shader vertex
#version 330 core


/* In Variables */
layout(location = 0) in vec2 in_data;


/* Out Variables */
out vec2 pass_textureCoordinates;


/* Uniforms */
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;


/* Main Loop */
void main()
{
	// Passing
	pass_textureCoordinates = in_data;

	// Position Setting
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(in_data, 0.0, 1.0);
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
	// Calculating Color
	vec4 textureColor = texture2D(u_textureSampler, pass_textureCoordinates);

	// Color Setting
	out_color = textureColor;
}