//
// Created by 30140770 on 27/02/2026.
//

#ifndef OPENGL1_SHAPES_H
#define OPENGL1_SHAPES_H

#pragma once
#include <map>

struct ShapeData {
    const GLfloat* vertices;
    const GLuint*  indices;
    size_t vertSize;
    size_t indecieSize;
    int vertexCount;
    int indexCount;
};


class Kotlin {
public:
    static constexpr GLfloat vertices[12] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
   };

    static constexpr   GLuint indices[6] = {
        0, 2, 3,
        1, 2, 3
    };
};

class Square {
public:
    static constexpr GLfloat vertices[12] = {
        0.5f,  0.5f, 0.0f,  // Top Right
        0.5f, -0.5f, 0.0f,  // Bottom Right
       -0.5f, -0.5f, 0.0f,  // Bottom Left
   };

    static constexpr GLuint indices[6] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
};

constexpr const char* shapes[] = {
    "Kotlin",
    "Square",
    "Triangle"
};

inline std::map<std::string, ShapeData> shapeMap {
    {"Kotlin",{Kotlin::vertices, Kotlin::indices, sizeof(Kotlin::vertices),sizeof(Kotlin::indices), 12, 6}},
    {"Square",{Square::vertices, Square::indices, sizeof(Kotlin::vertices),sizeof(Kotlin::indices),12, 6}}


};
#endif //OPENGL1_SHAPES_H