//
// Created by sourabh on 3/4/26.
//

#ifndef PHYSICSENGINE_WINDOW_H
#define PHYSICSENGINE_WINDOW_H
#include "GLFW/glfw3.h"

#endif //PHYSICSENGINE_WINDOW_H

struct  GLFWindow; // forward declaration

class Window
{
    public:
    Window(int width, int height, const char* title);
    ~Window();

    void PollEvents();
    void SwapBuffers();

    bool ShouldClose() const;

    float GetAspectRatio() const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;

};