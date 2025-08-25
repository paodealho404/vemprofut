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
#include <stdlib.h>
#include <OpenGL/gl.h>

#define DBG_SCALE 30

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
	struct color color = constants.team_colors[player->team];
	glColor4f(color.r, color.g, color.b, color.a);
	glPointSize(15.f);
	glBegin(GL_POINTS);
	glVertex2f(player->position.x, player->position.y);
	glEnd();
}

void move_player_to_ball(struct player *player)
{
}

void draw_player_force_vector(struct player *player)
{
#if CONFIG_DRAW_PLAYER_FORCE_VECTORS_EN
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
#endif
}