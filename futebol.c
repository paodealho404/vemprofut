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
struct Ball ball = {0.0, 0.0, 10.0};
struct ForceVector {
    float x;
    float y;
};

struct ForceVector force[MAX_PLAYERS][MAX_PLAYERS] = {};
struct Player players[MAX_PLAYERS] = {};


void drawForceVector(struct Player player, struct ForceVector forceVector)
{
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(player.x, player.y);
    glVertex2f(player.x + forceVector.x, player.y + forceVector.y);
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
}

void drawGoal()
{
}

void drawBall()
{
    glColor3f(1.0, 1.0, 1.0);

    float x = ball.x;
    float y = ball.y;
    float radius = ball.radius;
    int num_segments = 10;

    glPushMatrix();
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * i / (float ) num_segments;
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
            glColor3f(0, 0 ,0); // Magenta for goalkeeper
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
            glColor3f(0, 0,0); 

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
    // Goal keeper
    players[0].x = 100;
    players[0].y = 50;
    players[0].team = RED_BLACK;

    drawPlayer(players[0].x, players[0].y, RED_BLACK, true);

    for (int i = 1; i < MAX_PLAYERS / 2; i++)
    {
        players[i].x = 100;
        players[i].y = 50 + (i * 50);
        players[i].team = RED_BLACK;
        drawPlayer(players[i].x, players[i].y, RED_BLACK, false);
    }    


}

void drawBlackWhiteTeam()
{
    // goal keeper
    players[MAX_PLAYERS / 2].x = 400;
    players[MAX_PLAYERS / 2].y = 50;
    players[MAX_PLAYERS / 2].team = BLACK_WHITE;
    drawPlayer(players[MAX_PLAYERS / 2].x, players[MAX_PLAYERS / 2].y, BLACK_WHITE, true);

    // other players
    for (int i = MAX_PLAYERS / 2 + 1; i < MAX_PLAYERS; i++)
    {
        players[i].x = 400;
        players[i].y = 50 + ((i - MAX_PLAYERS / 2) * 50);
        players[i].team = BLACK_WHITE;
        drawPlayer(players[i].x, players[i].y, BLACK_WHITE, false);
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
    /* Não esperar! */
    glFlush();
}

void idle(void)
{
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // Example force vector update logic
            float scale = 10; // Adjust the scale as needed
            force[i][j].x = scale * (ball.x - players[i].x);
            force[i][j].y = scale * (ball.y - players[j].y);
            float magnitude = sqrt(force[i][j].x * force[i][j].x + force[i][j].y * force[i][j].y);
            if (magnitude > 0)
            {
                force[i][j].x /= magnitude;
                force[i][j].y /= magnitude;
            }

            drawForceVector(players[i], force[i][j]);
        }
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    printf("Tecla pressionada: %d\n", key);
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
