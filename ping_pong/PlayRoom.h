/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef _PLAYROOM_H_
#define _PLAYROOM_H_

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "Common.h"
#include "IntroductionRoom.h"
#include "Ball.h"
#include "Paddle.h"

class PlayRoom {
public:
    PlayRoom();
    ~PlayRoom() { endwin(); }

    void run();
private:
    int _playerPoint { 0 };
    int _computerPoint { 0 };
    const int _roomWidth { ROOM_WIDTH };
    const int _roomHeight { ROOM_HEIGHT };

    /* handler collisions between Ball and Paddle */
    void collisionsHandler();
    void drawRoom();
    void setBallSpeed();

    IntroductionRoom _introRoom;

    Ball _ball;
    Paddle _player;
    Paddle _computer;

    ColorHandle _red;
    ColorHandle _green;
    ColorHandle _blue;
    ColorHandle _yellow;
    ColorHandle _magenta;
};

#endif /* _PLAYROOM_H_ */