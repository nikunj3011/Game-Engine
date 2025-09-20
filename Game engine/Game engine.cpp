// Game engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "glad/include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
    std::cout << "Initializing engine..." << std::endl;

    // Initialize GLFW and OpenGL
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "My Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    std::cout << "Window created successfully." << std::endl;

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        std::cout << "Frame start..." << std::endl;

        // Input, update, render
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

        std::cout << "Frame end." << std::endl;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
