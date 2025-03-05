#pragma once
#include "Rigidbody.h"
class Box : public Rigidbody
{
public:
    Box(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 extents, glm::vec4 colour, glm::vec2 localX, glm::vec2 localY);
    ~Box();
    void fixedUpdate(glm::vec2 gravity, float timeStep);
    void draw();
    float getWidth() const;
    float getHeight() const;
    glm::vec2 getExtents() const;
    glm::vec2 getLocalX() const;
    glm::vec2 getLocalY() const;
    bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts,
        float& pen, glm::vec2& edgeNormal);

protected:
    glm::vec2 m_extents; // the halfedge lengths
    glm::vec4 m_colour;

    // store the local x,y axes of the box based on its angle of rotation
    glm::vec2 m_localX;
    glm::vec2 m_localY;
};

