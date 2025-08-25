/**
 * @file ball.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementação das funções relacionadas à bola.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "ball.h"
#include "opengl.h"
#include "circle.h"
#include "color.h"

#define BALL_RADIUS 5.0f
#define BALL_SPEED  3.0f

static struct ball_data {
	struct vector2d position;
} self;

const static struct ball_const {
	struct color ball_color;
} constants = {
	.ball_color = FROM_RGBA(255, 100, 255, 255),
};

void draw_ball()
{
	draw_circle_filled(self.position, BALL_RADIUS, constants.ball_color);
}

void move_ball(struct vector2d direction)
{
	self.position.x += direction.x * BALL_SPEED;
	self.position.y += direction.y * BALL_SPEED;
}

void set_ball_position(struct vector2d position)
{
	self.position = position;
}

struct vector2d get_ball_position(void)
{
	return self.position;
}
