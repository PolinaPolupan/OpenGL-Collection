#include "TextRendering.h"

scene::TextRendering::TextRendering()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader = std::make_shared<Shader>(GetResourcePath("res\\shaders\\Text.shader"));
    fonts = GetResourcesPath({".ttf"}, {"res/fonts"}, true);

    // FreeType
    // --------
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        exit(-1);
    }

    // find path to font
    std::string font_name = GetResourcePath("res\\fonts\\" + fonts[0]).string();

    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        exit(-1);
    }
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        exit(-1);
    }

    // configure VAO/VBO for texture quads
    // -----------------------------------
    VAO = std::make_shared<VertexArray>();
    VertexBuffer::Builder bufferBuilder;
    bufferBuilder
        .SetUsage(GL_DYNAMIC_DRAW)
        .SetData(NULL, sizeof(float) * 6 * 4);

    VBO = std::make_shared<VertexBuffer>(bufferBuilder);

    VertexBufferLayout layout;
    layout.Push<float>(4);

    VAO->AddBuffer(*VBO, layout);

    VAO->Unbind();
    VBO->Unbind();
    shader->Unbind();
}

scene::TextRendering::~TextRendering()
{
    VAO->Unbind();
    VBO->Unbind();
    shader->Unbind();
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void scene::TextRendering::OnUpdate(float deltaTime)
{
	cameraController.OnUpdate(deltaTime);
}

void scene::TextRendering::OnEvent(int event)
{
	cameraController.ProcessInput(event);
}

void scene::TextRendering::OnRender()
{
    glDisable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.Submit(cameraController.GetCamera());
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT));
    shader->Bind();
    shader->SetUniformMat4f("projection", projection);
  
    RenderText(shader, std::string(textBuf), WIDTH/4, HEIGHT/2, glm::vec3(0.5, 0.8f, 0.2f));
}

void scene::TextRendering::OnImGuiRender()
{
    ImGui::InputTextWithHint("Input", "Enter text", textBuf, IM_ARRAYSIZE(textBuf));
    ImGui::SliderInt("Size", &size, 1, 400);

    static int item_current_idx = 0; // Here we store our selection data as an index.
    if (ImGui::BeginListBox("fonts"))
    {
        for (int n = 0; n < fonts.size(); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable((fonts[n]).c_str(), is_selected))
            {
                item_current_idx = n;

                FT_Done_Face(face);

                std::string font_name = GetResourcePath("res\\fonts\\" + fonts[n]).string();
                if (font_name.empty())
                {
                    std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
                    exit(-1);
                }
                if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
                    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
                    exit(-1);
                }
            }
        }
        ImGui::EndListBox();
    }
}

void scene::TextRendering::RenderText(const std::shared_ptr<Shader>& shader, std::string text, float x, float y, glm::vec3 color)
{
    // activate corresponding render state	
    shader->Bind();
    shader->SetUniform3f("textColor", color);
    VAO->Bind();

    std::string font_name = GetResourcePath("res\\fonts\\Roboto-VariableFont_wdth,wght.ttf").string();

    FT_Set_Pixel_Sizes(face, 0, size);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        // Load character glyph 
        
        if (FT_Load_Char(face, *c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        Texture::Parameters parameters;
        Texture::Builder builder;
        builder
            .SetParameters(parameters)
            .SetDataFormat(GL_RED)
            .SetInternalFormat(GL_RED)
            .SetSize(face->glyph->bitmap.width, face->glyph->bitmap.rows)
            .SetBuffer(face->glyph->bitmap.buffer, face->glyph->bitmap.rows * face->glyph->bitmap.width);

        texture = std::make_shared<Texture>(builder);

        // now store character for later use
        character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        Character ch = character;

        float xpos = x + ch.Bearing.x;
        float ypos = y - (ch.Size.y - ch.Bearing.y);

        float w = ch.Size.x;
        float h = ch.Size.y;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        ch.Texture->Bind();
        // update content of VBO memory
        VBO->Bind();
        VBO->SetBufferAt(vertices, sizeof(vertices), 0);
        VAO->Bind();
    
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        ch.Texture->Unbind();
    }
    VAO->Unbind();
}
