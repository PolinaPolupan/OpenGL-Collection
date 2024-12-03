#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
    sampler2D emission;
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

float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

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
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    vec4 depthVec4 = vec4(vec3(pow(depth, 1.4)), 1.0);
    gl_FragColor = vec4(result, 1.f) * (1 - depthVec4) + depthVec4;
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
    vec3 ambient = light.color * texture(material.diffuse1, TexCoords).rgb * material.diffuseColor * 0.025f;
    vec3 diffuse = light.color * diff * (texture(material.diffuse1, TexCoords).rgb * material.diffuseColor) * light.intensity;
    vec3 specular = light.color * spec * texture(material.specular1, TexCoords).rgb * material.specularColor * light.intensity;
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
    vec3 ambient = light.color * vec3(texture(material.diffuse1, TexCoords)) * 0.025f;
    vec3 diffuse =  light.color * light.intensity * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.color * light.intensity * spec * vec3(texture(material.specular1, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
// calculates the color when using a directional light.
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction); // WARNING: set light dir "-" for corectness
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.color * vec3(texture(material.diffuse1, TexCoords)) * 0.025f;
    vec3 diffuse = light.color * light.intensity * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.color * light.intensity * spec * vec3(texture(material.specular1, TexCoords));
    return (ambient + diffuse + specular);
}

