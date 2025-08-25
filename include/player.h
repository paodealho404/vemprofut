/**
 * @file player.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definição da estrutura e funções relacionadas aos jogadores.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "vector.h"

enum team {
	TEAM_BLUE = 0,
	TEAM_RED,

	_TEAM_AMOUNT,
};

struct player {
	struct vector2d position;
	struct vector2d attractive;
	struct vector2d repulsive;
	enum team team;
};

struct player *create_player(float x, float y, enum team team);

void draw_player(struct player *player);

void draw_player_force_vector(struct player *player);

void update_attractive_force_vector_towards_ball(struct player *player,
						 struct vector2d ball_position, float d_star);

void update_repulsive_force_vector_from_other_player(struct player *player,
						     struct player *other_player, float d_star);

void update_player_position(struct player *player);

#endif /* PLAYER_H */
