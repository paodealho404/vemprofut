#include "vector.h"
#include "opengl.h"
#include "futebol.h"
#include "field.h"
#include "ball.h"
#include "team.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIN_WIDTH    900
#define WIN_HEIGHT   600
#define FIELD_STRIPS 16

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	create_football_field(VECTOR_2D(0.0, 0.0), VECTOR_2D(WIN_WIDTH, WIN_HEIGHT), FIELD_STRIPS,
			      VECTOR_2D(WIN_WIDTH * 0.9, WIN_HEIGHT * 0.9));

	struct vector2d field_center = get_field_center();
	struct vector2d field_offset = get_field_offset();
	struct vector2d field_size = get_field_size();

	init_teams(field_offset, field_size);

	set_ball_position(field_center);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw_football_field();
	draw_teams();
	draw_ball();

	glFlush();
}

void idle(void)
{
	static clock_t start_time = 0;
	clock_t end_time;
	static double elapsed_time = 0;

	if (start_time == 0) {
		start_time = clock();
	}
	end_time = clock();

	elapsed_time += (double)(end_time - start_time) / CLOCKS_PER_SEC;

	if (elapsed_time >= .08f) {
		glutPostRedisplay();
	}

	if (elapsed_time >= .5f) {
		elapsed_time = 0;
		update_teams_animations();
	}
	start_time = end_time;

	struct vector2d ball_position = get_ball_position();

	update_teams_positions(ball_position);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W') {
		move_ball(VECTOR_2D(0, 1));
	}

	if (key == 's' || key == 'S') {
		move_ball(VECTOR_2D(0, -1));
	}

	if (key == 'a' || key == 'A') {
		move_ball(VECTOR_2D(-1, 0));
	}

	if (key == 'd' || key == 'D') {
		move_ball(VECTOR_2D(1, 0));
	}

	if (key == 'g' || key == 'G') {
		printf("Toggle debug mode\n");
		team_toggle_debug();
	}

	if (key == 27) {
		printf("Saindo...\n");
#ifdef __APPLE__
		exit(0); // glutLeaveMainLoop is not available on macOS
#else
		glutLeaveMainLoop();
#endif
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Vem pro FUT");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
