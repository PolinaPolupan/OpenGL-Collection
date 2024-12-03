#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    int diffuseSize;
    sampler2D diffuse[128];
    sampler2D specular[128];
    sampler2D emission[128];
    float emissionWeight;
    float shininess;
    vec3 diffuseColor;
    vec3 specularColor;
};

struct Light {
    int type;

    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
    float outerCutOff;

    float intensity;

    float constant;
    float linear;
    float quadratic;
};

#define MAX_LIGHTS 128

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform int lightsNum;
uniform vec3 viewPos;
uniform Material material;

uniform Light lights[MAX_LIGHTS];

// function prototypes
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
     // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
     
    // phase 3: spot light
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.f, 0.f, 0.f);
    for (int i = 0; i < lightsNum; i++)
    {
       if (lights[i].type == 0)
       {
           result += CalcSpotLight(lights[i], norm, FragPos, viewDir);
       }
       if (lights[i].type == 1)
       {
           result += CalcPointLight(lights[i], norm, FragPos, viewDir);
       }
       if (lights[i].type == 2)
       {
           result += CalcDirLight(lights[i], norm, viewDir);
       }
    }
    
    FragColor = texture(result, TexCoords);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = vec3(0.f);
    vec3 diffuse = vec3(0.f);
    vec3 specular = vec3(0.f);
    for (int i = 0; i < material.diffuseSize; i++)
    {
        ambient += light.color * texture(material.diffuse[i], TexCoords).rgb * material.diffuseColor * 0.1f;
        diffuse += light.color * diff * (texture(material.diffuse[i], TexCoords).rgb * material.diffuseColor) * light.intensity;
        specular += light.color * spec * texture(material.specular[i], TexCoords).rgb * material.specularColor * light.intensity;
    } 
    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = vec3(0.f);
    vec3 diffuse = vec3(0.f);
    vec3 specular = vec3(0.f);
    for (int i = 0; i < material.diffuseSize; i++)
    {
        ambient += light.color * texture(material.diffuse[i], TexCoords).rgb * material.diffuseColor * 0.1f;
        diffuse += light.color * diff * (texture(material.diffuse[i], TexCoords).rgb * material.diffuseColor) * light.intensity;
        specular += light.color * spec * texture(material.specular[i], TexCoords).rgb * material.specularColor * light.intensity;
    } 
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
// calculates the color when using a directional light.
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction); // WARNING: set light dir "-" for corectness
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = vec3(0.f);
    vec3 diffuse = vec3(0.f);
    vec3 specular = vec3(0.f);
    for (int i = 0; i < material.diffuseSize; i++)
    {
        ambient += light.color * texture(material.diffuse[i], TexCoords).rgb * material.diffuseColor * 0.1f;
        diffuse += light.color * diff * (texture(material.diffuse[i], TexCoords).rgb * material.diffuseColor) * light.intensity;
        specular += light.color * spec * texture(material.specular[i], TexCoords).rgb * material.specularColor * light.intensity;
    } 
    return (ambient + diffuse + specular);
}