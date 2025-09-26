/**
 * @file circle.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementações das funções relacionadas a desenho de círculos e arcos
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "circle.h"
#include "opengl.h"
#include <math.h>

#define NUM_SEGS 360
#define PI       3.1415926f

static const float theta = 2 * PI / (float)NUM_SEGS;

/**
 * @brief Desenha um círculo vazio na tela
 * @param center Centro do círculo
 * @param radius Raio do círculo
 * @param color Cor do círculo
 */
void draw_circle(struct vector2d center, float radius, struct color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < NUM_SEGS; i++) {
		float x = radius * (float)cos((float)i * theta);
		float y = radius * (float)sin((float)i * theta);
		glVertex2f(x + center.x, y + center.y);
	}
	glEnd();
}

/**
 * @brief Desenha um círculo preenchido na tela
 * @param center Centro do círculo
 * @param radius Raio do círculo
 * @param color Cor do círculo
 * @param homogeneous Se verdadeiro, usa preenchimento homogêneo
 */
void draw_circle_filled(struct vector2d center, float radius, struct color color, bool homogeneous)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_POLYGON);
	for (int i = 0; i < NUM_SEGS; i++) {
		if (!homogeneous) {
			if (i % (NUM_SEGS >> 5) == 0) {
				glColor4f(color.r, color.g, color.b, color.a);
			} else {
				glColor4f(1.0 - color.r, 1.0 - color.g, 1.0 - color.b, color.a);
			}
		}

		float x = radius * (float)cos((float)i * theta);
		float y = radius * (float)sin((float)i * theta);
		glVertex2f(x + center.x, y + center.y);
	}
	glEnd();
}

/**
 * @brief Desenha um arco na tela
 * @param center Centro do arco
 * @param radius Raio do arco
 * @param start_angle Ângulo inicial do arco
 * @param end_angle Ângulo final do arco
 * @param color Cor do arco
 */
void draw_arc(struct vector2d center, float radius, float start_angle, float end_angle,
	      struct color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_STRIP);
	for (float angle = start_angle; angle <= end_angle; angle += 1.0f) {
		float x = radius * (float)cos(angle * (PI / 180.0f));
		float y = radius * (float)sin(angle * (PI / 180.0f));
		glVertex2f(x + center.x, y + center.y);
	}
	glEnd();
}