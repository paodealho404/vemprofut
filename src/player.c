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
#include <stdio.h>

#define DBG_SCALE        30
#define ATTRACTIVE_SCALE 7
#define REPULSIVE_SCALE  1000
#define MIN_MOVEMENT_THRESHOLD 0.00003

#define CLAMP(x, lower, upper) (x < lower ? lower : (x > upper ? upper : x))

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
    player->sprite_index = team == TEAM_BLUE ? 0 : 1;
    
	return player;
}

void draw_player(struct player *player)
{
    if(player == NULL) {
        printf("Error: Attempted to draw a NULL player.\n");
        return;
    }

	struct color base_color = {0.208f, 0.439f, 0.631f, 1.000f};
	struct color red_color = FROM_RGBA(255, 0, 0, 255);
	struct color black_color = FROM_RGBA(0, 0, 0, 255);
	struct color blue_color = FROM_RGBA(0, 0, 255, 255);
	struct color white_color = FROM_RGBA(200, 200, 0, 255);

	glPointSize(1.f);
	for (int i = 0; i < SPRITE_WIDTH; i++) {
		for (int j = 0; j < SPRITE_HEIGHT; j++) {
			rgba_pixel_t pixel = sprites[player->sprite_index][j * SPRITE_HEIGHT + i];
			rgba_pixel_t pixel2 = {0, 0, 0, 1.0};

			if (player->team == TEAM_BLUE) {
				pixel2.r = (player->is_goalkeeper) ? black_color.r : blue_color.r;
				pixel2.g = (player->is_goalkeeper) ? black_color.g : blue_color.g;
				pixel2.b = (player->is_goalkeeper) ? black_color.b : blue_color.b;
			} else {
				pixel2.r = (player->is_goalkeeper) ? white_color.r : red_color.r;
				pixel2.g = (player->is_goalkeeper) ? white_color.g : red_color.g;
				pixel2.b = (player->is_goalkeeper) ? white_color.b : red_color.b;
			}

			if (COLOR_EQ(pixel, base_color)) {
				glColor4f(pixel2.r, pixel2.g, pixel2.b, pixel2.a);
			} else {
				glColor4f(pixel.r, pixel.g, pixel.b, pixel.a);
			}

			glBegin(GL_POINTS);
			glVertex2f(player->position.x + i,
				   player->position.y + (SPRITE_HEIGHT - j));
			glEnd();
		}
	}
}

void update_animation(struct player *player)
{
    static int x = 0;
    float val = sqrt(pow((player->position.x - player->last_position.x), 2) + pow((player->position.y - player->last_position.y), 2));

    if(val >= MIN_MOVEMENT_THRESHOLD) {
        player->sprite_index = (player->sprite_index + 1) % NUM_SPRITES;
    }
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
    player->last_position = player->position;
	player->position.x += (player->attractive.x - player->repulsive.x) / 25000;
	player->position.y += (player->attractive.y - player->repulsive.y) / 25000;
}

void update_goalkeeper_position(struct player *player, struct vector2d smal_area_pos,
				struct vector2d small_area_size)
{
    player->last_position = player->position;
	player->position.y += (player->attractive.y - player->repulsive.y) / 20000;
	player->position.y = CLAMP(player->position.y, smal_area_pos.y,
				   smal_area_pos.y + small_area_size.y - SPRITE_HEIGHT / 2.f);
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