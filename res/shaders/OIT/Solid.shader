#shader vertex
#version 420 core

// shader inputs
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	 gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 420 core

// shader outputs
layout (location = 0) out vec4 frag;

// material color
uniform vec3 color;

void main()
{
	frag = vec4(color, 1.0f);
}
