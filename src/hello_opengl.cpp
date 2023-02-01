#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include "./shaders/shader.h"
#include <iostream>
#include "setup.cpp"
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unistd.h>

float x_offset = 0;
float y_offset = 0;
float x_offset_c = 0;
float y_offset_c = 0;
float new_Time_T_C = 0;

int flag_pop = 0;
int GameOver = 0; // Whenever GameOver = 100 -> End Game
int flag_hor = 0;

int Total_Length = 0; 

#include "./components/background/background.cpp"
#include "./components/character/character.cpp"
#include "./components/zappers/zappers.cpp"
#include "./components/coins/coins.cpp"
#include "./collission.cpp"

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

// settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
unsigned int VAO_5, VBO_5;

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void bind_transformation(Shader *ourShader)
{
    unsigned int transformLoc = glGetUniformLocation((*ourShader).ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

int main()
{
    GLFWwindow *window = Setup();

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("src/shaders/shader.vs", "src/shaders/shader.fs"); // you can name your shader files however you like

    back_init();
    character_init();
    zappers_init();
    coins_init();

    // OpenGL state
    // ------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // compile and setup the shader
    // ----------------------------
    Shader shader("/home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/text.vs", "/home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/text.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    // find path to font
    std::string font_name = "/home/venkata/Sem4/CG_New/Spring2023-CG-Resources-main/Boilerplate2023/fonts/Antonio-Bold.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return -1;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    else
    {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture_5;
            glGenTextures(1, &texture_5);
            glBindTexture(GL_TEXTURE_2D, texture_5);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture_5,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)};
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &VAO_5);
    glGenBuffers(1, &VBO_5);
    glBindVertexArray(VAO_5);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_5);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    // ----------- For Level -1 ------------
    while (!glfwWindowShouldClose(window) && count < 100 && GameOver < 15)
    {
        // Initially Pressed or not ->
        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render container
        ourShader.use();
        RenderBackground();
        bind_transformation(&ourShader);
        render_back_main();

        // /*Render BackGround Complete*/------------------------------------------------------
        // /*Render Character*/----------------------------------------------------------------
        transform = glm::mat4(1.0f);
        // /*Physics Engine*/------------------------------------------------------------------
        // std::cout << "JetPack is " << jet << std::endl;
        Physics_Engine();
        transform = glm::translate(transform, glm::vec3(0.0f, in_el, 0.0f));
        // std::cout << "Elevation is " << in_el << std::endl;

        // /*Physics Engine -> End*/------------------------------------------------------------------
        bind_transformation(&ourShader);
        render_Img();
        // /*Rendering Character Complete*/----------------------------------------------------------------

        // /*Render Zappers*/----------------------------------------------------------------
        transform = glm::mat4(1.0f);
        // /*Physics Engine*/------------------------------------------------------------------
        // std::cout << "JetPack is " << jet << std::endl;
        Physics_Engine();
        // transform = glm::translate(transform, glm::vec3(0.0f, in_el, 0.0f));
        // std::cout << "Elevation is " << in_el << std::endl;
        // /*Physics Engine -> End*/------------------------------------------------------------------
        // ourShader.use();
        Zapper_Setup();
        bind_transformation(&ourShader);
        render_Zapper();
        // // /*Rendering Zappers Complete*/---
        // // /*Rendering Zappers Complete*/---------------------------------------------------------

        transform = glm::mat4(1.0f);

        if (flag_pop == 1)
        {
            transform = glm::translate(transform, glm::vec3(-10.0f, 0, 0));
        }
        transform = glm::translate(transform, glm::vec3(1.3f + float(-0.0066 * new_Time_T_C) + x_offset_c, y_offset_c, 0.0f));

        // If Collision Happens Set Flag to 1 -> Whenever Flag = 1 -> Render -2.0 + Current Coordinates
        // Then No Possibility of it showing and whenever -0.0066*new_Time_T_C is less than -3 (Re-Rendering)
        // Set Flag to 1
        if (CollisionOccured_C == 1)
        {
            if (flag_pop != 1)
            {
                flag_pop = 1;
                std::cout << "flag_pop: set" << std::endl;
            }
        }

        if (-0.0066 * new_Time_T_C < -3.0)
        {
            // std::cout << "Entered" << std::endl;
            new_Time_T_C = 0;
            x_offset_c = (float)rand() * 0.6f / RAND_MAX;
            y_offset_c = (float)rand() * 1.4f / RAND_MAX - 0.70f;
            // std::cout << "x_offset" << x_offset_c << std::endl;
            // std::cout << "y_offset" << y_offset << std::endl;
            if (y_offset_c < 0)
            {
                // std::cout << "Horizontal Spawn" << std::endl;
                // Make Horizontal equal to 1 -> That is The Current Zapper is going to be rotated by 90 degrees
                flag_hor = 1;
            }
            else
            {
                flag_hor = 0;
            }
            flag_pop = 0;
            std::cout << "flag_pop: reset" << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, texture_3);
        ourShader.use();
        bind_transformation(&ourShader);
        glBindVertexArray(VAO_3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Collision Detection For Both Zappers and Coins
        CollisionDetection();

        /*Reset all the transformations to originals -------------------------------------------*/
        transform = glm::mat4(1.0f);
        /*Reset all the transformations to originals -------------------------------------------*/

        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Update Coins ->

        std::string Level = "Level is ";
        std::string level_no = std::to_string(level);
        Level = Level + level_no;

        std::string Header = "Dist: ";
        std::string Distance = std::to_string(Total_Length/10);
        Header = Header + Distance;

        std::string Header_Bot = " Coins: ";
        std::string Coins = std::to_string(Collisions_C*8);
        Header_Bot = Header_Bot + Coins;

        Header = Header + Header_Bot; 

        RenderText(shader, Level, 2200.0f, 700.0f, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));
        RenderText(shader, Header, 50.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

        if (CollisionOccured == 1)
        {
            RenderText(shader, "Game Over!!!", 700.0f, 350.0f, 5.0f, glm::vec3(0.5, 0.8f, 0.2f));
            GameOver++;
        }

        // std::cout << GameOver << std::endl;

        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        // std::cout << "1 Pressed" << std::endl;
        jet = 1;
        up_ticks++;
        down_ticks = 0;
        // std::cout << "Up Ticks: " << up_ticks << std::endl;
    }
    else
    {
        jet = 0;
        up_ticks = 0;
        down_ticks++;
        // std::cout << "Down Ticks: " << down_ticks << std::endl;
    }
}

void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO_5);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO_5);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}