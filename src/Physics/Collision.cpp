#include "Collision.h"

bool Collision::IsCollided(Body *a, Body *b)
{
    bool aIsCircle = a->shape->GetType() == CIRCILE;
    bool bIsCircle = b->shape->GetType() == CIRCILE;

    if (aIsCircle && bIsCircle)
    {
        return IsCollidedCircleCircle(a, b);
    }
}

bool Collision::IsCollidedCircleCircle(Body *a, Body *b)
{
    CircleShape *aCircle = (CircleShape *)a;
    CircleShape *bCircle = (CircleShape *)b;

    float radiousSum = aCircle->radius + bCircle->radius;

    Vec2 distance = b->postion - a->postion;

    bool isCollided = distance.MagnitudeSquared() >= (radiousSum * radiousSum);

    return isCollided;
}