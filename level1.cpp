#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "goalpost.h"
#include "ball.h"
#include "scoreboard.h"
#include "powerup.h"
#include <vector>
#include <cstdlib> 
#include "timer.h"
#include "powerup.h"
#include <cstdlib> // For rand()

std::vector<PowerUp*> m_powerUps; // List of active power-ups
Timer m_powerUpTimer; // Timer to spawn power-ups
/*
void Level::checkBallCollision(Ball* ball, Player* p1, Player* p2)
{
	// Get the bounding boxes for the ball and both players
	Box ballBox = ball->getBoundingBox();
	Box player1Box = p1->getBoundingBox();
	Box player2Box = p2->getBoundingBox();

	// Ball's current velocity
	float ballSpeedX = ball->getSpeedX();
	float ballSpeedY = ball->getSpeedY();

	// Check collision with Player 1 (on the right side)
	if (ballBox.intersect(player1Box))
	{
		printf("Ball collided with Player 1!\n");
		ball->setPosition(ball->getX() , ball->getY());
		// Determine which side of the player the ball hit
		if (ball->getX() < p1->getX()) // Ball hit the front of Player 1
		{
			ball->setVelocity(-fabs(ballSpeedX) * 0.04f, ballSpeedY); // Reverse X direction
		}
		else // Ball hit the back of Player 1
		{
			ball->setVelocity(fabs(ballSpeedX) * 0.04f , ballSpeedY); // Ball continues forward
		}

		// Adjust ball's position slightly to prevent sticking
		
	}

	// Check collision with Player 2 (on the left side)
	if (ballBox.intersect(player2Box))
	{
		printf("Ball collided with Player 2!\n");
		ball->setPosition(ball->getX() , ball->getY());
		// Determine which side of the player the ball hit
		if (ball->getX() > p2->getX()) // Ball hit the front of Player 2
		{
			ball->setVelocity(-fabs(ballSpeedX) * 0.04f, ballSpeedY); // Reverse X direction
		}
		else // Ball hit the back of Player 2
		{
			ball->setVelocity(fabs(ballSpeedX) * 0.04f, ballSpeedY); // Ball continues forward
		}

		// Adjust ball's position slightly to prevent sticking
	
	}
}

void Level::checkBallCollision(Ball* ball, Player* p1, Player* p2)
{
	// Get bounding boxes for the ball and the players
	Box ballBox = ball->getBoundingBox();
	Box playerBox;
	Player* collidingPlayer = nullptr;

	// Check if the ball collides with either player
	if (ballBox.intersect(p1->getBoundingBox()))
	{
		collidingPlayer = p1;
		playerBox = p1->getBoundingBox();
	}
	else if (ballBox.intersect(p2->getBoundingBox()))
	{
		collidingPlayer = p2;
		playerBox = p2->getBoundingBox();
	}

	// If there's a collision with any player
	if (collidingPlayer && !ball->isInCollision())
	{
		ball->setInCollision(true); // Prevent multiple collision checks
		printf("Ball collided with Player %d!\n", (collidingPlayer == p1) ? 1 : 2);

		// Get the current velocity of the ball and the colliding player's speed
		float playerSpeed = collidingPlayer->getSpeed();
		float ballSpeedX = ball->getSpeedX();
		float ballSpeedY = ball->getSpeedY();

		// Determine the collision response based on the player's position
		if (collidingPlayer == p1) // Player 1 (Right side of the canvas)
		{
			if (ball->getX() < p1->getX()) // Ball hits Player 1's front
			{
				if (ballSpeedX < 3.7f) {
					ballSpeedX = -playerSpeed;
				}
				else {
					ballSpeedX =  -(ballSpeedX);
					printf("ballSpeedX : %f", ballSpeedX);
				}
			}
			else // Ball hits Player 1's back
			{
				if (ballSpeedX< 3.7f) {
					ballSpeedX = playerSpeed;
				}
				else {
					ballSpeedX = fabs(ballSpeedX); // Ball moves to the left
					printf("ballSpeedX : %f", ballSpeedX);
				}
			}
		}
		else if (collidingPlayer == p2) // Player 2 (Left side of the canvas)
		{
			if (ball->getX() < p2->getX()) // Ball hits Player 2's back
			{
				if (ballSpeedX < 3.7f) {
					ballSpeedX = -playerSpeed;
				}
				else {
					ballSpeedX = -fabs(ballSpeedX);// Ball moves to the left
				}
			}
			else // Ball hits Player 2's front
			{
				if (ballSpeedX < 3.7f) {
					ballSpeedX = playerSpeed;
				}
				else {
					ballSpeedX = fabs(ballSpeedX); // Ball moves to the right
				}
			}
		}


		// Slight vertical adjustment to simulate deflection
		//ballSpeedY += (collidingPlayer->getY() - ball->getY()) * 0.1f;

		// Update the ball's velocity
		ball->setVelocity(ballSpeedX, ballSpeedY);

		// Reset the collision flag after handling
		ball->setInCollision(false);
	}
}
*/
void Level::checkBallCollision(Ball* ball, Player* p1, Player* p2)
{
	// Get bounding boxes for the ball and the players
	Box ballBox = ball->getBoundingBox();
	Box playerBox;
	Player* collidingPlayer = nullptr;

	// Determine if the ball collides with either player
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

	// Handle collision
	if (collidingPlayer && !ball->isInCollision())
	{
		ball->setInCollision(true);
		printf("Ball collided with Player %d!\n", (collidingPlayer == p1) ? 1 : 2);

		// Player properties
		float playerSpeed = collidingPlayer->getSpeed();
		bool isPlayerMoving = collidingPlayer->isMoving;

		// Ball properties
		float ballSpeedX = ball->getSpeedX();
		float ballSpeedY = ball->getSpeedY();
		const float friction = 0.98f;  // Friction for sliding
		const float bounceFactor = 0.7f;  // Speed reduction for bounces
		const float minSpeed = 3.51f;  // Minimum speed to avoid the ball being stuck

		// Handle shooting
		if (collidingPlayer->isShootingHigh()) {
			ballSpeedY = 50.0f; // Adjust vertical speed for high shot
			ballSpeedX = 100.0f; // Adjust horizontal speed for high shot
		}
		else if (collidingPlayer->isShootingLow()) {
			ballSpeedY = -50.0f; // Adjust vertical speed for low shot
			ballSpeedX = 100.0f; // Adjust horizontal speed for low shot
		}

		// Handle stationary ball (first push)
		if (fabs(ballSpeedX) < 0.01f && fabs(ballSpeedY) < 0.01f)
		{
			ballSpeedX = playerSpeed * ((collidingPlayer == p1) ? -1.0f : 1.0f);
			printf("First push applied to the ball!\n");
		}

		// Player is moving: push the ball
		if (isPlayerMoving) {
			if (collidingPlayer->isShootingHigh()) {
				ballSpeedY = 50.0f; // Adjust vertical speed for high shot
				ballSpeedX = 100.0f; // Adjust horizontal speed for high shot
			}
			else if (collidingPlayer->isShootingLow()) {
				ballSpeedY = -50.0f; // Adjust vertical speed for low shot
				ballSpeedX = 100.0f; // Adjust horizontal speed for low shot
			}
			else {
				ballSpeedX = playerSpeed * ((collidingPlayer == p1) ? -1.0f : 1.0f);
				ballSpeedY = 0.0f; // No vertical movement from push
			}
		}
		else {
			// Player is stationary: bounce the ball
			ballSpeedX = -ballSpeedX * bounceFactor;
			ballSpeedY = -ballSpeedY * bounceFactor;

			// Apply friction to simulate sliding
			ballSpeedX *= friction;
			ballSpeedY *= friction;

			// Ensure the ball doesn't stop completely
			if (fabs(ballSpeedX) < minSpeed)
				ballSpeedX = (collidingPlayer == p1) ? -minSpeed : minSpeed;
		}

		// Adjust ball position to avoid overlap
		if (collidingPlayer == p1)
		{
			// Player 1 is on the right; position ball to the left
			ball->setPosition(playerBox.position_x - playerBox.m_width / 2 - ballBox.m_width / 2, ball->getY());
		}
		else if (collidingPlayer == p2)
		{
			// Player 2 is on the left; position ball to the right
			ball->setPosition(playerBox.position_x + playerBox.m_width / 2 + ballBox.m_width / 2, ball->getY());
		}

		// Set the updated velocity
		ball->setVelocity(ballSpeedX, ballSpeedY);
	}
	else if (!collidingPlayer)
	{
		ball->setInCollision(false); // Reset collision status when no collision
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
	//checkPlayerCollision(m_state->getPlayer1() , m_state->getPlayer2());
	// Check for goals

	Box leftGoalpostBox = m_state->getGoalpostLeft()->getBoundingBox();
	Box rightGoalpostBox = m_state->getGoalpostRight()->getBoundingBox();
	Box ballBox = m_state->getBall()->getBoundingBox();
	if (ballBox.intersect(rightGoalpostBox) > 0.2)
	{
		goalScored = true;

		//m_state->getScoreboard()->incrementPlayer2Score();
		//	m_state->getBall()->setPosition(9.0f, 6.6f);
		//m_state->getBall()->setVelocity(0.0f, 0.0f);
	}
	if (ballBox.intersect(leftGoalpostBox)) {
		goalScored = true;

	}
	if (goalScored) {
		if (m_state->getBall()->getX() <= 0.9f && m_state->getBall()->getY() <= 15.0f) {

			m_state->getScoreboard()->incrementPlayer2Score();
			m_state->getBall()->setPosition(3.0f, 3.6f);
			m_state->getBall()->setVelocity(0.001f, 0.0f);
			m_state->getPlayer2()->setX(2.0f);
			m_state->getPlayer1()->setX(16.0f);
		}
		if (m_state->getBall()->getX() >= 17.5 && m_state->getBall()->getY() <= 15.0f) {

			m_state->getScoreboard()->incrementPlayer1Score();
			m_state->getBall()->setPosition(15.0f, 1.6f);
			m_state->getBall()->setVelocity(0.001f, 0.0f);
			m_state->getPlayer2()->setX(2.0f);
			m_state->getPlayer1()->setX(16.0f);
		}
		goalScored = false;
	}
	// End of goal check

	//Check for goalpost collision with ball

	
	if (!goalScored){
	if (ballBox.intersectDown(leftGoalpostBox)) {
		m_state->getBall()->setPosition(3.0f, m_state->getBall()->getY());
		m_state->getBall()->setVelocity(-2.0f, m_state->getBall()->getSpeedY());

	}
	else if (ballBox.intersectDown(rightGoalpostBox)) {
		m_state->getBall()->setPosition(15.0f, m_state->getBall()->getY());
		m_state->getBall()->setVelocity(-2.0f, m_state->getBall()->getSpeedY());
	}
}
	// End of goalpost collision with ball check

	// Start of powerups
	m_powerUpTimer.operator float(); // Update timer value

	// Spawn a new power-up every 15 seconds
	if (m_powerUpTimer >= 0.8f) // Timer completed one cycle (normalized to 1.0)
	{
		m_powerUpTimer.start(); // Restart the timer for the next cycle

		// Random X position (0 to 17.0f scaled from 0 to 1700, with two decimal places)
		float px = 4.0f + (rand() % 1100) / 100.0f;


		// Random Y position (6.6f to 8.0f scaled from 660 to 800, with two decimal places)
		float py = 1.50f + (rand() % 180) / 100.0f;

		int type = rand() % 2; // Random type (0 = ball effect, 1 = player effect)

		PowerUp* newPowerUp = new PowerUp(px, py, type); // Create the power-up
		newPowerUp->init(); // Initialize the power-up
		m_powerUps.push_back(newPowerUp); // Add to the list of active power-ups

		printf("Spawned a power-up at (%f, %f) of type %d\n", px, py, type);
	}

	// Update and remove expired power-ups
	for (auto it = m_powerUps.begin(); it != m_powerUps.end();)
	{
		(*it)->update(dt); // Update each power-up
		if (!(*it)->isActive()) // Check if the power-up expired
		{
			delete* it;
			it = m_powerUps.erase(it); // Remove from the list
		}
		else
		{
			++it;
		}
	}

	// Handle ball collisions with power-ups
	for (auto& powerUp : m_powerUps)
	{
		if (powerUp->checkCollision(m_state->getBall()->getX(), m_state->getBall()->getY(), m_state->getBall()->getRadius()))
		{
			int effectType = powerUp->getType();
			if (effectType == 0)
			{
			}
			else if (effectType == 1)
			{
				// Player effect: Freeze player 1
				m_state->getPlayer1()->freeze(); // Freeze for 2 seconds
			}
			powerUp->setActive(false); // Deactivate power-up after collision
		}
	}
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
	if (m_powerUpTimer > 0.0f && m_powerUpTimer < 1.0f) {
		// Random X position (0 to 17.0f scaled from 0 to 1700, with two decimal places)
		float px = (rand() % 1700) / 100.0f;

		// Random Y position (6.6f to 8.0f scaled from 660 to 800, with two decimal places)
		float py = 660 + (rand() % 1400) / 100.0f; // 140 because 8.0f - 6.6f = 1.4

		int type = rand() % 2; // Random type (0 = ball, 1 = player)
		PowerUp* powerUp = new PowerUp(px, py, type);
		powerUp->init(); // Initialize the power-up
		m_powerUps.push_back(powerUp);
	}
	m_powerUpTimer = Timer(15.0f, Timer::TIMER_LOOPING); // 15 seconds per spawn
	m_powerUpTimer.start(); // Start the power-up timer
	


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
	// Draw power-ups
	for (auto& powerUp : m_powerUps) {
		powerUp->draw();
	}


}
Level::Level(const std::string& name)
	: m_powerUpTimer(15.0f, Timer::TIMER_LOOPING) // Spawn every 10 seconds
{
	m_powerUpTimer.start();
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
