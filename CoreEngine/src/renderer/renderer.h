//
// Created by sourabh on 3/4/26.
//

#ifndef PHYSICSENGINE_RENDERER_H
#define PHYSICSENGINE_RENDERER_H

#endif //PHYSICSENGINE_RENDERER_H

#include <vector>

//TODO: move to math utils
struct Vec2
{
    float x;
    float y;
};

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();

    void BeginFrame();
    void EndFrame();

    void DrawLine(const Vec2 &pointA, const Vec2 &pointB);
    void DrawCircle(const Vec2 &center, float radius);

private:
    void CreateShader();
    void CreateBuffers();

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_shader;

    std::vector<float> m_vertexBuffer;

    int m_screenWidth;
    int m_screenHeight;

};