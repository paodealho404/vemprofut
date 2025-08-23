#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "futebol.h"
#define WIN_WIDTH 500
#define WIN_HEIGHT 400
#define FIELD_STRIPS 16
#define STRIP_OFFSET WIN_WIDTH / FIELD_STRIPS
#define MAX_PLAYERS 12
#define DBG_SCALE 30
#define CLAMP_GOAL_HEIGHT(_val) ((_val) > (WIN_HEIGHT / 3) ? ((_val < 2 * WIN_HEIGHT / 3) ? (_val) : (2 * WIN_HEIGHT / 3)) : (WIN_HEIGHT / 3))
void evalAttractiveForceVectorTowardsBall(struct Player *player, float d_star);

struct Ball ball = {0.0, 0.0, 10.0};
struct Scoreboard score = {
    .scoreBlackWhiteTeam = 0,
    .scoreRedBlackTeam = 0,
};

struct Player players[MAX_PLAYERS] = {
    [0] = {
        .x = 15,
        .y = WIN_HEIGHT / 2,
        .team = RED_BLACK,
        .attractive = {0.0, 0.0}},
    [1] = {.x = 50.0, .y = 50.0, .team = RED_BLACK, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [2] = {.x = 50.0, .y = 100.0, .team = RED_BLACK, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [3] = {.x = 50.0, .y = 150.0, .team = RED_BLACK, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [4] = {.x = 50.0, .y = 200.0, .team = RED_BLACK, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [5] = {.x = 75.0, .y = 200.0, .team = RED_BLACK, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [6] = {.x = WIN_WIDTH - 15, .y = WIN_HEIGHT / 2, .team = BLACK_WHITE, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [7] = {.x = 450.0, .y = 50.0, .team = BLACK_WHITE, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [8] = {.x = 450.0, .y = 100.0, .team = BLACK_WHITE, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [9] = {.x = 450.0, .y = 150.0, .team = BLACK_WHITE, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [10] = {.x = 450.0, .y = 200.0, .team = BLACK_WHITE, .attractive = {0.0, 0.0}, .repulsive = {0, 0}},
    [11] = {.x = 425.0, .y = 200.0, .team = BLACK_WHITE, .attractive = {0.0, 0.0}, .repulsive = {0, 0}}};

void drawForceVector(struct Player player)
{
    return;

    glPushMatrix();
    glColor3f(0.1, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(player.x, player.y);
    glVertex2f(player.x + (DBG_SCALE * player.attractive.x), player.y + (DBG_SCALE * player.attractive.y));
    glVertex2f(player.x + (DBG_SCALE * player.attractive.x), player.y + (DBG_SCALE * player.attractive.y + 4));
    glVertex2f(player.x, player.y + 8);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(player.x, player.y);
    glVertex2f(player.x + (DBG_SCALE * player.repulsive.x), player.y + (DBG_SCALE * player.repulsive.y));
    glVertex2f(player.x + (DBG_SCALE * player.repulsive.x), player.y + (DBG_SCALE * player.repulsive.y + 4));
    glVertex2f(player.x, player.y + 8);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(player.x, player.y);
    glVertex2f(player.x + (DBG_SCALE * (player.attractive.x - player.repulsive.x)), player.y + (DBG_SCALE * (player.attractive.y - player.repulsive.y)));
    glVertex2f(player.x + (DBG_SCALE * (player.attractive.x - player.repulsive.x)), player.y + (DBG_SCALE * (player.attractive.y - player.repulsive.y) + 4));
    glVertex2f(player.x, player.y + 8);
    glEnd();
    glPopMatrix();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT);
}

void drawScoreboard()
{
    return;
}

void drawGoal()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0);

    glBegin(GL_LINE_STRIP);
    glVertex2f(0, WIN_HEIGHT / 3);
    glVertex2f(STRIP_OFFSET, WIN_HEIGHT / 3);
    glVertex2f(STRIP_OFFSET, 2 * WIN_HEIGHT / 3);
    glVertex2f(0, 2 * WIN_HEIGHT / 3);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0);

    glBegin(GL_LINE_STRIP);
    glVertex2f(WIN_WIDTH, WIN_HEIGHT / 3);
    glVertex2f(WIN_WIDTH - STRIP_OFFSET, WIN_HEIGHT / 3);
    glVertex2f(WIN_WIDTH - STRIP_OFFSET, 2 * WIN_HEIGHT / 3);
    glVertex2f(WIN_WIDTH, 2 * WIN_HEIGHT / 3);

    glEnd();
    glPopMatrix();
}

void checkGoal()
{
    if (ball.x >= 0 && ball.x < STRIP_OFFSET && (ball.y > WIN_HEIGHT / 3 && ball.y < 2 * WIN_HEIGHT / 3))
    {
        printf("Goal from black white\n");
        score.scoreBlackWhiteTeam += 1;
    }
    if (ball.x >= WIN_WIDTH - STRIP_OFFSET && ball.x < WIN_WIDTH && (ball.y > WIN_HEIGHT / 3 && ball.y < 2 * WIN_HEIGHT / 3))
    {
        printf("Goal from red black\n");
        score.scoreRedBlackTeam += 1;
    }
}

void drawBall()
{
    glColor3f(1.0, 1.0, 1.0);

    float x = ball.x;
    float y = ball.y;
    float radius = ball.radius;
    int num_segments = 8;

    glPushMatrix();
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        if (i % (num_segments >> 1))
        {
            glColor3f(1.0, 1.0, 1.0);
        }
        else {
            glColor3f(0.0, 0.0, 0.0);

        }
        float theta = 2.0f * 3.1415926f * i / (float)num_segments;
        float dx = radius * cos(theta);
        float dy = radius * sin(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}

void drawPlayer(int x, int y, enum Team team, bool isGoalkeeper)
{
    if (team == RED_BLACK)
    {
        if (isGoalkeeper)
        {
            glColor3f(0.1, 0.1, 0.1); // Magenta for goalkeeper
        }
        else
        {
            glColor3f(1.0, 0.0, 0.0); // Green for other players
        }
    }
    else
    {
        if (isGoalkeeper)
        {
            glColor3f(1.0, 1.0, 1.0);
        }
        else
        {
            glColor3f(0, 0, 0);
        }
    }

    glBegin(GL_QUADS);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x + 10, y - 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x - 10, y + 10);
    glEnd();
}
void drawRedBlackTeam()
{

    drawPlayer(players[0].x, players[0].y, RED_BLACK, true);
    drawForceVector(players[0]);

    for (int i = 1; i < MAX_PLAYERS / 2; i++)
    {
        drawPlayer(players[i].x, players[i].y, RED_BLACK, false);
        drawForceVector(players[i]);
    }
}

void drawBlackWhiteTeam()
{
    drawPlayer(players[6].x, players[6].y, BLACK_WHITE, true);
    drawForceVector(players[6]);

    for (int i = 7; i < MAX_PLAYERS; i++)
    {
        drawPlayer(players[i].x, players[i].y, BLACK_WHITE, false);
        drawForceVector(players[i]);
    }
}

void drawPlayers()
{
    drawRedBlackTeam();
    drawBlackWhiteTeam();
}

void drawFootballField()
{

    for (int i = 0; i < FIELD_STRIPS / 2; i++)
    {
        glColor3f(95 / 255.0, 161 / 255.0, 53 / 255.0);
        glBegin(GL_POLYGON);
        glVertex2f(STRIP_OFFSET * i * 2, 0);
        glVertex2f(STRIP_OFFSET * i * 2, WIN_HEIGHT);
        glVertex2f(STRIP_OFFSET * i * 2 + STRIP_OFFSET, WIN_HEIGHT);
        glVertex2f(STRIP_OFFSET * i * 2 + STRIP_OFFSET, 0);
        glEnd();
    }

    for (int i = 0; i < FIELD_STRIPS / 2; i++)
    {
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

void display(void)
{
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);
    /* Desenhar os polígonos */
    drawFootballField();
    drawGoal();
    /* Não esperar! */
    glFlush();
}

bool print = false;

void evalAttractiveForceVectorTowardsBall(struct Player *player, float d_star)
{
    float dist = sqrt(pow(ball.x - player->x, 2) + pow(ball.y - player->y, 2));

    if (dist < d_star)
    {
        dist = d_star;
    }

    player->attractive.x = 7 * (ball.x - player->x) / dist;
    player->attractive.y = 7 * (ball.y - player->y) / dist;
}

void evalRepulsiveForceVectorFromOtherPlayer(struct Player *player, struct Player otherPlayer, float d_star)
{
    float dist = sqrt(pow(otherPlayer.x - player->x, 2) + pow(otherPlayer.y - player->y, 2));

    if (dist < 10)
    {
        dist = 10;
    }

    if (dist < d_star)
    {
        player->repulsive.x -= 1000 * (player->x - otherPlayer.x) / dist;
        player->repulsive.y -= 1000 * (player->y - otherPlayer.y) / dist;
        return;
    }
    player->repulsive.x = 4 * (player->x - otherPlayer.x) / dist;
    player->repulsive.y = 4 * (player->y - otherPlayer.y) / dist;
}

void idle(void)
{
    // Simple collision avoidance between players (using a repulsive force vector), Make the closest players scale to the inverse of the distance between them
    // Player moves in the attractive of the resultant force vector, the sum of all repulsive force vectors from other players and an attractive force vector towards the ball

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        evalAttractiveForceVectorTowardsBall(&players[i], 5);
        players[i].repulsive.x = 0;
        players[i].repulsive.y = 0;

        glutPostRedisplay();

        for (int j = 0; j < MAX_PLAYERS; j++)
        {
            if (i == j)
                continue;

            if (i == 0 || i == 6)
            {
                players[i].y += (players[i].attractive.y - players[i].repulsive.y) / 20000;
                players[i].y = CLAMP_GOAL_HEIGHT(players[i].y);

                continue;
            }
            evalRepulsiveForceVectorFromOtherPlayer(&players[i], players[j], 50);
            players[i].x += (players[i].attractive.x - players[i].repulsive.x) / 20000;
            players[i].y += (players[i].attractive.y - players[i].repulsive.y) / 20000;
        }
    }

    checkGoal();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'w' || key == 'W')
    {
        ball.y += 5.0;
    }

    if (key == 's' || key == 'S')
    {
        ball.y -= 5.0;
    }

    if (key == 'a' || key == 'A')
    {
        ball.x -= 5.0;
    }

    if (key == 'd' || key == 'D')
    {
        ball.x += 5.0;
    }

    if (key == 27)
    {
        printf("Saindo...\n");
        glutLeaveMainLoop();
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

    /* C ANSI requer que main retorne um inteiro */
    return 0;
}
