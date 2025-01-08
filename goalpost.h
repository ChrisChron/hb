#pragma once
# include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Goalpost : public GameObject, public Box
{

    float m_width = 1.0f;
    float m_height = 3.0f;
    graphics::Brush m_brush_post;
    float size;
    float position_x;
    float position_y;
    float speed = 2.3f;

public:
    Goalpost(std::string name) : GameObject(name) {}
    void init();
    void draw() override;
    void update(float dt) override;
    std::string getName() { return m_name; }
};

