#include "player.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"
#include <chrono>
#include <thread>

void Player::update(float dt)
{
    float delta_time = dt / 1000.0f; 
    const float gravity = 9.8f * 5; 
    float newX = position_x;
    float newY = position_y;

    bool isMoving = false;
    // Movement handling
    if (graphics::getKeyState(keyLeft) && position_x >= 0.75f)
    {
        newX -= speed * delta_time;
        isMoving = true;
    }
    if (graphics::getKeyState(keyRight) && position_x <= 17.24f)
    {
        newX += speed * delta_time;
        isMoving = true;
    }
    if (graphics::getKeyState(keyUp) && !isJumping)
    {
        isJumping = true;
        verticalVelocity = -jumpForce;
        isMoving = true;
    }
    if (isJumping)
    {
        verticalVelocity += gravity * delta_time;
        newY += verticalVelocity * delta_time;

        if (newY >= 6.60f)
        {
            newY = 6.60f;
            isJumping = false;
            verticalVelocity = 0.0f;
        }
    }

	if (graphics::getKeyState(keyShootLow))
	{
		shootLow();
        shootingLow = true; 
	}
    if (graphics::getKeyState(keyShootHigh)) {
        shootHigh();
		shootingHigh = true;
    }

    if (shootingLow || shootingHigh)
    {
            
            if (getName() == "p1")
                m_brush_p1.texture = m_state->getFullAssetGamePath("player3.png");
            else if (getName() == "p2")
                m_brush_p1.texture = m_state->getFullAssetGamePath("player1.png");

            shootingLow = false; 
            shootingHigh = false;
        
    }
	
    // Optional boundaries check
    if (newX <= 0.75f) newX = 0.75f;
    if (newX > 17.24f) newX = 17.24f;

    Player* otherPlayer = (getName() == "p1") ? m_state->getPlayer2() : m_state->getPlayer1();
    Box futureBox = Box(newX, newY, m_p1_size, m_p1_size);
    Box otherBox = otherPlayer->getBoundingBox();
    bool otherIsMoving = otherPlayer->isMoving;

    if (!futureBox.intersect(otherBox))
    {
        position_x = newX;
        position_y = newY;
    }
    else 
    {
        if (!isMoving && otherIsMoving) 
        {
            float pushOffset = futureBox.intersectSideways(otherBox); 
            position_x += pushOffset*3; 
            printf("This player was pushed back!\n");
            position_y = 6.6f; 
        }
        else if (isMoving && !otherIsMoving) 
        {
            float pushOffset = otherBox.intersectSideways(futureBox); 
            otherPlayer->position_x += pushOffset; 
            printf("Other player was pushed back!\n");
            position_y = 6.6f; 
        }
        else
        {
            printf("Movement blocked due to collision!\n");
        }
    }
    position_y = newY;

    GameObject::update(dt);
}


void Player::init()
{
    graphics::Brush brush;
	if (getName() == "p1")
	{
		position_x = 8.0;
		position_y = 6.6;

        brush.texture = m_state->getFullAssetGamePath("player3.png");
	}
	else if (getName() == "p2")
	{
		position_x = 2.0;
		position_y = 6.6;
        brush.texture = m_state->getFullAssetGamePath("player1.png");
	}

    m_p1_size = 1.5f;

    // Load custom texture
    SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
    brush.fill_opacity = 1.0f;
    brush.outline_opacity = 1.0f; 
    SETCOLOR(brush.outline_color, 0.2f, 1.0f, 0.5f);
    m_brush_p1 = brush; // Store brush
    
    printf("Player position: %f, %f\n", position_x, position_y);
    printf("%s\n", brush.texture.c_str());
}

void Player::draw()
{
    graphics::drawRect(position_x, position_y, m_p1_size, m_p1_size, m_brush_p1);
}

void Player::setControls(graphics::scancode_t left, graphics::scancode_t right, graphics::scancode_t up, graphics::scancode_t down, graphics::scancode_t shootLow, graphics::scancode_t shootHigh)
{
    keyLeft = left;
    keyRight = right;
    keyUp = up;
    keyDown = down;
	keyShootLow = shootLow;
	keyShootHigh = shootHigh;
}
Box Player::getBoundingBox() const
{
    return Box(position_x, position_y, m_p1_size, m_p1_size);
}
bool Player::canMoveTo(float newX, float newY, const Player* otherPlayer) const
{
    Box futureBox = Box(newX, newY, m_p1_size, m_p1_size);
    Box otherBox = otherPlayer->getBoundingBox();
    return !futureBox.intersect(otherBox); // Return true if no collision
}
bool Player::isStuckWith(const Player* otherPlayer) const
{
    return getBoundingBox().intersect(otherPlayer->getBoundingBox());
}

void Player::shootLow()
{
    printf("Player %s shoots low!\n", getName().c_str());
    if (getName() == "p1")
    {
        m_brush_p1.texture = m_state->getFullAssetGamePath("player3-shoot.png");
    }
    else if (getName() == "p2")
    {
        m_brush_p1.texture = m_state->getFullAssetGamePath("player1-shoot.png");
    }
    graphics::drawRect(position_x, position_y, m_p1_size, m_p1_size, m_brush_p1);
	
}

void Player::shootHigh()
{
	printf("Player %s shoots high!\n", getName().c_str());
    if (getName() == "p1")
    {
        m_brush_p1.texture = m_state->getFullAssetGamePath("player3-shoot.png");
    }
    else if (getName() == "p2")
    {
        m_brush_p1.texture = m_state->getFullAssetGamePath("player1-shoot.png");
    }
    graphics::drawRect(position_x, position_y, m_p1_size, m_p1_size, m_brush_p1);


}



