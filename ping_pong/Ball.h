/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef _BALL_H_
#define _BALL_H_

#include <ncurses.h>

#include "Common.h"

class Ball {
public:
    Ball(int x, int y) : _x(x), _y(y), _dir_x(1), _dir_y(1) {}

    void draw() const {
        mvprintw(_y, _x, "o");
    }

    void move() {
        _timeCount++;
        if (_timeCount % _moveSpeed == 0) {
            _x += _dir_x;
            _y += _dir_y;
            if (_y <= 1 || _y >= ROOM_HEIGHT - 2) {
                _dir_y = -_dir_y;
            }
            if (_x <= 1 || _x >= ROOM_WIDTH - 2) {
                if (_x <= 1)
                    _x = 1;
                _dir_x = -_dir_x;
            }
        }
        if (_timeCount >= 10000) {
            _timeCount = 0;
        }
    }

    void stop() { _dir_x = 0; _dir_y = 0; }

    void bounce() { _dir_x = (_dir_x > 0) ? 1 : -1; _dir_y = -_dir_y; }

    void reset() {
        _x = ROOM_WIDTH / 2;
        _y = ROOM_HEIGHT / 2;
        _dir_x = (_dir_x > 0) ? -1 : 1;
        _moveSpeed = 8;
    }
    void set_y(int y) { _y = y; }

    void set_x(int x) { _x = x; }

    void setDirXY() { _dir_x = 1; _dir_y = 1; }

    void setCoordinate(int x, int y) { _x = x; _y = y; }

    void setmoveSpeed(int speed) { _moveSpeed = speed; }
    int get_x() const { return _x; }
    int get_y() const { return _y; }
    int get_dir_x() const { return _dir_x; };
    int getmoveSpeed() const { return _moveSpeed; };

private:
    int _x, _y;
    int _dir_x, _dir_y;
    int _timeCount { 0 };
    int _moveSpeed { 8 };
};

#endif /* _BALL_H_ */