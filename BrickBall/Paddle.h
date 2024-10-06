/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Color.h"
#include "Common.h"

class Paddle {
public:
    Paddle(int x, int y) : _x(x), _y(y) {}

    void draw(ColorHandle& color) const {
        color.ColorOn();
        mvprintw(_y, _x + 1, "-----");
        color.ColorOff();
    }

    void moveLeft() {
        if (_x >= 1) {
            _x -= 1;
        }
    }

    void moveRight() {
        if (_x < ROOM_WIDTH - 7) {
            _x += 1;
        }
    }

    void setCoordinate(int x, int y) { _x = x; _y = y; }
    void moveAuto(int x) { _x = x; } /* For Computer */
    int get_x() const { return _x; }
    int get_y() const { return _y; }

private:
    int _x, _y;
};


#endif /* _PADDLE_H_ */