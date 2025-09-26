/**
 * @file ball.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definição da estrutura da bola e funções relacionadas.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef BALL_H
#define BALL_H

#include "vector.h"

#define BALL_RADIUS 10.0f

/**
 * @brief Desenha a bola na tela
 */
void draw_ball(void);

/**
 * @brief Move a bola em uma direção específica
 * @param direction Vetor de direção para movimentar a bola
 */
void move_ball(struct vector2d direction);

/**
 * @brief Define a posição da bola
 * @param position Nova posição da bola
 */
void set_ball_position(struct vector2d position);

/**
 * @brief Obtém a posição atual da bola
 * @return Posição atual da bola
 */
struct vector2d get_ball_position(void);

#endif /* BALL_H */
