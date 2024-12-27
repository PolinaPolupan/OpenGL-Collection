#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform int textureType;

void main()
{ 
    vec4 Diffuse = texture(gAlbedoSpec, TexCoords);
    vec3 result;

    switch (textureType) {
    case 0:
        result = texture(gAlbedoSpec, TexCoords).rgb;
        break;
    case 1:
        float Specular = texture(gAlbedoSpec, TexCoords).a;
        result = vec3(Specular);
        break;
    case 2:
        result = texture(gPosition, TexCoords).rgb;
        break;
    case 3:
        result = texture(gNormal, TexCoords).rgb;
        break;
    }

   FragColor = vec4(result, 1.0);
} 