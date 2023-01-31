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

int flag_hor = 0;

#include "./components/background/background.cpp"
#include "./components/character/character.cpp"
#include "./components/zappers/zappers.cpp"
#include "./components/coins/coins.cpp"
#include "./collission.cpp"

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

    // render loop
    // ----------- For Level -1 ------------
    while (!glfwWindowShouldClose(window) && count < 100)
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
        ourShader.use();
        Zapper_Setup();
        bind_transformation(&ourShader);
        render_Zapper();
        // /*Rendering Zappers Complete*/---
        // /*Rendering Zappers Complete*/---------------------------------------------------------

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(1.3f + float(-0.0066 * new_Time_T_C) + x_offset_c, y_offset_c, 0.0f));

        if (-0.0066 * new_Time_T_C < -3.0)
        {
            // std::cout << "Entered" << std::endl;
            new_Time_T_C = 0;
            x_offset_c = (float)rand() * 0.6f / RAND_MAX;
            y_offset_c = (float)rand() * 1.4f / RAND_MAX - 0.70f;
            std::cout << "x_offset" << x_offset_c << std::endl;
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
