#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION // Silence OpenGL deprecation warnings on macOS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "futebol.h"
#define WIN_WIDTH 500
#define WIN_HEIGHT 400
#define FIELD_STRIPS 16
#define STRIP_OFFSET WIN_WIDTH / FIELD_STRIPS
#define MAX_PLAYERS 12
#define DBG_SCALE 30
#define CLAMP_GOAL_HEIGHT(_val)                                                \
  ((_val) > (WIN_HEIGHT / 3)                                                   \
       ? ((_val < 2 * WIN_HEIGHT / 3) ? (_val) : (2 * WIN_HEIGHT / 3))         \
       : (WIN_HEIGHT / 3))
void evalAttractiveForceVectorTowardsBall(struct Player *player, float d_star);

struct Ball ball = {0.0, 0.0, 10.0};
struct Scoreboard score = {
    .scoreBlackWhiteTeam = 0,
    .scoreRedBlackTeam = 0,
};

struct Player players[MAX_PLAYERS] = {[0] = {.x = 15,
                                             .y = WIN_HEIGHT / 2,
                                             .team = RED_BLACK,
                                             .attractive = {0.0, 0.0}},
                                      [1] = {.x = 50.0,
                                             .y = 50.0,
                                             .team = RED_BLACK,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [2] = {.x = 50.0,
                                             .y = 100.0,
                                             .team = RED_BLACK,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [3] = {.x = 50.0,
                                             .y = 150.0,
                                             .team = RED_BLACK,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [4] = {.x = 50.0,
                                             .y = 200.0,
                                             .team = RED_BLACK,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [5] = {.x = 75.0,
                                             .y = 200.0,
                                             .team = RED_BLACK,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [6] = {.x = WIN_WIDTH - 15,
                                             .y = WIN_HEIGHT / 2,
                                             .team = BLACK_WHITE,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [7] = {.x = 450.0,
                                             .y = 50.0,
                                             .team = BLACK_WHITE,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [8] = {.x = 450.0,
                                             .y = 100.0,
                                             .team = BLACK_WHITE,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [9] = {.x = 450.0,
                                             .y = 150.0,
                                             .team = BLACK_WHITE,
                                             .attractive = {0.0, 0.0},
                                             .repulsive = {0, 0}},
                                      [10] = {.x = 450.0,
                                              .y = 200.0,
                                              .team = BLACK_WHITE,
                                              .attractive = {0.0, 0.0},
                                              .repulsive = {0, 0}},
                                      [11] = {.x = 425.0,
                                              .y = 200.0,
                                              .team = BLACK_WHITE,
                                              .attractive = {0.0, 0.0},
                                              .repulsive = {0, 0}}};

void drawForceVector(struct Player player) {
  return;

  glPushMatrix();
  glColor3f(0.1, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(player.x, player.y);
  glVertex2f(player.x + (DBG_SCALE * player.attractive.x),
             player.y + (DBG_SCALE * player.attractive.y));
  glVertex2f(player.x + (DBG_SCALE * player.attractive.x),
             player.y + (DBG_SCALE * player.attractive.y + 4));
  glVertex2f(player.x, player.y + 8);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(player.x, player.y);
  glVertex2f(player.x + (DBG_SCALE * player.repulsive.x),
             player.y + (DBG_SCALE * player.repulsive.y));
  glVertex2f(player.x + (DBG_SCALE * player.repulsive.x),
             player.y + (DBG_SCALE * player.repulsive.y + 4));
  glVertex2f(player.x, player.y + 8);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(player.x, player.y);
  glVertex2f(
      player.x + (DBG_SCALE * (player.attractive.x - player.repulsive.x)),
      player.y + (DBG_SCALE * (player.attractive.y - player.repulsive.y)));
  glVertex2f(
      player.x + (DBG_SCALE * (player.attractive.x - player.repulsive.x)),
      player.y + (DBG_SCALE * (player.attractive.y - player.repulsive.y) + 4));
  glVertex2f(player.x, player.y + 8);
  glEnd();
  glPopMatrix();
}

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT);
}

void drawScoreboard() {}

void drawGoal() {}

void drawBall() {}

void drawRedBlackTeam() {
  // goal keeper
  // generic player
}

void drawBlackWhiteTeam() {
  // goal keeper
  // generic player
}

void drawPlayers() {
  drawRedBlackTeam();
  drawBlackWhiteTeam();
}

void drawFootballField() {
  // color rgba(95, 161, 53, 1)
  // color rgba(55, 122, 14, 1)

  for (int i = 0; i < FIELD_STRIPS / 2; i++) {
    glColor3f(95 / 255.0, 161 / 255.0, 53 / 255.0);
    glBegin(GL_POLYGON);
    glVertex2f(STRIP_OFFSET * i * 2, 0);
    glVertex2f(STRIP_OFFSET * i * 2, WIN_HEIGHT);
    glVertex2f(STRIP_OFFSET * i * 2 + STRIP_OFFSET, WIN_HEIGHT);
    glVertex2f(STRIP_OFFSET * i * 2 + STRIP_OFFSET, 0);
    glEnd();
  }

  for (int i = 0; i < FIELD_STRIPS / 2; i++) {
    glColor3f(55 / 255.0, 122 / 255.0, 14 / 255.0);
    glBegin(GL_POLYGON);
    glVertex2f(STRIP_OFFSET * (2 * i + 1), 0);
    glVertex2f(STRIP_OFFSET * (2 * i + 1), WIN_HEIGHT);
    glVertex2f(STRIP_OFFSET * (2 * i + 1) + STRIP_OFFSET, WIN_HEIGHT);
    glVertex2f(STRIP_OFFSET * (2 * i + 1) + STRIP_OFFSET, 0);
    glEnd();
  }

  drawBall();
  drawScoreboard();
  drawPlayers();
}
void display(void) {
  /* Limpar todos os pixels */
  glClear(GL_COLOR_BUFFER_BIT);
  /* Desenhar os polígonos */
  drawFootballField();
  /* Não esperar! */
  glFlush();
}

void idle(void) { glutPostRedisplay(); }

void keyboard(unsigned char key, int x, int y) {
  printf("Tecla pressionada: %d\n", key);
  if (key == 'w' || key == 'W') {
    glutPostRedisplay();
  }

  if (key == 's' || key == 'S') {
    glutPostRedisplay();
  }

  if (key == 'a' || key == 'A') {
    glutPostRedisplay();
  }

  if (key == 'd' || key == 'D') {
    glutPostRedisplay();
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

int main(int argc, char **argv) {
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

  /* C ANSI requer que main retorne um inteiro */
  return 0;
}
