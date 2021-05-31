#pragma once

#include "Player.h"


class Game
{
private:
    __int16 Y[4];
    __int16 X[4];

public:
    enum STATE { EMPTY, REDPLAYER, BLUEPLAYER };

    STATE** FIELD;

    unsigned __int16 SCREEN_WIDTH;
    unsigned __int16 SCREEN_HEIGHT;

    unsigned __int16 FIELD_WIDTH;
    unsigned __int16 FIELD_HEIGHT;

    unsigned __int16 CELL_WIDTH;
    unsigned __int16 CELL_HEIGHT;

    bool FULLSCREEN;
    bool redPlayersTurn;
    bool bluePlayersTurn;

    Player redPlayer;
    Player bluePlayer;

    Game();
    ~Game();

    void tick();
    void initGame();
    void draw();
};