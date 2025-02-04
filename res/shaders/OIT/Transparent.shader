#shader vertex
#version 420 core

// shader inputs
layout (location = 0) in vec3 aPos;

// model * view * projection matrix
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
layout (location = 0) out vec4 accum;
layout (location = 1) out float reveal;

// material color
uniform vec4 color;

void main()
{
	// weight function
	float weight = clamp(pow(min(1.0, color.a * 10.0) + 0.01, 3.0) * 1e8 * pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);
	
	// store pixel color accumulation
	accum = vec4(color.rgb * color.a, color.a) * weight;
	
	// store pixel revealage threshold
	reveal = color.a;
}
