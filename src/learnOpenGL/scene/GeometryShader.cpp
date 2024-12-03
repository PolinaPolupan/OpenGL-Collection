#include "GeometryShader.h"

scene::GeometryShader::GeometryShader()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float points[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
	};

	houseShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\House.shader"));
	explodeShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Explode.shader"));
	defaultShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Default.shader"));
	normalShader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Normal.shader"));

	VAO = std::make_shared<VertexArray>();
	VBO = std::make_shared<VertexBuffer>(points, sizeof(points));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	VAO->AddBuffer(*VBO, layout);

	mode = Mode::HOUSES;
	modelsPaths = getObjectsPath();
}

scene::GeometryShader::~GeometryShader()
{
	houseShader->Unbind();
	explodeShader->Unbind();
	VAO->Unbind();
	VBO->Unbind();
	objectManager.clear();
}

void scene::GeometryShader::OnUpdate(float deltaTime)
{
	cameraController.OnUpdate(deltaTime);
	objectManager.update();
}

void scene::GeometryShader::OnMouseMovedEvent(double posX, double posY)
{
	cameraController.rotateCamera(posX, posY);
}

void scene::GeometryShader::OnMouseScrolledEvent(double offsetX, double offsetY)
{
	cameraController.zoomCamera(offsetX, offsetY);
}

void scene::GeometryShader::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (mode) {
	case HOUSES: { OnRenderHouses(); break; }
	case EXPLODE: { OnRenderExplode(); break; }
	case NORMALS: { OnRenderNormals(); break; }
	}
}

void scene::GeometryShader::OnImGuiRender()
{
	bool opened = mode == Mode::EXPLODE || mode == Mode::NORMALS;

	if (opened) {
		LoadObjectsList(modelsPaths, objectManager);
	}
		
	ImGui::SliderFloat("magnitude", &magnitude, 0.f, 1.f);
	if (ImGui::Button("houses")) {
		mode = Mode::HOUSES;
	}
	if (ImGui::Button("explode")) {
		mode = Mode::EXPLODE;
	}
	if (ImGui::Button("normals")) {
		mode = Mode::NORMALS;
	}
}

void scene::GeometryShader::OnEvent(int event)
{
	cameraController.processInput(event);
}

void scene::GeometryShader::OnRenderHouses()
{
	houseShader->Bind();
	VAO->Bind();
	glDrawArrays(GL_POINTS, 0, 4);

	houseShader->Unbind();
	VAO->Unbind();
}

void scene::GeometryShader::OnRenderExplode()
{
	renderer.Submit(cameraController.getCamera());
	// configure transformation matrices
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 1.0f, 100.0f);
	glm::mat4 view = cameraController.getViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	
	explodeShader->Bind();
	explodeShader->SetUniformMat4f("projection", projection);
	explodeShader->SetUniformMat4f("view", view);
	explodeShader->SetUniformMat4f("model", model);

	// add time component to geometry shader in the form of a uniform
	explodeShader->SetUniform1f("time", static_cast<float>(glfwGetTime()));

	// draw model
	for (auto& o : objectManager.getObjects())
	{
		explodeShader->Bind();
		renderer.RenderObject(*o, *explodeShader);
	}

	explodeShader->Unbind();
}

void scene::GeometryShader::OnRenderNormals()
{
	renderer.Submit(cameraController.getCamera());
	// configure transformation matrices
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 1.0f, 100.0f);
	glm::mat4 view = cameraController.getViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);

	defaultShader->Bind();
	defaultShader->SetUniformMat4f("projection", projection);
	defaultShader->SetUniformMat4f("view", view);
	defaultShader->SetUniformMat4f("model", model);

	// draw model
	for (auto& o : objectManager.getObjects())
	{
		defaultShader->Bind();
		renderer.RenderObject(*o, *defaultShader);
	}


	normalShader->Bind();
	normalShader->SetUniform1f("magnitude", magnitude);
	normalShader->SetUniformMat4f("projection", projection);
	normalShader->SetUniformMat4f("view", view);
	normalShader->SetUniformMat4f("model", model);

	// draw model
	for (auto& o : objectManager.getObjects())
	{
		normalShader->Bind();
		renderer.RenderObject(*o, *normalShader);
	}
}
