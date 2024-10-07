/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef _PLAYROOM_H_
#define _PLAYROOM_H_

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>

#include "Common.h"
#include "IntroductionRoom.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

#define ROOM_FILE "/opt/room.txt"

class PlayRoom {
public:
    PlayRoom();
    ~PlayRoom() { endwin(); }

    void setRoomNumber(int roomNumber) { _roomNumber = roomNumber; }
    void run();
private:
    int _roomWidth      { ROOM_WIDTH };
    int _roomHeight     { ROOM_HEIGHT };
    int _playerPoint    { 0 };
    int _playerHeart    { 3 };
    int _roomNumber     { 0 };
    int _totalRoom      { 0 };
    int _pColisionCount { 0 };
    int _randomSpeed    { 4 };
    int _stepSpeed      { 3 };

    /* handler collisions between Ball and Paddle */
    void collisionsHandler();
    void pointCollisionHandle(int x, int y, int brick_x, int brick_y);
    void drawRoom();
    void setBallSpeed();
    bool isBrickAtXY(int x, int y);
    bool isRightBrickEmpty(int brick_x, int brick_y);
    bool isLeftBrickEmpty(int brick_x, int brick_y);
    bool isAllBrickDestroyed();

    void parseRoomFile(const std::string& filename);

    IntroductionRoom _introRoom;
    std::vector<Brick> bricks;

    Ball _ball;
    Paddle _player;

    ColorHandle _red;
    ColorHandle _green;
    ColorHandle _blue;
    ColorHandle _yellow;
    ColorHandle _magenta;
    ColorHandle _cyan;
    ColorHandle _gray;
    ColorHandle _darkPurple;
    ColorHandle _lightGreen;
    ColorHandle _pink;
};

#endif /* _PLAYROOM_H_ */
