/**
 * @file player.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementação da estrutura e funções relacionadas aos jogadores.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "color.h"
#include "player.h"
#include "opengl.h"
#include "vector.h"
#include "players_sprites.h"
#include <stdlib.h>
#include <math.h>
#include <OpenGL/gl.h>

#define DBG_SCALE        30
#define ATTRACTIVE_SCALE 7
#define REPULSIVE_SCALE  1000

static const struct player_const {
	struct color team_colors[_TEAM_AMOUNT];
} constants = {
	.team_colors =
		{
			FROM_RGBA(0, 0, 255, 255), // Azul
			FROM_RGBA(255, 0, 0, 255), // Vermelho
		},
};

struct player *create_player(float x, float y, enum team team)
{
	struct player *player = malloc(sizeof(struct player));
	if (!player) {
		return NULL;
	}

	player->position.x = x;
	player->position.y = y;
	player->team = team;
	player->attractive.x = 0.0;
	player->attractive.y = 0.0;
	player->repulsive.x = 0.0;
	player->repulsive.y = 0.0;

	return player;
}

void draw_player(struct player *player)
{
	glPointSize(1.f);
	for (int i = 0; i < SPRITE_WIDTH; i++) {
		for (int j = 0; j < SPRITE_HEIGHT; j++) {
			rgba_pixel_t pixel = sprites[player->sprite_index][j * SPRITE_HEIGHT + i];
			glColor4f(pixel.r + ((player->team == TEAM_RED) ? .5f : .0f), pixel.g,
				  pixel.b + ((player->team == TEAM_BLUE) ? .5f : .0f), pixel.a);
			glBegin(GL_POINTS);
			glVertex2f(player->position.x + i,
				   player->position.y + (SPRITE_HEIGHT - j));
			glEnd();
		}
	}
}

void update_animation(struct player *player)
{
	player->sprite_index = (player->sprite_index + 1) % NUM_SPRITES;
}

void update_attractive_force_vector_towards_ball(struct player *player,
						 struct vector2d ball_position, float d_star)
{
	double x = ball_position.x - player->position.x;
	double y = ball_position.y - player->position.y;
	float dist = sqrt(x * x + y * y);

	if (dist < d_star) {
		dist = d_star;
	}
	player->attractive.x = ATTRACTIVE_SCALE * (ball_position.x - player->position.x) / dist;
	player->attractive.y = ATTRACTIVE_SCALE * (ball_position.y - player->position.y) / dist;
}

void update_repulsive_force_vector_from_other_player(struct player *player,
						     struct player *other_player, float d_star)
{
	double x = other_player->position.x - player->position.x;
	double y = other_player->position.y - player->position.y;
	float dist = sqrt(x * x + y * y);

	if (dist < 10) {
		dist = 10;
	}

	if (dist < d_star) {
		player->repulsive.x -=
			REPULSIVE_SCALE * (player->position.x - other_player->position.x) / dist;
		player->repulsive.y -=
			REPULSIVE_SCALE * (player->position.y - other_player->position.y) / dist;
	} else {
		player->repulsive.x = 4 * (player->position.x - other_player->position.x) / dist;
		player->repulsive.y = 4 * (player->position.y - other_player->position.y) / dist;
	}
}

void update_player_position(struct player *player)
{
	player->position.x += (player->attractive.x - player->repulsive.x) / 20000;
	player->position.y += (player->attractive.y - player->repulsive.y) / 20000;
}

void draw_player_force_vector(struct player *player)
{
	glPushMatrix();
	glColor3f(0.1, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(player->position.x, player->position.y);
	glVertex2f(player->position.x + (DBG_SCALE * player->attractive.x),
		   player->position.y + (DBG_SCALE * player->attractive.y));
	glVertex2f(player->position.x + (DBG_SCALE * player->attractive.x),
		   player->position.y + (DBG_SCALE * player->attractive.y + 4));
	glVertex2f(player->position.x, player->position.y + 8);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(player->position.x, player->position.y);
	glVertex2f(player->position.x + (DBG_SCALE * player->repulsive.x),
		   player->position.y + (DBG_SCALE * player->repulsive.y));
	glVertex2f(player->position.x + (DBG_SCALE * player->repulsive.x),
		   player->position.y + (DBG_SCALE * player->repulsive.y + 4));
	glVertex2f(player->position.x, player->position.y + 8);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(player->position.x, player->position.y);
	glVertex2f(player->position.x + (DBG_SCALE * (player->attractive.x - player->repulsive.x)),
		   player->position.y + (DBG_SCALE * (player->attractive.y - player->repulsive.y)));
	glVertex2f(player->position.x + (DBG_SCALE * (player->attractive.x - player->repulsive.x)),
		   player->position.y +
			   (DBG_SCALE * (player->attractive.y - player->repulsive.y) + 4));
	glVertex2f(player->position.x, player->position.y + 8);
	glEnd();
	glPopMatrix();
}