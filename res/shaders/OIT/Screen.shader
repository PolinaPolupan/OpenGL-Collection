#shader vertex
#version 420 core

// shader inputs
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

// shader outputs
out vec2 texture_coords;

void main()
{
	texture_coords = uv;

	gl_Position = vec4(position, 1.0f);
}

#shader fragment
#version 420 core

// shader inputs
in vec2 texture_coords;

// shader outputs
layout (location = 0) out vec4 frag;

// screen image
uniform sampler2D screen;

void main()
{
	frag = vec4(texture(screen, texture_coords).rgb, 1.0f);
}
