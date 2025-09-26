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

/**
 * @brief Inicializa os times com posições no campo
 * @param position Posição base para inicialização
 * @param size Tamanho da área de jogo
 */
void init_teams(struct vector2d position, struct vector2d size);

/**
 * @brief Desenha todos os times na tela
 */
void draw_teams(void);

/**
 * @brief Atualiza as posições de todos os jogadores dos times
 * @param ball_position Posição atual da bola
 */
void update_teams_positions(struct vector2d ball_position);

/**
 * @brief Atualiza as animações de todos os jogadores dos times
 */
void update_teams_animations(void);

/**
 * @brief Alterna o modo de debug dos times
 */
void team_toggle_debug(void);

#endif /* TEAM_H */
