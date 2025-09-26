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

/**
 * @brief Inicializa, sem desenhar, o campo de futebol com as especificações dadas
 * @param position Posição do campo
 * @param size Tamanho do campo
 * @param strips_amount Quantidade de listras no campo
 * @param bounds Limites dos desenhos do campo
 */
void create_football_field(struct vector2d position, struct vector2d size, size_t strips_amount,
			   struct vector2d bounds);

/**
 * @brief Desenha o campo de futebol na tela
 */
void draw_football_field(void);

/**
 * @brief Obtém o centro do campo
 * @return Posição do centro do campo
 */
struct vector2d get_field_center(void);

/**
 * @brief Obtém o offset do campo
 * @return Offset do campo
 */
struct vector2d get_field_offset(void);

/**
 * @brief Obtém o tamanho do campo
 * @return Tamanho do campo
 */
struct vector2d get_field_size(void);

/**
 * @brief Obtém o tamanho do gol
 * @return Tamanho do gol
 */
struct vector2d get_goal_size(void);

/**
 * @brief Obtém a posição de um gol específico
 * @param index Índice do gol (0 ou 1) (0 para o gol da equipe A, 1 para o gol da equipe B)
 * @return Posição do gol
 */
struct vector2d get_goal_position(int index);

/**
 * @brief Obtém o tamanho da pequena área
 * @return Tamanho da pequena área
 */
struct vector2d get_small_area_size(void);

/**
 * @brief Obtém a posição da pequena área
 * @param index Índice da pequena área (0 ou 1)
 * @return Posição da pequena área
 */
struct vector2d get_small_area_position(int index);

/**
 * @brief Verifica se um gol foi marcado
 * @param ball_position Posição da bola
 * @param ball_radius Raio da bola
 * @return Estado do gol (NO_GOAL, GOAL_TEAM_A ou GOAL_TEAM_B)
 */
enum goal_score was_goal_scored(struct vector2d ball_position, float ball_radius);

/**
 * @brief Computa um gol para o time A
 */
void compute_goal_team_a(void);

/**
 * @brief Computa um gol para o time B
 */
void compute_goal_team_b(void);
#endif /* FIELD_H */
