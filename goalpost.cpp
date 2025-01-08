#include "goalpost.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Goalpost::init()
{
	graphics::Brush brush;

	if (getName() == "goalLeft") {

			brush.texture = m_state->getFullAssetGamePath("goal-front-left.png");
			position_x = 3.0f;
			position_y = 6.6f;
		}
	else if (getName() == "goalRight") {
		brush.texture = m_state->getFullAssetGamePath("goal-front-right.png");
		position_x = 8.0f;
		position_y = 6.6f;
	}
	SETCOLOR(brush.fill_color, 1.0f, 1.0f, 1.0f);
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 1.0f;
	SETCOLOR(brush.outline_color, 0.2f, 1.0f, 0.5f);
	m_brush_post = brush;

	printf("Drawing goalpost\n");
	printf("Goalpost position: %f, %f\n", position_x, position_y);


	
}

void Goalpost::draw()
{
	graphics::drawRect(position_x, position_y, size, size, m_brush_post);

}

void Goalpost::update(float dt)
{
	GameObject::update(dt);
}
