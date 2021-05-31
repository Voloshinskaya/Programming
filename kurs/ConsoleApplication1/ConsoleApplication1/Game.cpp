#include <iostream>
#include <conio.h>
#include <math.h>
#include <cstdlib>

#include "Game.h"
#include "glut.h"
#include <stdlib.h>

Game::Game()
{
    redPlayersTurn = true;
    bluePlayersTurn = false;

    Y[0] = 0; Y[1] = 1; Y[2] = 1; Y[3] = 1;
    X[0] = 1; X[1] = 0; X[2] = 1; X[3] = -1;
}

Game::~Game()
{
    for (int i = 0; i < FIELD_HEIGHT; i++) delete[] FIELD[i];
    delete[] FIELD;
}

void Game::initGame()
{
    std::cout << "Initializing game's settings: " << std::endl;

    std::cout << "Field's width  (5 - 100) = ";
    std::cin >> FIELD_WIDTH;

    std::cout << "Field's height (5 - 100) = ";
    std::cin >> FIELD_HEIGHT;

    std::cout << "Cell's width   (20 - 50) = ";
    std::cin >> CELL_WIDTH;

    std::cout << "Cell's height  (20 - 50) = ";
    std::cin >> CELL_HEIGHT;

    std::cout << "Fullscreen ( 1 / 0, 1 - true, 0 - false ) : ";
    std::cin >> FULLSCREEN;

    //Добавляем по 1, чтобы при отрисовке линий не получить ошибку о выходе за границы массива
    FIELD_HEIGHT++;
    FIELD_WIDTH++;

    SCREEN_WIDTH = (FIELD_WIDTH - 1) * CELL_WIDTH;
    SCREEN_HEIGHT = (FIELD_HEIGHT - 1) * CELL_HEIGHT;

    FIELD = new STATE * [FIELD_HEIGHT];
    for (int i = 0; i < FIELD_HEIGHT; i++) FIELD[i] = new STATE[FIELD_WIDTH];

    for (int i = 0; i < FIELD_HEIGHT; i++)
        for (int j = 0; j < FIELD_WIDTH; j++)
            FIELD[i][j] = EMPTY;

    redPlayer.initPlayer(round(FIELD_WIDTH / 2) - 1, round(FIELD_HEIGHT / 2), true);
    bluePlayer.initPlayer(round(FIELD_WIDTH / 2) + 1, round(FIELD_HEIGHT / 2), false);

    std::cout << "Game has been initialized successfully!" << std::endl;
    std::cout << std::endl;
    std::cout << "Red Player's active keys: A,W,S,D and Q to place a point." << std::endl;
    std::cout << "Blue Player's active keys: LEFT,UP,DOWN,RIGHT(Arrows) and /(.) to place a point." << std::endl;
    std::cout << std::endl;
    std::cout << "Hit a key to start the game . . .";

    _getch();
}

void Game::tick()
{
    //В будущем напишу сюда алгоритм для поиска полигонов, образовавшихся из замкнутых линий и в последствии их закраску
}

void Game::draw()
{
    //РИСУЕМ ПОЛЕ---------------------------------------------
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(CELL_WIDTH / 6.0f);

    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(0, i * CELL_WIDTH);
        glVertex2f(SCREEN_WIDTH, i * CELL_WIDTH);
        glEnd();
    }

    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(CELL_HEIGHT * i, 0);
        glVertex2f(CELL_HEIGHT * i, SCREEN_HEIGHT);
        glEnd();
    }
    //---------------------------------------------------------

    //РИСУЕМ КУРСОРЫ ИГРОКОВ-----------------------------------
    glEnable(GL_POINT_SMOOTH);
    glPointSize(CELL_WIDTH / 2.0f);

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(redPlayer.posX * CELL_WIDTH, redPlayer.posY * CELL_HEIGHT);
    glColor3f(0.0f, 0.3019f, 1.0f);
    glVertex2f(bluePlayer.posX * CELL_WIDTH, bluePlayer.posY * CELL_HEIGHT);
    glEnd();
    //---------------------------------------------------------

    //РИСУЕМ ТОЧКИ---------------------------------------------
    glPointSize(CELL_WIDTH / 2.5f);

    for (int y = 1; y < FIELD_HEIGHT - 1; y++)
        for (int x = 1; x < FIELD_WIDTH - 1; x++)
        {
            switch (FIELD[y][x])
            {
            case EMPTY:
                break;
            case REDPLAYER:
                glBegin(GL_POINTS);
                glColor3f(0.5f, 0.0f, 0.0f);
                glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT);
                glEnd();
                break;
            case BLUEPLAYER:
                glBegin(GL_POINTS);
                glColor3f(0.0f, 0.3019f, 0.5f);
                glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT);
                glEnd();
                break;
            }    
        }
    //---------------------------------------------------------

    //РИСУЕМ ЛИНИИ МЕЖДУ ТОЧКАМИ-------------------------------
    for (int y = 1; y < FIELD_HEIGHT - 1; y++)
        for (int x = 1; x < FIELD_WIDTH - 1; x++)
        {
            if (FIELD[y][x] != EMPTY)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (FIELD[y][x] == FIELD[y + Y[i]][x + X[i]] != EMPTY)
                    {
                        switch (FIELD[y][x])
                        {
                        case REDPLAYER:
                            glColor3f(0.5f, 0.0f, 0.0f);
                            break;
                        case BLUEPLAYER:
                            glColor3f(0.0f, 0.3019f, 0.5f);
                            break;
                        }
                        glBegin(GL_LINES);
                        glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT);
                        glVertex2f((x + X[i]) * CELL_WIDTH, (y + Y[i]) * CELL_HEIGHT);
                        glEnd();
                    }
                }
            }
        }
    //---------------------------------------------------------

}