/**
 * @file box.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definições e funções relacionadas a rectagulos.
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef BOX_H
#define BOX_H

#include "vector.h"
#include "color.h"

/**
 * @brief Desenha um retângulo sem preenchimento na tela
 * @param pos Posição do retângulo
 * @param size Tamanho do retângulo
 * @param color Cor do retângulo
 */
void draw_box(struct vector2d pos, struct vector2d size, struct color color);

#endif /* BOX_H */
