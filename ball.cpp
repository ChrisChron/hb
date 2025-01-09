#include "ball.h"
#include <sgg/graphics.h>
#include "gamestate.h"
void Ball::init() {
    m_x = m_state->getCanvasWidth()/2; // Initial position
    m_y = 3.0f;
    m_speedX = 0.0f; // Initial speed
    m_speedY = 0.04f;
    m_brush.texture = m_state->getFullAssetGamePath("ball.png");
    m_brush.outline_opacity = 0.0f;
    SETCOLOR(m_brush.outline_color, 0.2f, 1.0f, 0.5f);
    m_brush.outline_opacity = 1.0f;
    m_brush.fill_opacity = 0.8f;
}

void Ball::draw() {
    graphics::drawDisk(m_x, m_y, m_radius, m_brush);
}

void Ball::update(float dt) {
    float delta_time = dt / 1000.0f;
    const float gravity = 9.8f * 5; // Gravity strength
    const float groundLevel = 7.3f; // Ground level
    const float bounceDamping = 0.6f; // Factor to reduce bounce height

    // Apply gravity to vertical velocity
    m_speedY += gravity * delta_time;

    // Update ball position
    m_x += m_speedX * delta_time;
    m_y += m_speedY * delta_time;

    // Check collision with ground
    if (m_y > groundLevel - m_radius ) {
        m_y = groundLevel - m_radius; // Align with the ground
        m_speedY = -m_speedY * bounceDamping; // Reverse velocity and apply damping

        // Optional: Stop bouncing if the velocity is very small
        if (abs(m_speedY) < 0.1f) {
            m_speedY = 0.0f; // Stop vertical movement
        }
    }


}

