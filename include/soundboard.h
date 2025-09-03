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

int init_sound_board(void);
void destroy_sound_board(void);
void play_background_music(void);
void play_goal_sound(void);
void play_initial_music(void);
void play_tafarel_sound(void);

#endif /* SOUND_BOARD_H */
