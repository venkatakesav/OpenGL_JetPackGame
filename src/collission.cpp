#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include "./shaders/shader.h"
#include <iostream>
// #include "setup.cpp"
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unistd.h>

// Define Two Arrays Character and Zapper

int HasCollided_y = 0;
int HasCollided_x = 0;
int Collisions = 0;
int CollisionOccured = 0;

void CollisionDetection()
{
    // First Update the Character Coordinates ->
    //  -0.80f, -0.60f
    //  -0.80f, -0.93f   //Baseline Coordinates
    //  -0.90f, -0.93f
    //  -0.90f, -0.60f

    // Update Coordinates -> Character
    float char_coord[] = {
        -0.80f, -0.60f + in_el, // Top-Right Corner
        -0.80f, -0.93f + in_el, // Bottom-Right Corner
        -0.90f, -0.93f + in_el, // Bottom-Left Corner
        -0.90f, -0.60f + in_el  // Top-Left Corner
    };

    // Update the Coordinates of the Zapper
    float Zapper_coord[] = {
        0.455f + 0.7f + float(-0.0066 * new_Time_T), 0.500f + y_offset,  // Top-Right Corner
        0.455f + 0.7f + float(-0.0066 * new_Time_T), -0.500f + y_offset, // Bottom-Right Corner
        0.345f + 0.7f + float(-0.0066 * new_Time_T), -0.500f + y_offset, // Bottom-Left Corner
        0.345f + 0.7f + float(-0.0066 * new_Time_T), 0.500f + y_offset   // Top-Left Corner
    };

    // Now that we have both the Character and the Zapper Coordinates in Place -> We can work
    // On Collision Detection
    if (char_coord[2] >= Zapper_coord[6] && Zapper_coord[2] >= char_coord[6])
    {
        if (HasCollided_x != 1)
        {
            // std::cout << "X- Coordinate Collision Detected" << std::endl; // Now -> Collision has been detected};
        }
        HasCollided_x = 1;
        // Collisions++;
    }
    else
    {
        HasCollided_x = 0;
    }

    if (char_coord[1] >= Zapper_coord[5] && Zapper_coord[1] >= char_coord[5])
    {
        if (HasCollided_y != 1)
        {
            // std::cout << "Y- Coordinate Collision Detected" << std::endl; // Now -> Collision has been detected};
        }
        HasCollided_y = 1;
        // Collisions++;
    }
    else
    {
        HasCollided_y = 0;
    }

    // Now If Both X and Y are collided -> Then Post Player Killed !!!!
    if (HasCollided_y == 1 && HasCollided_x == 1)
    {
        if (CollisionOccured != 1)
        {
            std::cout << "Collision Occurred!!!" << std::endl;
        }
        CollisionOccured = 1;
        Collisions++;
    }
    else
    {
        CollisionOccured = 0;
    }
}