#include "goalpost.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Goalpost::init()
{
	graphics::Brush brush;
	SETCOLOR(m_brush_post.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_post.fill_opacity = 1.0f;
	m_brush_post.outline_opacity = 0.0f;
	SETCOLOR(m_brush_post.outline_color, 0.2f, 1.0f, 0.5f);


	if (getName() == "goalLeft") {

		m_brush_post.texture = m_state->getFullAssetGamePath("goal-front-left.png");
		position_x = 0.5f;
		position_y = 5.32f;
	
	}

	else if (getName() == "goalRight") {
		m_brush_post.texture = m_state->getFullAssetGamePath("goal-front-right.png");
		position_x = m_state->getCanvasWidth()-0.5f;
		position_y = 5.32f;
	}


	printf("Drawing goalpost\n");
	printf("Goalpost position: %f, %f\n", position_x, position_y);


	
}

void Goalpost::draw()
{
	graphics::drawRect(position_x, position_y, 3.1f*size, size*3.8, m_brush_post);

}

void Goalpost::update(float dt)
{
	GameObject::update(dt);
}
