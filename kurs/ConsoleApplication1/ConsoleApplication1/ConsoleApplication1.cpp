#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "Game.h"
#include "glut.h"
#include <stdlib.h>



Game game;

void DisplayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    game.draw();
    glutSwapBuffers();
}

void timer(int = 0)
{
    DisplayFunc();
    game.tick();
    glutTimerFunc(50, timer, 0);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'A':
    case 'a':
        if (game.redPlayer.posX >= 2) game.redPlayer.posX--;
        break;
    case 'D':
    case 'd':
        if (game.redPlayer.posX <= game.FIELD_WIDTH - 3) game.redPlayer.posX++;
        break;
    case 'W':
    case 'w':
        if (game.redPlayer.posY >= 2) game.redPlayer.posY--;
        break;
    case 'S':
    case 's':
        if (game.redPlayer.posY <= game.FIELD_HEIGHT - 3) game.redPlayer.posY++;
        break;
    case 'Q':
    case 'q':
        if (game.redPlayersTurn)
        {
            if (game.FIELD[game.redPlayer.posY][game.redPlayer.posX] == Game::EMPTY)
            {
                game.FIELD[game.redPlayer.posY][game.redPlayer.posX] = Game::REDPLAYER;
                game.redPlayersTurn = false;
                game.bluePlayersTurn = true;
            }
        }
        break;
    case '/':
        if (game.bluePlayersTurn)
        {
            if (game.FIELD[game.bluePlayer.posY][game.bluePlayer.posX] == Game::EMPTY)
            {
                game.FIELD[game.bluePlayer.posY][game.bluePlayer.posX] = Game::BLUEPLAYER;
                game.redPlayersTurn = true;
                game.bluePlayersTurn = false;
            }
        }
        break;
    case 27:
        exit(0); 
        break;
    }
}

void SpecialFunc(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (game.bluePlayer.posX >= 2) game.bluePlayer.posX--;
        break;
    case GLUT_KEY_RIGHT:
        if (game.bluePlayer.posX <= game.FIELD_WIDTH - 3) game.bluePlayer.posX++;
        break;
    case GLUT_KEY_UP:
        if (game.bluePlayer.posY >= 2) game.bluePlayer.posY--;
        break;
    case GLUT_KEY_DOWN:
        if (game.bluePlayer.posY <= game.FIELD_HEIGHT - 3) game.bluePlayer.posY++;
        break;
    }
}

int main(int argc, char** argv)
{
    game.initGame();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(game.SCREEN_WIDTH, game.SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("POINTS THE GAME");

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game.SCREEN_WIDTH, game.SCREEN_HEIGHT, 0, -1.0, 1.0);

    glutDisplayFunc(DisplayFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(SpecialFunc);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (game.FULLSCREEN) glutFullScreen();

    timer();

    glutMainLoop();


}