#pragma once
#include <sgg/graphics.h>
#include "util.h"
#include <string>

class GameState {
private:
    std::string m_asset_game_path = "assets\\game\\";
    std::string m_asset_home_path = "assets\\home\\";
    float m_canvas_width = 18.0f;
    float m_canvas_height = 10.0f;



    static GameState* m_instance;
    GameState();

    class Player* m_p1 = 0;
    class Player* m_p2 = 0;
    class Ball* m_ball = 0;
    class Goalpost* m_goalLeft = 0;
    class Goalpost* m_goalRight = 0;
    class Level* m_current_level = 0;
public:
    graphics::Brush m_brush_bg;

    graphics::Brush m_brush_p2;
    graphics::Brush m_brush_ball;


    float m_ball_x = m_canvas_width / 0.5f;
    float m_ball_y = m_canvas_height / 1.8f;
    float m_ball_size = 1.0f;

    bool m_debugging = false;

    void init();
    void update(float dt);
    void draw();


    static GameState* getInstance();
	~GameState();
	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }
    std::string getAssetGamePath();
    std::string getAssetHomePath();
    std::string getFullAssetGamePath(const std::string& asset);
    std::string getFullAssetHomePath(const std::string& asset);

	class Player* getPlayer1() { return m_p1; }
    class Player* getPlayer2() { return m_p2; }
    class Goalpost* getGoalpostLeft() { return m_goalLeft; }
    class Goalpost* getGoalpostRight() { return m_goalRight; }






};
