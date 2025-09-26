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
#include <stdint.h>
#include <stdbool.h>

enum team {
	TEAM_BLUE = 0,
	TEAM_RED,

	_TEAM_AMOUNT,
};

struct player {
	struct vector2d position;
	struct vector2d last_position;
	struct vector2d attractive;
	struct vector2d repulsive;
	enum team team;
	uint8_t sprite_index;
	bool is_goalkeeper;
};

/**
 * @brief Cria um novo jogador
 * @param x Posição X inicial do jogador
 * @param y Posição Y inicial do jogador
 * @param team Time do jogador
 * @return Ponteiro para o jogador criado
 */
struct player *create_player(float x, float y, enum team team);

/**
 * @brief Desenha o jogador na tela
 * @param player Ponteiro para o jogador a ser desenhado
 */
void draw_player(struct player *player);

/**
 * @brief Atualiza a animação do jogador
 * @param player Ponteiro para o jogador
 */
void update_animation(struct player *player);

/**
 * @brief Desenha o vetor de força do jogador
 * @param player Ponteiro para o jogador
 */
void draw_player_force_vector(struct player *player);

/**
 * @brief Atualiza o vetor de força atrativa em direção à bola
 * @param player Ponteiro para o jogador
 * @param ball_position Posição da bola
 * @param d_star Distância de referência para o cálculo da força
 */
void update_attractive_force_vector_towards_ball(struct player *player,
						 struct vector2d ball_position, float d_star);

/**
 * @brief Atualiza o vetor de força repulsiva de outro jogador
 * @param player Ponteiro para o jogador atual
 * @param other_player Ponteiro para o outro jogador
 * @param d_star Distância de referência para o cálculo da força
 */
void update_repulsive_force_vector_from_other_player(struct player *player,
						     struct player *other_player, float d_star);

/**
 * @brief Atualiza a posição do jogador baseada nas forças aplicadas
 * @param player Ponteiro para o jogador
 */
void update_player_position(struct player *player);

/**
 * @brief Atualiza a posição do goleiro dentro da pequena área
 * @param player Ponteiro para o jogador goleiro
 * @param smal_area_pos Posição da pequena área
 * @param small_area_size Tamanho da pequena área
 */
void update_goalkeeper_position(struct player *player, struct vector2d smal_area_pos,
				struct vector2d small_area_size);

#endif /* PLAYER_H */
