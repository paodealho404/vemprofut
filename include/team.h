/**
 * @file team.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definição da estrutura e funções relacionadas aos times.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef TEAM_H
#define TEAM_H

#include "vector.h"

#define PLAYERS_PER_TEAM 7

void init_teams(struct vector2d position, struct vector2d size);

void draw_teams(void);

void move_teams_players_to_ball(void);

#endif /* TEAM_H */
