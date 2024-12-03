#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
    TexCoords = aTexCoords;
}

#shader fragment
#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;

    float emissionStrength;
    sampler2D emission;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

uniform Light light;
uniform Material material;
uniform vec3 lightColor;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    vec3 emission = vec3(texture(material.emission, TexCoords)).rgb * material.emissionStrength;

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
    
}