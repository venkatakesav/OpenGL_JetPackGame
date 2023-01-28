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


// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void Physics_Engine();

int new_Time = 0;
int flag = 0;
int count = 0;

/*Initial Elevation*/
float in_el = 0;
/*JetPack Off*/
int jet = 0;
/*Number of moments of Upward acc*/
int up_ticks = 0; 
/*Number of moments of Downward acc*/
int down_ticks = 0; 
/*Velocity = 0*/
float vel = 0; 

int main()
{
    GLFWwindow *window = Setup();

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("src/shaders/shader.vs", "src/shaders/shader.fs"); // you can name your shader files however you like

    back_init();
    character_init();

    // render loop
    // ----------- For Level -1 ------------
    while (!glfwWindowShouldClose(window) && count < 10)
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

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // /*Render The BackGround*/------------------------------------------------------
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

        if (new_Time < 100)
        {
            // Create Transformations
            transform = glm::translate(transform, glm::vec3(float(-0.0033 * new_Time), 0.0f, 0.0f));
            // std:: cout << "X Coordinate is: " << -0.0033*new_Time << std::endl;
            // usleep(100);
            new_Time++;
        }
        else if (flag == 1)
        {
            transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
            new_Time = 0;
            count++;
        }

        if (new_Time == 100)
        {
            flag = 1;
            usleep(10000);
        }

        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

        // /*Render BackGround Complete*/------------------------------------------------------
        // /*Render Character*/----------------------------------------------------------------
        transform = glm::mat4(1.0f);
        // /*Physics Engine*/------------------------------------------------------------------
        // std::cout << "JetPack is " << jet << std::endl;
        Physics_Engine();
        transform = glm::translate(transform, glm::vec3(0.0f, in_el, 0.0f));
        // std::cout << "Elevation is " << in_el << std::endl;

        // /*Physics Engine -> End*/------------------------------------------------------------------
        transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindTexture(GL_TEXTURE_2D, texture_1);

        glBindVertexArray(VAO_1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // /*Rendering Character Complete*/----------------------------------------------------------------

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
        std:: cout << "Up Ticks: "<< up_ticks << std:: endl;
    }
    else
    {
        jet = 0;
        up_ticks = 0; 
        down_ticks++;
        std:: cout << "Down Ticks: "<< down_ticks << std:: endl;
    }
}

void Physics_Engine()
{
    // Case 1 if Jet is active and player is on ground

    if (jet == 1)
    {
        if (in_el <= 1.6 && in_el >= 0.0f)
        {
            in_el = in_el + vel*(up_ticks) +0.0000005*(up_ticks)*(up_ticks); // Basically hover over the ground
            vel = vel + 0.0000010*(up_ticks);
        }
        else if (in_el > 1.6f)
        {
            in_el = 1.6f;
            up_ticks = 0; 
            vel = 0; 
        }else if(in_el < 0.0f){
            in_el = 0; 
            vel = 0;
        }
    }
    else
    {
        if (in_el >= 0 && in_el <= 1.6f)
        {
            in_el = in_el + vel*(down_ticks) - 0.00000025*(down_ticks)*(down_ticks); // Basically hover over the ground
            vel = vel - 0.0000005*(down_ticks);
        }
        else if (in_el < 0)
        {
            in_el = 0;
            down_ticks = 0;
            vel = 0; 
        }else if(in_el > 1.6f){
            in_el = 1.6f; 
            vel = 0;
        }
    }
}
