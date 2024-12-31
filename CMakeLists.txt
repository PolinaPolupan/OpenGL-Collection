cmake_minimum_required(VERSION 3.15...3.30)
project(LearnOpenGL LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES
src/learnOpenGL/Application.cpp
src/learnOpenGL/Renderer.cpp
"src/learnOpenGL/scene/BasicLighting.cpp"
"src/learnOpenGL/scene/Blending.cpp"
"src/learnOpenGL/scene/CoordinateSystem.cpp"
"src/learnOpenGL/scene/ModelLoading.cpp"
"src/learnOpenGL/scene/Scene.cpp"
"src/learnOpenGL/scene/ClearColor.cpp"
"src/learnOpenGL/scene/Texture2D.cpp"
"src/learnOpenGL/scene/FaceCulling.cpp"
"src/learnOpenGL/scene/Framebuffers.cpp"
"src/learnOpenGL/scene/Cubemaps.cpp"
"src/learnOpenGL/scene/AdvancedGLSL.cpp"
"src/learnOpenGL/scene/GeometryShader.cpp"
"src/learnOpenGL/scene/Instancing.cpp"
"src/learnOpenGL/scene/Antialiasing.cpp"
"src/learnOpenGL/scene/AdvancedLighting.cpp"
"src/learnOpenGL/scene/GammaCorrection.cpp"
"src/learnOpenGL/scene/ShadowMapping.cpp"
"src/learnOpenGL/scene/PointShadows.cpp"
"src/learnOpenGL/scene/NormalMapping.cpp"
"src/learnOpenGL/scene/ParallaxMapping.cpp"
"src/learnOpenGL/scene/DeferredShading.cpp"
"src/learnOpenGL/scene/SSAO.cpp"
"src/learnOpenGL/scene/Hdr.cpp"
"src/learnOpenGL/scene/PBR.cpp"
"src/learnOpenGL/core/Lights.cpp"
"src/learnOpenGL/core/Mesh.cpp"
"src/learnOpenGL/core/Model.cpp"
"src/learnOpenGL/core/ObjectManager.cpp"
"src/learnOpenGL/core/Shader.cpp"
src/learnOpenGL/core/IndexBuffer.cpp
src/learnOpenGL/core/Texture.cpp
src/learnOpenGL/core/VertexArray.cpp
src/learnOpenGL/core/VertexBuffer.cpp
)

set(IMGUI_SOURCE
src/ext/imgui/imgui.cpp
src/ext/imgui/imgui_demo.cpp
src/ext/imgui/imgui_draw.cpp
src/ext/imgui/imgui_tables.cpp
src/ext/imgui/imgui_widgets.cpp
src/ext/imgui/backends/imgui_impl_opengl3.cpp
src/ext/imgui/backends/imgui_impl_glfw.cpp
src/learnOpenGL/utils/FileUtils.cpp
src/learnOpenGL/utils/Utils.cpp
src/learnOpenGL/scene/Bloom.cpp
)

set(STB_IMAGE_SOURCE
src/ext/stb_image/stb_image.cpp
)

add_executable(LearnOpenGL ${SOURCE_FILES} ${IMGUI_SOURCE} ${STB_IMAGE_SOURCE})

add_subdirectory(src/ext/glad EXCLUDE_FROM_ALL)
add_subdirectory(src/ext/glfw EXCLUDE_FROM_ALL)
add_subdirectory(src/ext/glm EXCLUDE_FROM_ALL)
add_subdirectory(src/ext/assimp EXCLUDE_FROM_ALL)

target_include_directories(LearnOpenGL
PRIVATE src/ext/assimp/include
PRIVATE src/ext/glfw-3.4/include
PRIVATE src/ext/glm/glm
PRIVATE src/ext/imgui
PRIVATE src/ext/imgui/backends
PRIVATE src/ext/stb_image
PRIVATE src/ext/assimp/include
PRIVATE src/ext/stb_image
PRIVATE src/ext/glad/include
PRIVATE src/learnOpenGL
PRIVATE src/learnOpenGL/core
PRIVATE src/learnOpenGL/scene
PRIVATE src/learnOpenGL/widgets
PRIVATE src/learnOpenGL/utils
PRIVATE src/learnOpenGL/scene/include
)

target_link_libraries(LearnOpenGL PRIVATE glad)
target_link_libraries(LearnOpenGL PRIVATE glfw)
target_link_libraries(LearnOpenGL PRIVATE glm)
target_link_libraries(LearnOpenGL PRIVATE assimp)

target_compile_definitions(LearnOpenGL PRIVATE PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_precompile_headers(LearnOpenGL PRIVATE src/learnOpenGL/scene/include/pch.h)