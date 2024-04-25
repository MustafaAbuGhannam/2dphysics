#include "Application.h"
#include "./Physics/Force.h"
#include <iostream>

bool Application::IsRunning()
{
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup()
{
    running = Graphics::OpenWindow();

    this->anchor = Vec2(Graphics::Width() / 2.0, 30);
    Particle *bob = new Particle(Graphics::Width() / 2.0, Graphics::Height() / 2.0, 2.0);
    bob->radius = 10;
    this->particles.push_back(bob);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            if (event.key.keysym.sym == SDLK_UP)
                this->pushForce.y = -50 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_RIGHT)
                this->pushForce.x = 50 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_DOWN)
                this->pushForce.y = 50 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_LEFT)
                this->pushForce.x = -50 * PIXELS_PER_METER;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP)
                this->pushForce.y = 0;
            if (event.key.keysym.sym == SDLK_RIGHT)
                this->pushForce.x = 0;
            if (event.key.keysym.sym == SDLK_DOWN)
                this->pushForce.y = 0;
            if (event.key.keysym.sym == SDLK_LEFT)
                this->pushForce.x = 0;
            break;
        case SDL_MOUSEMOTION:
            this->mouseCurser.x = event.motion.x;
            this->mouseCurser.y = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:

            if (!this->leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
            {
                this->leftMouseButtonDown = true;
                int x, y;
                SDL_GetMouseState(&x, &y);
                this->mouseCurser.x = x;
                this->mouseCurser.y = y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (this->leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
            {
                this->leftMouseButtonDown = false;
                Vec2 impulseDirection = (this->particles[0]->postion - mouseCurser).UnitVector();
                float impulseMagnitude = (this->particles[0]->postion - mouseCurser).Magnitude() * 5;

                this->particles[0]->velocity = impulseDirection * impulseMagnitude;
            }
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update()
{
    static int timePreviousFrame;
    int timeToWait = MILLSECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);

    if (timeToWait > 0)
    {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;

    if (deltaTime > 0.016)
    {
        deltaTime = 0.016;
    }

    timePreviousFrame = SDL_GetTicks();

    // attraction force
    // Vec2 attraction = Force::GenerateGravitationalForce(*this->particles[0], *this->particles[1], 1000.0, 5, 100);
    // this->particles[0]->addForce(attraction);
    // this->particles[1]->addForce(-attraction);

    for (auto particle : this->particles)
    {

        // apply wind force to all particles
        // Vec2 wind = Vec2(.2 * PIXELS_PER_METER, 0.0);
        // particle->addForce(wind);

        // apply weight force to all particles
        Vec2 weight = Vec2(0.0, 9.8 * PIXELS_PER_METER * particle->mass);
        particle->addForce(weight);

        // apply a force by keyboard arrow key press
        particle->addForce(this->pushForce);

        // apply friction force
        // Vec2 friction = Force::GenerateFrictionForce(*particle, 20);
        // particle->addForce(friction);

        // apply drag force to all particles if nessecary
        Vec2 drag = Force::GenerateDragForce(*particle, 0.001);
        particle->addForce(drag);
    }

    // apply stringForce to particle connected to the anchor

    Vec2 springForce = Force::GenerateSpringForce(*particles[0], this->anchor, this->restLength, this->k);
    particles[0]->addForce(springForce);

    for (auto particle : this->particles)
    {
        particle->integrate(deltaTime);
    }

    // check if we got to screen bondres;
    for (auto particle : this->particles)
    {
        if (particle->postion.y + particle->radius >= Graphics::Height())
        {
            particle->postion.y = Graphics::Height() - particle->radius;
            particle->velocity.y = particle->velocity.y * -0.9;
        }
        else if (particle->postion.y - particle->radius <= 0)
        {
            particle->postion.y = particle->radius;
            particle->velocity.y = particle->velocity.y * -0.9;
        }
        if (particle->postion.x + particle->radius >= Graphics::Width())
        {
            particle->postion.x = Graphics::Width() - particle->radius;
            particle->velocity.x = particle->velocity.x * -0.9;
        }

        else if (particle->postion.x - particle->radius <= 0)
        {
            particle->postion.x = particle->radius;
            particle->velocity.x = particle->velocity.x * -0.9;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render()
{
    Graphics::ClearScreen(0xFF056263);

    if (this->leftMouseButtonDown)
    {
        Graphics::DrawLine(particles[0]->postion.x, particles[0]->postion.y, mouseCurser.x, mouseCurser.y, 0xFF24238A);
    }

    // draw the anchor
    Graphics::DrawFillCircle(anchor.x, anchor.y, 5, 0xFF001155);

    // draw anchor bob
    Graphics::DrawFillCircle(particles[0]->postion.x, particles[0]->postion.y, particles[0]->radius, 0xFF001155);

    // draw anchor spring

    Graphics::DrawLine(anchor.x, anchor.y, particles[0]->postion.x, particles[0]->postion.y, 0xFF313131);

    // render all particles
    //  for (auto particle : this->particles)
    //  {
    //      Graphics::DrawFillCircle(particle->postion.x, particle->postion.y, particle->radius, 0xFFFFFFFF);
    //  }
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy()
{
    // TODO: destroy all objects in the scene
    for (auto particle : this->particles)
    {
        delete particle;
    }
    Graphics::CloseWindow();
}