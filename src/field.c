/**
 * @file field.c
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief Implementações das funções relacionadas ao campo de futebol
 * @version 0.1
 * @date 24/08/2025
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "circle.h"
#include "field.h"
#include "color.h"
#include "vector.h"
#include "opengl.h"
#include "box.h"

static struct field_data {
	struct vector2d position;
	struct vector2d size;
	struct vector2d bounds;
	struct vector2d center;
	size_t strips_amount;
} self;

const static struct field_const {
	struct color light_green;
	struct color dark_green;
	struct color white;
} constants = {
	.light_green = FROM_RGBA(95, 161, 53, 255),
	.dark_green = FROM_RGBA(55, 122, 14, 255),
	.white = FROM_RGBA(255, 255, 255, 255),
};

void create_football_field(struct vector2d position, struct vector2d size, size_t strips_amount,
			   struct vector2d bounds)
{
	self.position = position;
	self.size = size;
	self.bounds = bounds;
	self.strips_amount = strips_amount;
	self.center = VECTOR_2D(position.x + size.x / 2.f, position.y + size.y / 2.f);
}

static void draw_strip(struct vector2d pos, struct vector2d size, struct color color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_POLYGON);
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x + size.x, pos.y);
	glVertex2f(pos.x + size.x, pos.y + size.y);
	glVertex2f(pos.x, pos.y + size.y);
	glEnd();
}

static void draw_outline(struct vector2d offset)
{
	draw_box(offset, self.bounds, constants.white);
}

static void draw_area_markings(struct vector2d offset)
{
	struct vector2d area_size = {self.bounds.x * .15f, self.bounds.y * .55f};
	struct vector2d small_area_size = {area_size.x * .5f, area_size.y * .5f};

	draw_box(VECTOR_2D(offset.x, offset.y + self.bounds.y / 2.f - area_size.y / 2.f), area_size,
		 constants.white);
	draw_box(VECTOR_2D(offset.x, offset.y + self.bounds.y / 2.f - small_area_size.y / 2.f),
		 small_area_size, constants.white);
	draw_circle_filled(VECTOR_2D(offset.x + (area_size.x + small_area_size.x) / 2.f,
				     offset.y + self.bounds.y / 2.f),
			   (small_area_size.x + small_area_size.y) * .03f / 2.f, constants.white);
	draw_arc(VECTOR_2D(offset.x + area_size.x * .7f, offset.y + self.bounds.y / 2.f),
		 small_area_size.y / 2.f, 301.0, 420.0, constants.white);

	draw_box(VECTOR_2D(offset.x + self.bounds.x - area_size.x,
			   offset.y + self.bounds.y / 2.f - area_size.y / 2.f),
		 area_size, constants.white);
	draw_box(VECTOR_2D(offset.x + self.bounds.x - small_area_size.x,
			   offset.y + self.bounds.y / 2.f - small_area_size.y / 2.f),
		 small_area_size, constants.white);
	draw_circle_filled(
		VECTOR_2D(offset.x + self.bounds.x - (area_size.x + small_area_size.x) / 2.f,
			  offset.y + self.bounds.y / 2.f),
		(small_area_size.x + small_area_size.y) * .03f / 2.f, constants.white);
	draw_arc(VECTOR_2D(offset.x - area_size.x * .7f + self.bounds.x,
			   offset.y + self.bounds.y / 2.f),
		 small_area_size.y / 2.f, 122.f, 239.f, constants.white);
}

static void draw_center_circle(struct vector2d offset)
{
	struct vector2d center = {
		offset.x + self.bounds.x / 2.f,
		offset.y + self.bounds.y / 2.f,
	};
	float radius = self.bounds.y * .3f / 2.f;

	glBegin(GL_LINES);
	glVertex2f(offset.x + self.bounds.x / 2.f, offset.y);
	glVertex2f(offset.x + self.bounds.x / 2.f, offset.y + self.bounds.y);
	glEnd();

	draw_circle(center, radius, constants.white);
	draw_circle_filled(center, radius * .1f, constants.white);
}

static void draw_goals(struct vector2d offset)
{
	struct vector2d goal_size = {(self.size.x - self.bounds.x) / 2.f * .6f,
				     self.bounds.y * .15f};

	draw_box(VECTOR_2D(offset.x - goal_size.x,
			   offset.y + self.bounds.y / 2.f - goal_size.y / 2.0),
		 goal_size, constants.white);
	draw_box(VECTOR_2D(offset.x + self.bounds.x,
			   offset.y + self.bounds.y / 2.f - goal_size.y / 2.0),
		 goal_size, constants.white);
}

void draw_football_field()
{
	float strip_width = self.size.x / ((float)self.strips_amount);
	struct color current_color;

	for (int i = 0; i < self.strips_amount; i++) {
		if (i % 2 == 0) {
			current_color = constants.light_green;
		} else {
			current_color = constants.dark_green;
		}

		struct vector2d strip_pos = self.position;
		strip_pos.x += ((float)i) * strip_width;
		struct vector2d strip_size = {strip_width, self.size.y};

		draw_strip(strip_pos, strip_size, current_color);
	}

	float remaining_width = self.size.x - self.bounds.x;
	float remaining_height = self.size.y - self.bounds.y;
	struct vector2d offset = {
		self.position.x + remaining_width / 2.f,
		self.position.y + remaining_height / 2.f,
	};

	draw_outline(offset);
	draw_area_markings(offset);
	draw_center_circle(offset);
	draw_goals(offset);
}

struct vector2d get_field_center(void)
{
	return self.center;
}
