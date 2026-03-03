//
// Created by sourabh on 3/4/26.
//

#include "engine.h"
#include <iostream>
#include <chrono>

Engine::Engine(int width, int height, const char* title): m_window(width, height, title), m_renderer(width, height), m_running(true)
{
}

void Engine::Run()
{
    using clock = std::chrono::high_resolution_clock;

    auto lastTime = clock::now();

    while (!m_window.ShouldClose())
    {
        auto now = clock::now();

        float dt = std::chrono::duration<float>(now - lastTime).count();

        lastTime = now;

        Update(dt);
        Render();

        m_window.SwapBuffers();
        m_window.PollEvents();

    }
}

void Engine::Update(float dt)
{

}

void Engine::Render()
{
    m_renderer.BeginFrame();
    std::cout<<"Rendering\n";

    m_renderer.DrawLine({-0.5f, -0.5f
}, {0.5f, 0.5f});

    m_renderer.EndFrame();
}

Engine::~Engine()
{

}

