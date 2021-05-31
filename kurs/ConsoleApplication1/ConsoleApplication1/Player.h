#pragma once

class Player
{
public:
    unsigned __int16 posX;
    unsigned __int16 posY;

    bool goes;

    Player() {}; 

    void initPlayer(int _posX, int _posY, bool _goes)
    {
        posX = _posX;
        posY = _posY;
        goes = _goes;
    }
};