#include "Application.h"
#include "./Physics/Force.h"
#include "./Physics/Collision.h"
#include "./Physics/Contact.h"
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

    // Body *p1 = new Body(BoxShape(200, 100), Graphics::Width() / 2.0, Graphics::Height() / 2.0, 2.0);
    // this->bodies.push_back(p1);

    Body *bigCirlce = new Body(CircleShape(100), 100, 100, 1.0);
    Body *smallCirlce = new Body(CircleShape(50), 500, 100, 1.0);
    this->bodies.push_back(bigCirlce);
    this->bodies.push_back(smallCirlce);
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
        // case SDL_MOUSEMOTION:
        //     this->mouseCurser.x = event.motion.x;
        //     this->mouseCurser.y = event.motion.y;
        //     break;
        // case SDL_MOUSEBUTTONDOWN:

        //     if (!this->leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
        //     {
        //         this->leftMouseButtonDown = true;
        //         int x, y;
        //         SDL_GetMouseState(&x, &y);
        //         this->mouseCurser.x = x;
        //         this->mouseCurser.y = y;
        //     }
        //     break;
        // case SDL_MOUSEBUTTONUP:
        //     if (this->leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT)
        //     {
        //         this->leftMouseButtonDown = false;
        //         Vec2 impulseDirection = (this->bodies[0]->postion - mouseCurser).UnitVector();
        //         float impulseMagnitude = (this->bodies[0]->postion - mouseCurser).Magnitude() * 5;

        //         this->bodies[0]->velocity = impulseDirection * impulseMagnitude;
        //     }
        //     break;
        case SDL_MOUSEMOTION:
            int x, y;
            SDL_GetMouseState(&x, &y);
            this->bodies[0]->postion = Vec2(x, y);
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update()
{
    // temp adding clear screen for debugging reasons
    Graphics::ClearScreen(0x0);

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
    // Vec2 attraction = Force::GenerateGravitationalForce(*this->bodies[0], *this->bodies[1], 1000.0, 5, 100);
    // this->bodies[0]->addForce(attraction);
    // this->bodies[1]->addForce(-attraction);

    for (auto body : this->bodies)
    {

        // apply wind force to all bodies
        // Vec2 wind = Vec2(20 * PIXELS_PER_METER, 0.0);
        // body->AddForce(wind);

        // apply weight force to all bodies
        // Vec2 weight = Vec2(0.0, 9.8 * PIXELS_PER_METER * body->mass);
        // body->AddForce(weight);

        // apply torque;
        // float torque = 200;
        // body->AddTorque(torque);

        // apply a force by keyboard arrow key press
        // body->AddForce(this->pushForce);

        // apply friction force
        // Vec2 friction = Force::GenerateFrictionForce(*body, 20);
        // body->addForce(friction);

        // apply drag force to all bodies if nessecary
        // Vec2 drag = Force::GenerateDragForce(*body, 0.001);
        // body->AddForce(drag);
    }

    // apply stringForce to body connected to the anchor

    // Vec2 springForce = Force::GenerateSpringForce(*bodies[0], this->anchor, this->restLength, this->k);
    // bodies[0]->addForce(springForce);

    // int i;
    // for (i = 1; i < this->bodies.size(); i++)
    // {
    //     Vec2 springForce = Force::GenerateSpringForce(*bodies[i], *bodies[i - 1], 30, 300);
    //     bodies[i]->addForce(springForce);
    //     bodies[i - 1]->addForce(-springForce);
    // }

    for (auto body : this->bodies)
    {
        body->Update(deltaTime);
    }

    for (auto body : this->bodies)
    {
        body->isCollided = false;
    }

    for (int i = 0; i <= this->bodies.size() - 1; i++)
    {
        for (int j = i + 1; j < this->bodies.size(); j++)
        {
            Body *a = this->bodies[i];
            Body *b = this->bodies[j];
            Contact contact;
            bool Collided = Collision::IsCollided(a, b, contact);

            if (Collided)
            {
                Graphics::DrawFillCircle(contact.start.x, contact.start.y, 4, 0xFFF000FF);
                Graphics::DrawFillCircle(contact.end.x, contact.end.y, 4, 0xFFF000FF);
                Graphics::DrawLine(contact.start.x, contact.start.y, contact.start.x + contact.normal.x * 15, contact.start.y + contact.normal.y * 15, 0xFFF000FF);

                a->isCollided = true;
                b->isCollided = true;

                // contact.ResolvePenetration();
            }
        }
    }

    // check if we got to screen bondres;
    for (auto body : this->bodies)
    {
        if (body->shape->GetType() == CIRCILE)
        {
            body->CollidedWithScreenBorders();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render()
{
    // temp remove clear screen from render function for debugging
    // Graphics::ClearScreen(0xFF056263);

    if (this->leftMouseButtonDown)
    {
        Graphics::DrawLine(bodies[0]->postion.x, bodies[0]->postion.y, mouseCurser.x, mouseCurser.y, 0xFF24238A);
    }

    // render all bodies
    for (auto body : this->bodies)
    {
        Uint32 color = body->isCollided ? 0xFF0000FF : 0xFFFFFFFF;

        if (body->shape->GetType() == CIRCILE)
        {
            CircleShape *cirlceShape = (CircleShape *)body->shape;
            Graphics::DrawCircle(body->postion.x, body->postion.y, cirlceShape->radius, body->rotation, color);
        }
        if (body->shape->GetType() == BOX)
        {
            BoxShape *boxShape = (BoxShape *)body->shape;
            Graphics::DrawPolygon(body->postion.x, body->postion.y, boxShape->worldVertices, color);
        }
    }

    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy()
{
    // TODO: destroy all objects in the scene
    for (auto body : this->bodies)
    {
        delete body;
    }
    Graphics::CloseWindow();
}