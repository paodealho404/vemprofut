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

#include <stdbool.h>

/**
 * @brief Desenha um círculo vazio na tela
 * @param center Centro do círculo
 * @param radius Raio do círculo
 * @param color Cor do círculo
 */
void draw_circle(struct vector2d center, float radius, struct color color);

/**
 * @brief Desenha um círculo preenchido na tela
 * @param center Centro do círculo
 * @param radius Raio do círculo
 * @param color Cor do círculo
 * @param homogeneous Se verdadeiro, usa preenchimento homogêneo
 */
void draw_circle_filled(struct vector2d center, float radius, struct color color, bool homogeneous);

/**
 * @brief Desenha um arco não preenchido na tela
 * @param center Centro do arco
 * @param radius Raio do arco
 * @param start_angle Ângulo inicial do arco
 * @param end_angle Ângulo final do arco
 * @param color Cor do arco
 */
void draw_arc(struct vector2d center, float radius, float start_angle, float end_angle,
	      struct color color);

#endif /* CIRCLE_H */