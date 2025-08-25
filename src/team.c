/**
 * @file team.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementação da estrutura e funções relacionadas aos times.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "team.h"
#include "player.h"
#include "opengl.h"
#include "vector.h"

static struct team_data {
	struct player *players[_TEAM_AMOUNT][PLAYERS_PER_TEAM];
} self;

void init_teams(struct vector2d position, struct vector2d size)
{
	struct vector2d initial_positions[_TEAM_AMOUNT][PLAYERS_PER_TEAM] = {
		{
			VECTOR_2D(position.x, position.y + size.y * .5f),

			VECTOR_2D(position.x + size.x * .35f, position.y + size.y * .75f),
			VECTOR_2D(position.x + size.x * .40f, position.y + size.y * .5f),
			VECTOR_2D(position.x + size.x * .35f, position.y + size.y * .25f),

			VECTOR_2D(position.x + size.x * .20f, position.y + size.y * .75f),
			VECTOR_2D(position.x + size.x * .15f, position.y + size.y * .5f),
			VECTOR_2D(position.x + size.x * .20f, position.y + size.y * .25f),
		},
		{
			VECTOR_2D(position.x + size.x, position.y + size.y * .5f),

			VECTOR_2D(position.x + size.x * .85f, position.y + size.y * .75f),
			VECTOR_2D(position.x + size.x * .90f, position.y + size.y * .5f),
			VECTOR_2D(position.x + size.x * .85f, position.y + size.y * .25f),

			VECTOR_2D(position.x + size.x * .70f, position.y + size.y * .75f),
			VECTOR_2D(position.x + size.x * .65f, position.y + size.y * .5f),
			VECTOR_2D(position.x + size.x * .70f, position.y + size.y * .25f),
		},
	};

	for (int t = 0; t < _TEAM_AMOUNT; t++) {
		for (int i = 0; i < PLAYERS_PER_TEAM; i++) {
			self.players[t][i] = create_player(initial_positions[t][i].x,
							   initial_positions[t][i].y, t);
		}
	}
}

void draw_teams(void)
{
	for (int t = 0; t < _TEAM_AMOUNT; t++) {
		for (int i = 0; i < PLAYERS_PER_TEAM; i++) {
			draw_player(self.players[t][i]);
			draw_player_force_vector(self.players[t][i]);
		}
	}
}

void move_teams_players_to_ball(void)
{
	for (int t = 0; t < _TEAM_AMOUNT; t++) {
		for (int i = 0; i < PLAYERS_PER_TEAM; i++) {
			move_player_to_ball(self.players[t][i]);
		}
	}
}
