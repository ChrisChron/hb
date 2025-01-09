#pragma once

# include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Ball : public GameObject, public Box
{

private:
    float m_x, m_y;
    float m_speedX, m_speedY;
    float m_radius = 0.2f;
	graphics::Brush m_brush;

public:
    Ball(std::string name) : GameObject(name) {}
    void init();
    void draw() override;
	void update(float dt) override;
};

