#include "Shape.h"
#include <iostream>

CircleSahpe::CircleSahpe(float radius)
{
    this->radius = radius;
    std::cout << "CircleShape constructor called!" << std::endl;
};

CircleSahpe::~CircleSahpe()
{
    std::cout << "CircleShape destructor called!" << std::endl;
}

ShapeType CircleSahpe::GetType() const 
{
    return CIRCILE;
}

Shape* CircleSahpe::Clone() const
{
    return new CircleSahpe(this->radius);
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

Shape* PolygonShape::Clone() const
{
    new PolygonShape(this->vertices);
}

BoxShape::BoxShape(float width, float height) {
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

Shape* BoxShape::Clone() const
{
    return new BoxShape(this->width, this->height);
}
