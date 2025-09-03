/**
 * @file field.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definições e funções relacionadas ao campo de futebol
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef FIELD_H
#define FIELD_H

#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

#define SCORE_PADDING_X 28
#define SCORE_PADDING_Y 8

enum goal_score {
    NO_GOAL = 0,
    GOAL_TEAM_A,
    GOAL_TEAM_B
};

void create_football_field(struct vector2d position, struct vector2d size, size_t strips_amount,
			   struct vector2d bounds);

void draw_football_field(void);

struct vector2d get_field_center(void);

struct vector2d get_field_offset(void);

struct vector2d get_field_size(void);

struct vector2d get_goal_size(void);

struct vector2d get_goal_position(int index);

struct vector2d get_small_area_size(void);

struct vector2d get_small_area_position(int index);

enum goal_score was_goal_scored(struct vector2d ball_position, float ball_radius);

void compute_goal_team_a(void);
void compute_goal_team_b(void);
#endif /* FIELD_H */
