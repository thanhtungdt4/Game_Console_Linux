/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#ifndef INTRODUCTION_ROOM_H_
#define INTRODUCTION_ROOM_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Color.h"

#define EASY              1
#define HARD              2
#define ROOM_INTRO_WIDTH  112
#define ROOM_INTRO_HEIGHT 26
#define FILE_NAME         "/home/tungnt/game_console/ping_pong/pingpong.txt"

class IntroductionRoom {
public:
    IntroductionRoom() : _blue(Color::Blue), _red(Color::Red), _green(Color::Green) {}

    void run();
    int levelSelected { EASY };
private:
    std::vector<std::string> readFile();
    void printArt(const std::vector<std::string>& art);
    void highLightEasy(int x, int y);
    void normalEasy(int x, int y);
    void highLightHard(int x, int y);
    void normalHard(int x, int y);
    void drawRoomIntro();

    ColorHandle _blue;
    ColorHandle _red;
    ColorHandle _green;
    const std::string _filename { FILE_NAME };
};

#endif /* INTRODUCTION_ROOM_H_ */