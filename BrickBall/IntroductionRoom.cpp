/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#include "IntroductionRoom.h"

std::vector<std::string> IntroductionRoom::readFile() {
    std::vector<std::string> lines;
    std::ifstream file(_filename);
    if (!file) {
        std::cerr << "Error opening file: " << _filename << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

void IntroductionRoom::printArt(const std::vector<std::string>& art) {
    if (art.empty()) {
        mvprintw(0, 0, "No content to display.");
        return;
    }

    _red.ColorOn();
    for (size_t i = 0; i < art.size(); ++i) {
        mvprintw(static_cast<int>(i + 2), 10, "%s", art[i].c_str());
    }
    _red.ColorOff();
}

void IntroductionRoom::highLightStart(int x, int y) {
    _green.ColorOn();
    mvprintw(y, x, "START");
    _green.ColorOff();
}

void IntroductionRoom::drawRoomIntro() {
    _red.ColorOn();
    for (int i = 0; i < ROOM_INTRO_HEIGHT; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, ROOM_INTRO_WIDTH - 1, "|");
    }
    for (int i = 0; i < ROOM_INTRO_WIDTH; i++) {
        mvprintw(0, i, "-");
        mvprintw(ROOM_INTRO_HEIGHT - 1, i, "-");
    }
    _red.ColorOff();
}

void IntroductionRoom::run() {
    int ch;
    std::vector<std::string> art = readFile();

    _red.StringColor();
    _blue.StringColor();
    _green.StringColor();
    highLightStart(ROOM_INTRO_WIDTH / 2 -2, 19);
    drawRoomIntro();

    while ((ch = getch())) {
        printArt(art);
        _blue.ColorOn();
        mvprintw(22, 29, "Press 'Enter' to start; Press 'q' Key to EXIT");
        _blue.ColorOff();
        if (ch == '\n' || ch == '\r' || ch == KEY_ENTER) {
            break;
        }
        if (ch == 'q') {
            endwin();
            exit(0);
        }
    }
}