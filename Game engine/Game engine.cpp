#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <cmath>
#include <vector>
#include <iostream>

// Vertex Shader
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";

// Generate circle vertices
std::vector<float> generateCircle(float cx, float cy, float r, int segments) {
    std::vector<float> verts;
    verts.push_back(cx); verts.push_back(cy); verts.push_back(0.0f); // center
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * 3.14159265358979323846 * i / segments;
        verts.push_back(cx + r * cos(angle));
        verts.push_back(cy + r * sin(angle));
        verts.push_back(0.0f);
    }
    return verts;
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Moving Circle", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Setup VAO/VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float time = glfwGetTime();
        float x = 0.5f * sin(time);
        float y = 0.0f;
        float radius = 0.2f;

        std::vector<float> circle = generateCircle(x, y, radius, 50);
        glBufferData(GL_ARRAY_BUFFER, circle.size() * sizeof(float), circle.data(), GL_DYNAMIC_DRAW);

        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.size() / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
