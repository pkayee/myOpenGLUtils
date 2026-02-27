//
// Created by 30140770 on 27/02/2026.
//

#ifndef OPENGL1_SHAPES_H
#define OPENGL1_SHAPES_H

#pragma once

class Kotlin {
public:
    GLfloat vertices[12] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
   };

    GLuint indices[6] = {
        0, 2, 3,
        1, 2, 3
    };
};

class Square {
public:
    GLfloat vertices[12] = {
        0.5f,  0.5f, 0.0f,  // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
       -0.5f, -0.5f, 0.0f,  // Bottom Left
   };

    GLuint indices[6] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
};

#endif //OPENGL1_SHAPES_H