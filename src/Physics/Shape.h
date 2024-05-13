#ifndef SHAPE_H
#define SHAPE_H

#include "Vec2.h"
#include "../Graphics.h"
#include <vector>

enum ShapeType
{
    CIRCILE,
    POLYGON,
    BOX
};

struct Shape
{
    virtual ~Shape() = default;
    virtual ShapeType GetType() const = 0;
    virtual Shape *Clone() const = 0;
    virtual void Draw(Vec2 postion, float rotation) const = 0;
    virtual float getMomentOfInertia() const = 0;
};

struct CircleShape : public Shape
{
    float radius;

    CircleShape(const float radius);
    virtual ~CircleShape();
    ShapeType GetType() const override;
    Shape *Clone() const override;
    void Draw(Vec2 postion, float rotation) const override;
    float getMomentOfInertia() const override;
};

struct PolygonShape : public Shape
{
    std::vector<Vec2> localVertices;
    std::vector<Vec2> worldVertices;

    PolygonShape() = default;
    PolygonShape(const std::vector<Vec2> vertices);
    virtual ~PolygonShape();
    ShapeType GetType() const override;
    Shape *Clone() const override;
    void Draw(Vec2 postion, float rotation) const override;
    float getMomentOfInertia() const override;
    void UpdateVertices(Vec2 position, float rotation);
};

struct BoxShape : public PolygonShape
{
    float width;
    float height;

    BoxShape(float witdh, float height);
    virtual ~BoxShape();
    ShapeType GetType() const override;
    Shape *Clone() const override;
    void Draw(Vec2 postion, float rotation) const override;
    float getMomentOfInertia() const override;
};

#endif
