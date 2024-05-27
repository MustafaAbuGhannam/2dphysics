#include "Collision.h"

bool Collision::IsCollided(Body *a, Body *b, Contact &contact)
{
    bool aIsCircle = a->shape->GetType() == CIRCILE;
    bool bIsCircle = b->shape->GetType() == CIRCILE;

    bool aIsPolygon = a->shape->GetType() == BOX || a->shape->GetType() == POLYGON;
    bool bIsPolygon = b->shape->GetType() == BOX || b->shape->GetType() == POLYGON;

    if (aIsCircle && bIsCircle)
    {
        return IsCollidedCircleCircle(a, b, contact);
    }

    if (aIsPolygon && bIsPolygon) {

    }

    return false;
}

bool Collision::IsCollidedCircleCircle(Body *a, Body *b, Contact &contact)
{
    CircleShape *aCircle = (CircleShape *)a->shape;
    CircleShape *bCircle = (CircleShape *)b->shape;

    const float radiousSum = aCircle->radius + bCircle->radius;

    Vec2 distance = b->postion - a->postion;

    bool isCollided = distance.MagnitudeSquared() <= (radiousSum * radiousSum);

    if (!isCollided)
    {
        return false;
    }

    contact.a = a;
    contact.b = b;

    contact.normal = distance;
    contact.normal.Normalize();

    contact.start = contact.b->postion - (contact.normal * bCircle->radius);
    contact.end = contact.a->postion + (contact.normal * aCircle->radius);

    contact.depth = (contact.end - contact.start).Magnitude();

    return true;
}

bool Collision::IsCollidedPolygonPolygon(Body *a, Body* b, Contact &contact)
{
    PolygonShape *polygonA = (PolygonShape*) a->shape;
    PolygonShape *polygonB = (PolygonShape*) b->shape;

    return polygonA->MinimumSeperation(polygonB) <= 0 && polygonB->MinimumSeperation(polygonA) <= 0;
}