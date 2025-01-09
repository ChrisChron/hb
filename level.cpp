#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "goalpost.h"
#include "ball.h"
#include "scoreboard.h"

void Level::checkPlayerCollision(Player* p1, Player* p2)
{
	// Get bounding boxes for both players
	Box box1 = p1->getBoundingBox();
	Box box2 = p2->getBoundingBox();

	// Check if they intersect
	if (box1.intersect(box2))
	{
		printf("Players collided and are stuck!\n");

		// Prevent movement by freezing positions
		p1->setX(p1->getX()); // Lock position


		p2->setX(p2->getX()); // Lock position

	}
	else if (box2.intersect(box1))
	{
		printf("Players collided and are stuck!\n");
		// Prevent movement by freezing positions
		p1->setX(p1->getX()); // Lock position


		p2->setX(p2->getX()); // Lock position

	}
	
}


void Level::update(float dt)
{
	if (m_state->getPlayer1()->isActive())
	{
		
		m_state->getPlayer1()->update(dt);
		
		
	}
	if (m_state->getPlayer2()->isActive())
	{
		
		m_state->getPlayer2()->update(dt);
	}
	if (m_state->getBall()->isActive())
	{
		m_state->getBall()->update(dt);
	}
	if (m_state->getGoalpostLeft()->isActive())
	{
		m_state->getGoalpostLeft()->update(dt);
	}
	if (m_state->getGoalpostRight()->isActive())
	{
		m_state->getGoalpostRight()->update(dt);
	}
	if (m_state->getScoreboard()->isActive())
	{
		m_state->getScoreboard()->update(dt);
	}



	
	checkPlayerCollision(m_state->getPlayer1() , m_state->getPlayer2());
	GameObject::update(dt);

}

void Level::init()
{	
	SETCOLOR(m_brush_bg.fill_color, 1.0f, 0.0f, 0.3f);
	m_brush_bg.outline_opacity =1.0f;
	m_brush_bg.fill_opacity = 1.0f;
	SETCOLOR(m_brush_field.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_field.fill_opacity = 1.0f;
	m_brush_field.outline_opacity = 0.0f;
	m_brush_field.texture = m_state->getFullAssetGamePath("bg.png");

	for (auto p_gob : m_static_objects) {
		if (p_gob) p_gob->init();
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) p_gob->init();
	}
	


}
void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	graphics::drawRect(w/2, h/2 , w, h, m_brush_bg);
	
	graphics::drawRect(w / 2, h / 2, w, h, m_brush_field);


	if (m_state->getPlayer1()->isActive())
	{
		m_state->getPlayer1()->draw();
	}
	if (m_state->getPlayer2()->isActive())
	{
		m_state->getPlayer2()->draw();
	}
	if (m_state->getBall()->isActive())
	{
		m_state->getBall()->draw();
	}
	if (m_state->getGoalpostLeft()->isActive())
	{
		m_state->getGoalpostLeft()->draw();
	}
	if (m_state->getGoalpostRight()->isActive())
	{
		m_state->getGoalpostRight()->draw();
	}
	if (m_state->getScoreboard()->isActive())
	{
		m_state->getScoreboard()->draw();
	}
	for (auto p_gob : m_static_objects) {
		if (p_gob) p_gob->draw();
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) p_gob->draw();
	}

}
Level::Level(const std::string& name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects) {
		if (p_gob) delete p_gob;
	}
	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) delete p_gob;
	}
}
