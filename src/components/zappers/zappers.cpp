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

float vertices_2[] = {
    // Position (x, y, z)  //Colors (arbitrary)  //Textures(x, y)
    0.455f, 0.500f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.455f, -0.500f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.345f, -0.500f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.345f, 0.500f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
unsigned int indices_2[] = {
    0, 1, 3, // second triangle
    1, 2, 3  // first triangle
};

unsigned int VBO_2, VAO_2, EBO_2;
unsigned int texture_2;

void zappers_init()
{

    glGenVertexArrays(1, &VAO_2);
    glGenBuffers(1, &VBO_2);
    glGenBuffers(1, &EBO_2);

    glBindVertexArray(VAO_2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_2), indices_2, GL_STATIC_DRAW);

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
    glGenTextures(1, &texture_2);
    glBindTexture(GL_TEXTURE_2D, texture_2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // int width, height, nrChannels;
    char path_2[100];
    strcpy(path_2, "src/components/zappers/ZapWithoutBack.png");
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data_2 = stbi_load(path_2, &width, &height, &nrChannels, 0);
    if (data_2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data_2);
}

void Zapper_Setup()
{
    transform = glm::translate(transform, glm::vec3(0.7f + float(-0.0066 * new_Time_T), y_offset, 0.0f));

    if (-0.0066 * new_Time_T < -3)
    {
        // std::cout << "Entered" << std::endl;
        new_Time_T = 0;
        x_offset = (float)rand() * 0.3f / RAND_MAX;
        y_offset = (float)rand() * 0.7f / RAND_MAX - 0.35f;
        // std::cout << "x_offset" << x_offset << std::endl;
        // std::cout << "y_offset" << y_offset << std::endl;
        if (y_offset < 0)
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
}

void render_Zapper()
{
    glBindTexture(GL_TEXTURE_2D, texture_2);

    glBindVertexArray(VAO_2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}