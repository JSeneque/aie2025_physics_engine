#pragma once
#include <glm/glm.hpp>

class Stick
{
public:
    Stick () {}
    Stick(const glm::vec2 cueBallPosition);

    void Update(float deltaTime);
    void Draw();
    void DrawImGui();

    glm::vec2 GetDirection() const;
    float GetPower() const;

private:
    glm::vec2 m_cueBallPosition;
    float m_angle;
    float m_power;
    float m_length;    
};
