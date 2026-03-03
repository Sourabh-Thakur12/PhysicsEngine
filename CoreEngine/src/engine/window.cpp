//
// Created by sourabh on 3/4/26.
//

#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


Window::Window(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        throw std::runtime_error( "Failed to initialize GLFW\n");
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_width = width;
    m_height = height;
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error( "Failed to create GLFW window\n");
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
    }

    glViewport(0, 0, m_width, m_height);

    // Successfully loaded OpenGL
    // printf("Loaded OpenGL %d.%d\n", GLFW_VERSION_MAJOR(version), GLFW_VERSION_MINOR(version));

}

float Window::GetAspectRatio() const
{
    return static_cast<float>(m_width)/(m_height);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

