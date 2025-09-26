/**
 * @file soundboard.h
 * @author Pedro Henrique (phbn@ic.ufal.br)
 * @brief Definições e funções relacionadas ao painel de som
 * @version 0.1
 * @date 03/09/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef SOUND_BOARD_H
#define SOUND_BOARD_H

/**
 * @brief Inicializa o sistema de som
 * @return 0 em caso de sucesso, -1 em caso de erro
 */
int init_sound_board(void);

/**
 * @brief Destrói o sistema de som e libera recursos
 */
void destroy_sound_board(void);

/**
 * @brief Toca a música de fundo
 */
void play_background_music(void);

/**
 * @brief Toca o som de gol
 */
void play_goal_sound(void);

/**
 * @brief Toca a música inicial
 */
void play_initial_music(void);

/**
 * @brief Toca o som do Tafarel
 */
void play_tafarel_sound(void);

#endif /* SOUND_BOARD_H */
