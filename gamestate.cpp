#include "gamestate.h"
#include "player.h"
#include <sgg/graphics.h>
#include "level.h"
#include "goalpost.h"
#include "ball.h"
GameState* GameState::m_instance = nullptr;

GameState::GameState()
{

}
void GameState::init()
{
	graphics::preloadBitmaps(getAssetGamePath());

	m_current_level = new Level();
	m_current_level->init();

	m_p1 = new Player("p1");
	m_p1->setControls(graphics::SCANCODE_LEFT, graphics::SCANCODE_RIGHT, graphics::SCANCODE_UP, graphics::SCANCODE_DOWN , graphics::SCANCODE_KP_PLUS, graphics::SCANCODE_KP_ENTER);
	m_p1->init();
			

	m_p2 = new Player("p2");
	m_p2->setControls(graphics::SCANCODE_A, graphics::SCANCODE_D, graphics::SCANCODE_W, graphics::SCANCODE_S,graphics::SCANCODE_C,graphics::SCANCODE_V);
	m_p2->init();

	m_ball = new Ball("ball");
	m_ball->init();

	m_goalLeft = new Goalpost("goalLeft");
	m_goalLeft->init();

	m_goalRight = new Goalpost("goalRight");
	m_goalRight->init();

	
}

void GameState::update(float dt)
{

	if (!m_current_level) return;
	m_current_level->update(dt);
}

void GameState::draw()
{
	if (!m_current_level) return;
	m_current_level->draw();
}

GameState* GameState::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GameState();
	}
	return m_instance;
}

GameState::~GameState()
{
	if (m_p1) {
		delete m_p1;
	}
	if (m_p2) {
		delete m_p2;
	}
	if (m_ball) {
		delete m_ball;
	}
	if (m_current_level) {
		delete m_current_level;
	}
	if (m_goalLeft) {
		delete m_goalLeft;
	}
	if (m_goalRight) {
		delete m_goalRight;
	}
}

std::string GameState::getAssetGamePath()
{
	return m_asset_game_path;
}

std::string GameState::getAssetHomePath()
{
	return m_asset_home_path;
}

std::string GameState::getFullAssetGamePath(const std::string& asset)
{
	return m_asset_game_path + asset;
}

std::string GameState::getFullAssetHomePath(const std::string& asset)
{
	return m_asset_home_path + asset;
}


