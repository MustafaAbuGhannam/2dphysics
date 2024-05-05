#ifndef SHAPE_H
#define SHAPE_H

#include "Vec2.h"
#include <vector>

enum ShapeType {
    CIRCILE,
    POLYGON,
    BOX
};

struct Shape
{
    virtual ~Shape() = default;
    virtual ShapeType GetType() const = 0;
    virtual Shape* Clone() const = 0;
};

struct CircleSahpe: public Shape 
{
    float radius;

    CircleSahpe(const float radius);
    virtual ~CircleSahpe();
    ShapeType GetType() const override;
    Shape* Clone() const override;
};

struct PolygonShape: public Shape
{
    std::vector<Vec2> vertices;

    PolygonShape() = default;
    PolygonShape(const std::vector<Vec2> vertices);
    virtual ~PolygonShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
};

struct BoxShape: public PolygonShape
{
    float width;
    float height;

    BoxShape(float witdh, float height);
    virtual ~BoxShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
};

#endif
