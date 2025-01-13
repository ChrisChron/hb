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

void Level::checkBallCollision(Ball* ball, Player* p1, Player* p2)
{
	// Get bounding boxes for the ball and the players
	Box ballBox = ball->getBoundingBox();
	Box playerBox;
	Player* collidingPlayer = nullptr;

	// Έλεγχος αν η μπάλα συγκρούεται με κάποιον από τους παίκτες
	if (p1->getBoundingBox().intersect(ballBox))	
	{
		collidingPlayer = p1;
		playerBox = p1->getBoundingBox();
	}
	else if (p2->getBoundingBox().intersect(ballBox))
	{
		collidingPlayer = p2;
		playerBox = p2->getBoundingBox();
	}

	// Αν υπάρχει σύγκρουση με κάποιον παίκτη
	if (collidingPlayer && !ball->isInCollision())
	{
		ball->setInCollision(true);
		printf("Ball collided with Player %d!\n", (collidingPlayer == p1) ? 1 : 2);

		// Υπολογισμός ταχύτητας
		float playerSpeed = collidingPlayer->getSpeed();
		float ballSpeedX = ball->getSpeedX();
		float ballSpeedY = ball->getSpeedY();

		// Determine the direction based on the player's position relative to the ball
		if (p1->getX() < ball->getX())
		{
			// Player is to the left of the ball, ball should go to the right
			ballSpeedX = fabs(ballSpeedX) * 200.0f + playerSpeed * 100.0f;
		}
		else
		{
			// Player is to the right of the ball, ball should go to the left
			ballSpeedX = -(fabs(ballSpeedX) * 200.0f + playerSpeed * 100.0f);
		}

		// Add some randomness to the ball's speed
		ballSpeedX += (rand() % 10 - 5) * 0.1f;
		ballSpeedY += (rand() % 10 - 5) * 0.1f;

		ball->setVelocity(ballSpeedX, ballSpeedY);
	}
	else if (!collidingPlayer)
	{
		ball->setInCollision(false);
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



	checkBallCollision(m_state->getBall(), m_state->getPlayer1(), m_state->getPlayer2());
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
