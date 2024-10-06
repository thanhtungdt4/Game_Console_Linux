/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include <ncurses.h>

enum class Color {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    white,
    gray,
    pink,
    lightGreen = 51,
    darkPurple = 57,
};

class ColorHandle {
public:
    ColorHandle(Color color) : _color(color) {
    }

    void FullColor() {
        int colorValue = static_cast<int>(_color);
        init_pair(colorValue, colorValue, colorValue);
    }

    void StringColor() {
        int colorValue = static_cast<int>(_color);
        init_pair(colorValue, colorValue, static_cast<int>(Color::Black));
    }

    void ColorOn() {
        int colorValue = static_cast<int>(_color);
        attron(COLOR_PAIR(colorValue));
    }

    void ColorOff() {
        int colorValue = static_cast<int>(_color);
        attroff(COLOR_PAIR(colorValue));
    }
private:
    Color _color;
};

#endif /* _COLOR_H_ */
