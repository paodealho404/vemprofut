#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

#define WIN_WIDTH 500
#define WIN_HEIGHT 400
#define FIELD_STRIPS 16
#define STRIP_OFFSET WIN_WIDTH / FIELD_STRIPS

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
}

void drawRedBlackTeam()
{
    // goal keeper
    // generic player
}

void drawBlackWhiteTeam()
{
    // goal keeper
    // generic player
}

void drawPlayers()
{
    drawRedBlackTeam();
    drawBlackWhiteTeam();
}

void drawFootballField()
{
    // color rgba(95, 161, 53, 1)
    // color rgba(55, 122, 14, 1)

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
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    printf("Tecla pressionada: %d\n", key);
    if (key == 'w' || key == 'W')
    {
        glutPostRedisplay();
    }

    if (key == 's' || key == 'S')
    {
        glutPostRedisplay();
    }

    if (key == 'a' || key == 'A')
    {
        glutPostRedisplay();
    }

    if (key == 'd' || key == 'D')
    {
        glutPostRedisplay();
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
