#include "Contact.h"

void Contact::ResolvePenetration()
{
    this->ResolveWithProjection();
}

void Contact::ResolveWithProjection()
{
    if (this->a->IsStatic() && this->b->IsStatic())
    {
        return;
    }

    float da = this->depth / (this->a->invMass + this->b->invMass) * this->a->invMass;
    float db = this->depth / (this->a->invMass + this->b->invMass) * this->b->invMass;

    this->a->postion -= this->normal * da;
    this->b->postion += this->normal * db;
}