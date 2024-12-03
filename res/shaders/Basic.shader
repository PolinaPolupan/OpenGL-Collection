#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 v_TexCoord;
uniform mat4 u_MVP;
uniform mat4 transform;

void main()
{
	vec4 pos = vec4(position, 1.f);
   gl_Position = transform * u_MVP * pos;
   v_TexCoord = texCoord;
   ourColor = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 ourColor;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) / vec4(ourColor, 1.f);
	color = texColor;
};