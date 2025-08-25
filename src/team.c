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
#include <stdbool.h>

static struct team_data {
	struct player *players[_TEAM_AMOUNT * PLAYERS_PER_TEAM];
	bool debug;
} self;

void init_teams(struct vector2d position, struct vector2d size)
{
	struct vector2d initial_positions[_TEAM_AMOUNT * PLAYERS_PER_TEAM] = {
		// Blue Team
		// Goalkeeper
		VECTOR_2D(position.x, position.y + size.y * .5f),
		// Players
		VECTOR_2D(position.x + size.x * .35f, position.y + size.y * .75f),
		VECTOR_2D(position.x + size.x * .40f, position.y + size.y * .5f),
		VECTOR_2D(position.x + size.x * .35f, position.y + size.y * .25f),
		VECTOR_2D(position.x + size.x * .20f, position.y + size.y * .75f),
		VECTOR_2D(position.x + size.x * .15f, position.y + size.y * .5f),
		VECTOR_2D(position.x + size.x * .20f, position.y + size.y * .25f),

		// Red Team
		// Goalkeeper
		VECTOR_2D(position.x + size.x, position.y + size.y * .5f),
		// Players
		VECTOR_2D(position.x + size.x * .85f, position.y + size.y * .75f),
		VECTOR_2D(position.x + size.x * .90f, position.y + size.y * .5f),
		VECTOR_2D(position.x + size.x * .85f, position.y + size.y * .25f),
		VECTOR_2D(position.x + size.x * .70f, position.y + size.y * .75f),
		VECTOR_2D(position.x + size.x * .65f, position.y + size.y * .5f),
		VECTOR_2D(position.x + size.x * .70f, position.y + size.y * .25f),
	};

	for (int i = 0; i < PLAYERS_PER_TEAM * _TEAM_AMOUNT; i++) {
		self.players[i] = create_player(initial_positions[i].x, initial_positions[i].y,
						i < PLAYERS_PER_TEAM ? TEAM_BLUE : TEAM_RED);
	}
}

void draw_teams(void)
{
	for (int i = 0; i < PLAYERS_PER_TEAM * _TEAM_AMOUNT; i++) {
		draw_player(self.players[i]);
		if (self.debug) {
			draw_player_force_vector(self.players[i]);
		}
	}
}

void update_teams_positions(struct vector2d ball_position)
{
	for (int i = 0; i < PLAYERS_PER_TEAM * _TEAM_AMOUNT; i++) {
		update_attractive_force_vector_towards_ball(self.players[i], ball_position, 5);
		self.players[i]->repulsive.x = 0;
		self.players[i]->repulsive.y = 0;

		for (int j = 0; j < PLAYERS_PER_TEAM; j++) {
			if (i == j) {
				continue;
			}

			// TODO: Handle Goalkeeper differently

			update_repulsive_force_vector_from_other_player(self.players[i],
									self.players[j], 50);
			update_player_position(self.players[i]);
		}
	}
}

void team_toggle_debug(void)
{
	self.debug = !self.debug;
}
