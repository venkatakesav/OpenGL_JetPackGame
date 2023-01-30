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

#include "./components/background/background.cpp"
#include "./components/character/character.cpp"
#include "./components/zappers/zappers.cpp"

float x_offset = 0; 
float y_offset = 0; 

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
        // Physics_Engine();
        // transform = glm::translate(transform, glm::vec3(0.0f, in_el, 0.0f));
        // std::cout << "Elevation is " << in_el << std::endl;

        transform = glm::translate(transform, glm::vec3(0.7f + float(-0.0066 * new_Time_T), y_offset, 0.0f));

        if (-0.0066 * new_Time_T < -3)
        {
            std::cout << "Entered" << std::endl;
            new_Time_T = 0;
            x_offset = (float)rand()*0.3f/RAND_MAX;
            y_offset = (float)rand()*0.7f/RAND_MAX - 0.35f;
            std::cout << "x_offset" << x_offset << std::endl;
            std::cout << "y_offset" << y_offset << std::endl;
        }

        // /*Physics Engine -> End*/------------------------------------------------------------------
        bind_transformation(&ourShader);
        render_Zapper();
        // /*Rendering Zappers*/---

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
        std::cout << "Up Ticks: " << up_ticks << std::endl;
    }
    else
    {
        jet = 0;
        up_ticks = 0;
        down_ticks++;
        // std::cout << "Down Ticks: " << down_ticks << std::endl;
    }
}
