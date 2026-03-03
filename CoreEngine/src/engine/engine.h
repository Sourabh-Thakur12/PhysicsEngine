//
// Created by sourabh on 3/4/26.
//

#ifndef PHYSICSENGINE_ENGINE_H
#define PHYSICSENGINE_ENGINE_H

#endif //PHYSICSENGINE_ENGINE_H
#include "../engine/window.h"
#include "../renderer/renderer.h"
class PhysicsWorld;


class Engine
{
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void Run();

private:
    void Update(float dt);
    void Render();
private:
    Window m_window;
    Renderer m_renderer;
    PhysicsWorld* m_world;

    float m_lastFrameTime;
    bool m_running;

};