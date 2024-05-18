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

float CircleShape::getMomentOfInertia() const
{
    // this is only the shape part of the eq
    return 0.5 * (this->radius * this->radius);
}

PolygonShape::PolygonShape(const std::vector<Vec2> vertices)
{
    std::cout << "PolygonShape constructor called!" << std::endl;
}

PolygonShape::~PolygonShape()
{
    std::cout << "PolygonShape destructor called!" << std::endl;
}

ShapeType PolygonShape::GetType() const
{
    return POLYGON;
}

Shape *PolygonShape::Clone() const
{
    Shape *cloned = new PolygonShape(this->localVertices);
    return cloned;
}

float PolygonShape::getMomentOfInertia() const
{
    // TODO
    return 0.0;
}

void PolygonShape::UpdateVertices(Vec2 position, float rotation)
{
    for (int i = 0; i < this->localVertices.size(); i++)
    {
        // rotate
        this->worldVertices[i] = this->localVertices[i].Rotate(rotation);

        // translate

        this->worldVertices[i] += position;
    }
}

BoxShape::BoxShape(float width, float height)
{
    this->width = width;
    this->height = height;
    this->localVertices.push_back(Vec2(-width / 2, -height / 2));
    this->localVertices.push_back(Vec2(+width / 2, -height / 2));
    this->localVertices.push_back(Vec2(+width / 2, +height / 2));
    this->localVertices.push_back(Vec2(-width / 2, +height / 2));

    this->worldVertices.push_back(Vec2(-width / 2, -height / 2));
    this->worldVertices.push_back(Vec2(+width / 2, -height / 2));
    this->worldVertices.push_back(Vec2(+width / 2, +height / 2));
    this->worldVertices.push_back(Vec2(-width / 2, +height / 2));

    std::cout << "BoxShape constructor called!" << std::endl;
};

BoxShape::~BoxShape()
{
    std::cout << "BoxShape destructor called!" << std::endl;
}

ShapeType BoxShape::GetType() const
{
    return BOX;
}

Shape *BoxShape::Clone() const
{
    return new BoxShape(this->width, this->height);
}

float BoxShape::getMomentOfInertia() const
{
    // this is only the shape part of the eq
    return 0.083333 * (this->width * this->width + this->height * this->height);
}
