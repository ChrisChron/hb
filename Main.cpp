#include "sgg/graphics.h"
#include <stdio.h>
#include "util.h"
#include <string>
#include "gamestate.h"



void init()
{
	GameState::getInstance()->init();   
}



void draw() {
	GameState::getInstance()->draw();
}

void update(float dt) {
	GameState::getInstance()->update(dt);   
}

int main()
{
    graphics::createWindow(1200, 600, "Head Ball here");

    init();
    graphics::setDrawFunction(draw);
    printf("All good draw\n");
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);




    graphics::startMessageLoop();

    return 0;
}