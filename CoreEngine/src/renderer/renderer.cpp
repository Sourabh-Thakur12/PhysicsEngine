//
// Created by sourabh on 3/4/26.
//

#include "renderer.h"
#include "glad/glad.h"
#include <iostream>

Renderer::Renderer(int width, int height): m_screenWidth(width), m_screenHeight(height)
{
    CreateShader();
    CreateBuffers();
}

void Renderer::CreateShader()
{
    const char* vertexShader = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 uProjection;

void main(){
   // gl_Position = uProjection * vec4(aPos, 1.0);
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

    const char* fragmentShader = R"(
#version 330 core
out vec4 FragColor;
void main(){
FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, nullptr);
    glCompileShader(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, nullptr);
    glCompileShader(fs);

    m_shader = glCreateProgram();
    glAttachShader(m_shader, vs);
    glAttachShader(m_shader, fs);
    glLinkProgram(m_shader);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Renderer::CreateBuffers()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10000, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Renderer::BeginFrame()
{
    m_vertexBuffer.clear();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawLine(const Vec2& pointA, const Vec2& pointB)
{
    m_vertexBuffer.push_back(pointA.x);
    m_vertexBuffer.push_back(pointA.y);

    m_vertexBuffer.push_back(pointB.x);
    m_vertexBuffer.push_back(pointB.y);
}


void Renderer::EndFrame()
{
    if (m_vertexBuffer.empty()) return;

    glUseProgram(m_shader);

    float left = 0.0f;
    float right = (float)m_screenWidth;
    float bottom = 0.0f;
    float top = (float)m_screenHeight;

    float proj[16] = {
        2/(right-left), 0, 0, 0,
        0, 2/(top-bottom), 0, 0,
        0, 0, -1, 0,
        -(right + left)/(right-left),
        -(top + bottom)/(top-bottom),
        0,
        1
    };

    int loc = glGetUniformLocation(m_shader, "uProjection");

    glUniformMatrix4fv(loc, 1, GL_FALSE, proj);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexBuffer.size() * sizeof(float), m_vertexBuffer.data());
    glDrawArrays(GL_LINES, 0, m_vertexBuffer.size()/2);
    glBindVertexArray(0);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shader);
}



