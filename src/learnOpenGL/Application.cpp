#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <filesystem>

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ClearColor.h"
#include "Texture2D.h"
#include "Scene.h"
#include "CoordinateSystem.h"
#include "BasicLighting.h"
#include "ModelLoading.h"
#include "Blending.h"
#include "FaceCulling.h"
#include "Framebuffers.h"
#include "Cubemaps.h"
#include "AdvancedGLSL.h"
#include "GeometryShader.h"
#include "Instancing.h"
#include "Antialiasing.h"
#include "AdvancedLighting.h"
#include "GammaCorrection.h"
#include "ShadowMapping.h"
#include "PointShadows.h"
#include "NormalMapping.h"
#include "ParallaxMapping.h"
#include "Hdr.h"
#include "Bloom.h"
#include "DeferredShading.h"
#include "SSAO.h"

#include "assimp/Importer.hpp"

#include "Constants.h"


float mouseX;
float mouseY;
float offsetX;
float offsetY;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwWindowHint(GLFW_SAMPLES, 4);

    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    scene::Scene* currentTest = nullptr;
    scene::SceneMenu* sceneMenu = new scene::SceneMenu(currentTest);
    currentTest = sceneMenu;
    
    sceneMenu->RegisterScene<scene::ClearColor>("Clear Color");
    sceneMenu->RegisterScene<scene::Texture2D>("Texture 2D");
    sceneMenu->RegisterScene<scene::CoordinateSystem>("Coordinate System");
    sceneMenu->RegisterScene<scene::BasicLighting>("Basic Lighting");
    sceneMenu->RegisterScene<scene::ModelLoading>("Model Loading");
    sceneMenu->RegisterScene<scene::Blending>("Blending");
    sceneMenu->RegisterScene<scene::FaceCulling>("Face Culling");
    sceneMenu->RegisterScene<scene::Framebuffers>("Framebuffers");
    sceneMenu->RegisterScene<scene::Cubemaps>("Cubemaps");
    sceneMenu->RegisterScene<scene::AdvancedGLSL>("Advanced GLSL");
    sceneMenu->RegisterScene<scene::GeometryShader>("Geometry Shader");
    sceneMenu->RegisterScene<scene::Instancing>("Instancing");
    sceneMenu->RegisterScene<scene::Antialiasing>("Antialiasing");
    sceneMenu->RegisterScene<scene::AdvancedLighting>("Advanced Lighting");
    sceneMenu->RegisterScene<scene::GammaCorrection>("Gamma Correction");
    sceneMenu->RegisterScene<scene::ShadowMapping>("Shadow Mapping");
    sceneMenu->RegisterScene<scene::PointShadows>("Point Shadows");
    sceneMenu->RegisterScene<scene::NormalMapping>("Normal Mapping");
    sceneMenu->RegisterScene<scene::ParallaxMapping>("Parallax Mapping");
    sceneMenu->RegisterScene<scene::Hdr>("Hdr");
    sceneMenu->RegisterScene<scene::Bloom>("Bloom");
    sceneMenu->RegisterScene<scene::DeferredShading>("Deferred Shading");
    sceneMenu->RegisterScene<scene::SSAO>("SSAO");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    int events[] = { GLFW_KEY_W , GLFW_KEY_S , GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_Q, GLFW_KEY_E };
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    { 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
       
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (currentTest)
        {
            currentTest->OnUpdate(deltaTime);

            for (auto& event : events)
            {
                if (glfwGetKey(window, event) == GLFW_PRESS)
                {
                    currentTest->OnEvent(event);
                }
            }
            currentTest->OnMouseMovedEvent(mouseX, mouseY);
            currentTest->OnMouseScrolledEvent(offsetX, offsetY);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != sceneMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = sceneMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    delete currentTest;
        if (currentTest != sceneMenu)
           delete sceneMenu;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    mouseX = xpos;
    mouseY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    offsetY = yoffset;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
