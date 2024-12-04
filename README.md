# OpenGL Collection

This repository contains **OpenGL Collection**, a C++ application inspired by the [Learn OpenGL](https://learnopengl.com/) tutorials. It offers an interactive interface to explore various OpenGL features, test them, and tweak their parameters in real time.

## Features

- **Interactive Interface**: A user-friendly interface to interact with and visualize OpenGL features.
- **Feature Exploration**: Test a wide range of OpenGL concepts, such as:
  - Shading and lighting
  - Texture mapping
  - Model transformations
  - Framebuffers and post-processing effects
- **Customization**: Modify parameters and experiment with settings to observe how they influence rendering.
- **Educational Tool**: Perfect for learning and understanding OpenGL concepts in depth.

## Requirements

- **C++ Compiler**: Compatible with C++17 or later
- **OpenGL Version**: 3.3 or higher
- **Dependencies**:
  - [GLFW](https://www.glfw.org/) (for window and input handling)
  - [GLAD](https://glad.dav1d.de/) (for OpenGL function loading)
  - [Dear ImGui](https://github.com/ocornut/imgui) (for graphical interface)
- **Build System**: CMake

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/yourusername/OpenGL-Collection.git
cd OpenGL-Collection
```

### Build the Project

1. Generate the build files:
   ```bash
   cmake -S . -B build
   ```
2. Compile the project:
   ```bash
   cmake --build build
   ```
3. Run the application:
   ```bash
   ./build/OpenGLCollection
   ```

## Usage

1. Launch the application.
2. Navigate through the interface to select and experiment with OpenGL features.
3. Adjust settings such as shader properties, lighting parameters using the GUI.
4. View real-time results in the rendering window.
