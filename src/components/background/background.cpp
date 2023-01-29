#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "./../../shaders/shader.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

unsigned int VBO, VAO, EBO;
int width, height, nrChannels;
unsigned int texture;
glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

int new_Time = 0;
int flag = 0;
int count = 0;

float vertices[] = {
    // positions          // colors           // texture coords
    -0.33f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
    -0.33f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // top left
    -0.33f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // top left -> 4
    -0.33f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // bottom left -> 5
    0.33f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right -> 6
    0.33f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right -> 7
    0.33f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left -> 8
    0.33f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left -> 9
    1.00f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right -> 10
    1.00f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right -> 11
    1.00f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left -> 12
    1.00f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left -> 13
    1.66f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right -> 14
    1.66f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right -> 15
};
unsigned int indices[] = {
    0, 1, 3,    // first triangle
    1, 2, 3,    // second triangle
    4, 5, 6,    // Thrird Triangle
    5, 6, 7,    // 4th Triangle
    8, 9, 10,   // 5th Triangle
    9, 10, 11,  // 6th Triangle
    12, 13, 14, // 7th Triangle
    13, 14, 15  // 8th Triangle
};

void back_init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture
    // -------------------------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    char path[100];
    strcpy(path, "src/components/background/H2.png");
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void RenderBackground()
{
    // bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // /*Render The BackGround*/------------------------------------------------------

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
}

void render_back_main()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
}