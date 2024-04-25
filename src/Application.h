#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "./Physics/Particle.h"
#include "./Physics/Constants.h"
#include <vector>

class Application
{
private:
    bool running = false;
    bool leftMouseButtonDown = false;
    std::vector<Particle *> particles;
    Vec2 pushForce = Vec2(0.0, 0.0);
    Vec2 mouseCurser = Vec2(0.0, 0.0);
    Vec2 anchor = Vec2(0.0, 0.0);
    float restLength = 30;
    float k = 300;

    // SDL_Rect liquid;

public:
    Application() = default;
    ~Application() = default;
    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};

#endif