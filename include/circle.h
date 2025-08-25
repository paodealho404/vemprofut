/**
 * @file circle.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definições e funções relacionadas a desenho de círculos e arcos
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CIRCLE_H
#define CIRCLE_H

#include "vector.h"
#include "color.h"

void draw_circle(struct vector2d center, float radius, struct color color);

void draw_circle_filled(struct vector2d center, float radius, struct color color);

void draw_arc(struct vector2d center, float radius, float start_angle, float end_angle,
	      struct color color);

#endif /* CIRCLE_H */