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

#include <stdio.h>
#include <string.h>

#define SCOREBOARD_WIDTH 110
#define SCOREBOARD_HEIGHT 30

struct score {
	int team_a;
	int team_b;
};

static struct field_data {
	struct vector2d position;
	struct vector2d size;
	struct vector2d bounds;
	struct vector2d center;
	struct vector2d offset;
	struct vector2d goal_size;
	struct vector2d goal_position[2];
	struct vector2d small_area_size;
	struct vector2d small_area_position[2];
	size_t strips_amount;
    struct score team_scores;
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

	float remaining_width = self.size.x - self.bounds.x;
	float remaining_height = self.size.y - self.bounds.y;
	self.offset.x = self.position.x + remaining_width / 2.f;
	self.offset.y = self.position.y + remaining_height / 2.f;

	self.goal_size = VECTOR_2D((self.size.x - self.bounds.x) / 2.f * .6f, self.bounds.y * .15f);
	self.goal_position[0] =
		VECTOR_2D(self.offset.x - self.goal_size.x,
			  self.offset.y + self.bounds.y / 2.f - self.goal_size.y / 2.0);
	self.goal_position[1] =
		VECTOR_2D(self.offset.x + self.bounds.x,
			  self.offset.y + self.bounds.y / 2.f - self.goal_size.y / 2.0);

	self.small_area_size = VECTOR_2D(self.bounds.x * .15f / 2.f, self.bounds.y * .55f / 2.f);
	self.small_area_position[0] = VECTOR_2D(
		self.offset.x, self.offset.y + self.bounds.y / 2.f - self.small_area_size.y / 2.f);
	self.small_area_position[1] =
		VECTOR_2D(self.offset.x + self.bounds.x - self.small_area_size.x,
			  self.offset.y + self.bounds.y / 2.f - self.small_area_size.y / 2.f);
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

static void draw_outline(void)
{
	draw_box(self.offset, self.bounds, constants.white);
}

static void draw_area_markings(void)
{
	struct vector2d area_size = {self.bounds.x * .15f, self.bounds.y * .55f};

	draw_box(VECTOR_2D(self.offset.x, self.offset.y + self.bounds.y / 2.f - area_size.y / 2.f),
		 area_size, constants.white);
	draw_box(self.small_area_position[0], self.small_area_size, constants.white);
	draw_circle_filled(VECTOR_2D(self.offset.x + (area_size.x + self.small_area_size.x) / 2.f,
				     self.offset.y + self.bounds.y / 2.f),
			   (self.small_area_size.x + self.small_area_size.y) * .03f / 2.f,
			   constants.white, true);
	draw_arc(VECTOR_2D(self.offset.x + area_size.x * .7f, self.offset.y + self.bounds.y / 2.f),
		 self.small_area_size.y / 2.f, 301.0, 420.0, constants.white);

	draw_box(VECTOR_2D(self.offset.x + self.bounds.x - area_size.x,
			   self.offset.y + self.bounds.y / 2.f - area_size.y / 2.f),
		 area_size, constants.white);
	draw_box(self.small_area_position[1], self.small_area_size, constants.white);
	draw_circle_filled(VECTOR_2D(self.offset.x + self.bounds.x -
					     (area_size.x + self.small_area_size.x) / 2.f,
				     self.offset.y + self.bounds.y / 2.f),
			   (self.small_area_size.x + self.small_area_size.y) * .03f / 2.f,
			   constants.white, true);
	draw_arc(VECTOR_2D(self.offset.x - area_size.x * .7f + self.bounds.x,
			   self.offset.y + self.bounds.y / 2.f),
		 self.small_area_size.y / 2.f, 122.f, 239.f, constants.white);
}

static void draw_center_circle(void)
{
	struct vector2d center = {
		self.offset.x + self.bounds.x / 2.f,
		self.offset.y + self.bounds.y / 2.f,
	};
	float radius = self.bounds.y * .3f / 2.f;

	glBegin(GL_LINES);
	glVertex2f(self.offset.x + self.bounds.x / 2.f, self.offset.y);
	glVertex2f(self.offset.x + self.bounds.x / 2.f, self.offset.y + self.bounds.y);
	glEnd();

	draw_circle(center, radius, constants.white);
	draw_circle_filled(center, radius * .1f, constants.white, true);
}

static void draw_goals(void)
{
	draw_box(self.goal_position[0], self.goal_size, constants.white);
	draw_box(self.goal_position[1], self.goal_size, constants.white);
}

static void draw_text(float x, float y, const char *text) {
    glColor4f(0,0,0,1.0);
    glRasterPos3f(x, y, 0.0);

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
}


static void draw_scoreboard(int score_x_pos, int score_y_pos, int score_width, int score_height){
    glColor4f(constants.white.r, constants.white.g, constants.white.b, constants.white.a);

    glBegin(GL_QUADS);
    glVertex2f(score_x_pos - score_width, score_y_pos - score_height);
    glVertex2f(score_x_pos - score_width, score_y_pos);
    glVertex2f(score_x_pos, score_y_pos);
    glVertex2f(score_x_pos, score_y_pos - score_height);
    glEnd();

    // Draw the scores
    char score_text[32];
    snprintf(score_text, sizeof(score_text), "%d  -  %d", self.team_scores.team_a, self.team_scores.team_b);
    draw_text(score_x_pos - ((score_width + strlen(score_text)) / 2.0) - SCORE_PADDING_X , score_y_pos - (score_height / 2) - SCORE_PADDING_Y, score_text);
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

	glLineWidth(3.f);
	draw_outline();
	draw_area_markings();
	draw_center_circle();
	draw_goals();
    draw_scoreboard(self.center.x + (SCOREBOARD_WIDTH / 2), self.size.y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
}

struct vector2d get_field_center(void)
{
	return self.center;
}

struct vector2d get_field_offset(void)
{
	return self.offset;
}

struct vector2d get_field_size(void)
{
	return self.bounds;
}

struct vector2d get_goal_size(void)
{
	return self.goal_size;
}

struct vector2d get_goal_position(int index)
{
	if (index != 0 && index != 1) {
		return VECTOR_2D(0, 0);
	}

	return self.goal_position[index];
}

struct vector2d get_small_area_size(void)
{
	return self.small_area_size;
}

struct vector2d get_small_area_position(int index)
{
	if (index != 0 && index != 1) {
		return VECTOR_2D(0, 0);
	}

	return self.small_area_position[index];
}

enum goal_score was_goal_scored(struct vector2d ball_position, float ball_radius)
{
	if (ball_position.x - (ball_radius/2) >= self.goal_position[0].x && ball_position.x + (ball_radius/2) <= self.goal_position[0].x + self.goal_size.x &&
		ball_position.y - (ball_radius/2) >= self.goal_position[0].y && ball_position.y + (ball_radius/2) <= self.goal_position[0].y + self.goal_size.y) {
		return GOAL_TEAM_B;
	}

	if (ball_position.x - (ball_radius/2) >= self.goal_position[1].x && ball_position.x + (ball_radius/2) <= self.goal_position[1].x + self.goal_size.x &&
		ball_position.y - (ball_radius/2) >= self.goal_position[1].y && ball_position.y + (ball_radius/2) <= self.goal_position[1].y + self.goal_size.y) {
		return GOAL_TEAM_A;
	}

	return NO_GOAL;
}

void compute_goal_team_a(void)
{
	self.team_scores.team_a++;
}

void compute_goal_team_b(void)
{
	self.team_scores.team_b++;
}