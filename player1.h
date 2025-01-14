#pragma once

# include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Player : public GameObject, public Box
{

        float m_width = 1.0f;
        float m_height = 1.0f;
        graphics::Brush m_brush_p1;
        graphics::scancode_t keyLeft, keyRight, keyUp, keyDown, keyShootLow, keyShootHigh; // Key mappings
        float m_p1_size;
        float size;
		std::string texturePath;
        float position_x;
        float position_y;
        float speed = 3.5f;
        bool shootingLow = false;
        bool shootingHigh = false;
private: 
    bool isJumping = false;
    float verticalVelocity = 0.0f;
    float jumpForce = 15.0f;
    float shootingTimer = 0.0f;    // Timer to track animation duration
    float shootingDuration = 0.4f; // Animation duration (400ms)




    public:
        Player(std::string name) : GameObject(name) {}
        std::string getName() const { return m_name; }
		int getX() const { return position_x; }
		int getY() const { return position_y; }
        void setX(float x) { position_x = x; }
        void setY(float y) { position_y = y; }
		void setSpeed(float s) { speed = s; }
		float getSpeed() { return speed; }
		bool canMoveTo(float newX, float newY, const Player* otherPlayer) const;
		Box getBoundingBox() const;
        bool isMoving = false;
        bool isStuckWith(const Player* otherPlayer) const;
        void shootLow();
        void shootHigh();
		void freeze() { printf("freeze\n"); }
        bool isShootingHigh() const;
        bool isShootingLow() const;
     

        void setControls(graphics::scancode_t left, graphics::scancode_t right, graphics::scancode_t up, graphics::scancode_t down, graphics::scancode_t shootLow , graphics::scancode_t shootHigh);
        void update(float dt) override;
        void init() ;
        void draw() override;
    };

