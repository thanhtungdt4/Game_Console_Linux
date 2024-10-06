/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef _BRICK_H_
#define _BRICK_H_

#include "Color.h"

class Brick {
public:
    Brick(int startX, int startY, int type) : x(startX), y(startY), brickType(type), isDestroyed(false) {}

    void draw(ColorHandle& yellow, ColorHandle& magenta, ColorHandle& cyan,
            ColorHandle& green, ColorHandle& gray) {
        if (!isDestroyed) {
            if (brickType == 1) {
                green.ColorOn();
                mvprintw(y, x, "===");
                green.ColorOff();
            } else if (brickType == 2) {
                yellow.ColorOn();
                mvprintw(y, x, "===");
                yellow.ColorOff();
            } else if (brickType == 3) {
                magenta.ColorOn();
                mvprintw(y, x, "###");
                magenta.ColorOff();
            } else if (brickType == 4) {
                cyan.ColorOn();
                mvprintw(y, x, "###");
                cyan.ColorOff();
            } else if (brickType == 5) {
                gray.ColorOn();
                mvprintw(y, x, "###");
                gray.ColorOff();
            }
        }
    }

    void destroy() {
        brickType--;
        if (brickType <= 0)
            isDestroyed = true;
    }

    int get_x() const { return x; }
    int get_y() const { return y; }

    bool isDestroyed;
private:
    int x, y;
    int brickType { 1 };
};

#endif /* _BRICK_H_ */