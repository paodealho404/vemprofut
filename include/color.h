/**
 * @file color.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definições e funções relacionadas às cores
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define FROM_RGBA(r, g, b, a) {r / 255.0, g / 255.0, b / 255.0, a / 255.0}

#define COLOR_EQ(c1, c2) ((c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a))

struct color {
	float r; // Componente vermelha
	float g; // Componente verde
	float b; // Componente azul
	float a; // Componente alfa (transparência)
};

struct color fromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

struct color fromHex(const char *hexValue);

#endif /* COLOR_H */
