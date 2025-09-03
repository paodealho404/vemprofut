/**
 * @file vector.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Definições e funções relacionadas a vetores
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_2D(_x, _y)                                                                          \
	(struct vector2d)                                                                          \
	{                                                                                          \
		(_x), (_y)                                                                         \
	}

struct vector2d {
	float x;
	float y;
};

#endif /* VECTOR_H */
