#include "Shape.h"
#include <iostream>

CircleShape::CircleShape(float radius)
{
    this->radius = radius;
    std::cout << "CircleShape constructor called!" << std::endl;
};

CircleShape::~CircleShape()
{
    std::cout << "CircleShape destructor called!" << std::endl;
}

ShapeType CircleShape::GetType() const
{
    return CIRCILE;
}

Shape *CircleShape::Clone() const
{
    return new CircleShape(this->radius);
}

void CircleShape::Draw(Vec2 postion) const
{
    Graphics::DrawCircle(postion.x, postion.y, this->radius, 0.0, 0xFFFFFFFF);
}

PolygonShape::PolygonShape(const std::vector<Vec2> vertices)
{
}

PolygonShape::~PolygonShape()
{
}

ShapeType PolygonShape::GetType() const
{
    return POLYGON;
}

void PolygonShape::Draw(Vec2 postion) const
{
}

Shape *PolygonShape::Clone() const
{
    Shape *cloned = new PolygonShape(this->vertices);
    return cloned;
}

BoxShape::BoxShape(float width, float height)
{
    this->width = width;
    this->height = height;
};

BoxShape::~BoxShape()
{
}

ShapeType BoxShape::GetType() const
{
    return BOX;
}

Shape *BoxShape::Clone() const
{
    return new BoxShape(this->width, this->height);
}

void BoxShape::Draw(Vec2 postion) const
{
}