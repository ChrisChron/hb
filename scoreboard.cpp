#include "scoreboard.h"
#include "gamestate.h"
#include <sgg/graphics.h>
#include <string>
#include <sstream>

void Scoreboard::init() {
    m_brush.outline_opacity = 0.0f;
    m_brush.fill_opacity = 1.0f;
    SETCOLOR(m_brush.fill_color, 1.0f, 0.5f, 0.1f);
	m_brush.texture = m_state->getFullAssetGamePath("scoreboard.png");
    m_x = m_state->getCanvasWidth() / 2;
    m_y = 1.0f;
    m_scorePlayer1 = 0;
    m_scorePlayer2 = 0;
}

void Scoreboard::draw() {
	graphics::setFont(m_state->getFullAssetGamePath("font.ttf"));

    graphics::drawRect(m_x, m_y,1.5f* 1.7f,1.5f* 1.25f, m_brush);
	std::stringstream ss;
	ss << m_scorePlayer1;
	graphics::drawText(m_x - 1.7f / 2.0f, m_y+0.5f, 0.8f, ss.str().c_str(), m_brush);
	ss.str("");
	ss << m_scorePlayer2;
	graphics::drawText(m_x + 0.8f / 2.0f, m_y+0.5f, 0.8f, ss.str().c_str(), m_brush);


}

void Scoreboard::update(float dt) {
}

void Scoreboard::incrementPlayer1Score() {
    m_scorePlayer1++;
}

void Scoreboard::incrementPlayer2Score() {
    m_scorePlayer2++;
}

void Scoreboard::resetScores() {
    m_scorePlayer1 = 0;
    m_scorePlayer2 = 0;
}

int Scoreboard::getPlayer1Score() const {
    return m_scorePlayer1;
}

int Scoreboard::getPlayer2Score() const {
    return m_scorePlayer2;
}
