#pragma once
#include <string>
#include "gameobject.h"
#include <sgg/graphics.h>
#include <vector>
#include <list>
#include "player.h"
#include "ball.h"

class Level : public GameObject
{
	graphics::Brush m_brush_bg;
	graphics::Brush m_brush_ground;
	graphics::Brush m_brush_field;
	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;
	

	void checkPlayerCollision(Player* p1, Player* p2);
	void checkBallCollision(Ball *ball, Player* p1, Player* p2);
public : 
	
	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level0");
	~Level();
};