#pragma once

#include <string>
#include <sgg/graphics.h>
#include "gameobject.h"

class Scoreboard : public GameObject
{
private:
    int m_scorePlayer1 = 0;
    int m_scorePlayer2= 0;
    float m_x;
    float m_y;
    graphics::Brush m_brush;

public:
    Scoreboard(std::string name) : GameObject(name) {};

    void init() override;
    void draw() override;
    void update(float dt) override;

    void incrementPlayer1Score();
    void incrementPlayer2Score();

    void resetScores();

    int getPlayer1Score() const;
    int getPlayer2Score() const;
};


