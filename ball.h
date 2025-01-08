#pragma once

# include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Ball : public GameObject, public Box
{

    float m_width = 1.0f;
    float m_height = 1.0f;
    graphics::Brush m_brush_p1;
    float size;
    float position_x;
    float position_y;
    float speed = 2.3f;

public:
    Ball(std::string name) : GameObject(name) {}
    void init();
    void draw() override;
	void update(float dt) override;
};

