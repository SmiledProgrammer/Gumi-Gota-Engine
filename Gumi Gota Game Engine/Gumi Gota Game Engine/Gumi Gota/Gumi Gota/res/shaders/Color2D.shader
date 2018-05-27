#shader vertex
#version 330 core


/* In Variables */
layout(location = 0) in vec2 in_data;

/* Out Variables */

/* Uniforms */
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;


/* Main Loop */
void main()
{
	// Position Setting
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(in_data, 0.0, 1.0);
}






#shader fragment
#version 330 core


/* In Variables */

/* Out Variables */
out vec4 out_color;

/* Uniforms */
uniform vec4 u_color;


/* Main Loop */
void main()
{
	// Color Setting
	out_color = u_color;
}