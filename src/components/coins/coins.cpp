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

float vertices_3[] = {
    // Position (x, y, z)  //Colors (arbitrary)  //Textures(x, y)
    0.455f, 0.500f , 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.455f, -0.500f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.345f, -0.500f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.345f, 0.500f , 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
unsigned int indices_3[] = {
    0, 1, 3, // second triangle
    1, 2, 3  // first triangle
};

unsigned int VBO_3, VAO_3, EBO_3;
unsigned int texture_3;

void coins_init(){

    glGenVertexArrays(1, &VAO_3);
    glGenBuffers(1, &VBO_3);
    glGenBuffers(1, &EBO_3);

    glBindVertexArray(VAO_3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_3), vertices_3, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_3), indices_3, GL_STATIC_DRAW);

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
    glGenTextures(1, &texture_3);
    glBindTexture(GL_TEXTURE_2D, texture_3); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // int width, height, nrChannels;
    char path_3[100];
    strcpy(path_3, "src/components/coins/coins.png");
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data_3 = stbi_load(path_3, &width, &height, &nrChannels, 0);
    if (data_3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data_3);
}

void render_coins()
{
    glBindTexture(GL_TEXTURE_2D, texture_3);

    glBindVertexArray(VAO_3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}