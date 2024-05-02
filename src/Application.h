#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "./Physics/Body.h"
#include "./Physics/Constants.h"
#include <vector>

class Application
{
private:
    bool running = false;
    bool leftMouseButtonDown = false;
    std::vector<Body *> bodies;
    Vec2 pushForce = Vec2(0.0, 0.0);
    Vec2 mouseCurser = Vec2(0.0, 0.0);

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