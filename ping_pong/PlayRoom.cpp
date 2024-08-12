/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#include "PlayRoom.h"

PlayRoom::PlayRoom()
  : _blue(Color::Blue),
    _red(Color::Red),
    _green(Color::Green),
    _yellow(Color::Yellow),
    _magenta(Color::Magenta),
    _ball(_roomWidth / 2, _roomHeight / 2),
    _player(_roomWidth / 2 - 1, _roomHeight - 3),
    _computer(_roomWidth / 2 - 1, 2)
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(0);
    std::srand(static_cast<unsigned int>(std::time(0)));

    if (has_colors() == FALSE) {
        endwin();
        throw std::invalid_argument("Your terminal does not support color");
    }
    start_color();
}

void PlayRoom::setBallSpeed()
{
    if (_introRoom.levelSelected == EASY) {
        _ball.setmoveSpeed(std::rand() % 4 + 3);
    } else {
        _ball.setmoveSpeed(std::rand() % 3 + 2);
    }
}

void PlayRoom::collisionsHandler() {
    /* Check for paddle collisions */
        if (_ball.get_y() == _player.get_y()) {
                if (_ball.get_x() == _player.get_x() + 1) {
                    _ball.set_x(_player.get_x() + 1 - (_ball.get_dir_x() < 0 ? 0 : 1));
                    _ball.set_y(_player.get_y() - 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _player.get_x() + 2) {
                    _ball.set_x(_player.get_x() + 2 - (_ball.get_dir_x() < 0 ? 0 : 1));
                    _ball.set_y(_player.get_y() - 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _player.get_x() + 3) {
                    _ball.set_x(_player.get_x() + 3 - (_ball.get_dir_x() < 0 ? 0 : 1));
                    _ball.set_y(_player.get_y() - 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _player.get_x() + 4) {
                    _ball.set_x(_player.get_x() + 4 - (_ball.get_dir_x() < 0 ? 0 : 1));
                    _ball.set_y(_player.get_y() - 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _player.get_x() + 5) {
                    _ball.set_x(_player.get_x() + 5 - (_ball.get_dir_x() < 0 ? 0 : 1));
                    _ball.set_y(_player.get_y() - 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _player.get_x() + 6) {
                    _ball.set_x(_player.get_x() + 6 - (_ball.get_dir_x() < 0 ? 0 : 1));
                    _ball.set_y(_player.get_y() - 1);
                    _ball.bounce();
                    setBallSpeed();
                }
        }

        if (_ball.get_y() == _computer.get_y()) {
                if (_ball.get_x() == _computer.get_x() + 1) {
                    _ball.set_x(_computer.get_x());
                    _ball.set_y(_computer.get_y() + 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _computer.get_x() + 2) {
                    _ball.set_x(_computer.get_x() + 1);
                    _ball.set_y(_computer.get_y() + 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _computer.get_x() + 3) {
                    _ball.set_x(_computer.get_x() + 2);
                    _ball.set_y(_computer.get_y() + 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _computer.get_x() + 4) {
                    _ball.set_x(_computer.get_x() + 3);
                    _ball.set_y(_computer.get_y() + 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _computer.get_x() + 5) {
                    _ball.set_x(_computer.get_x() + 4);
                    _ball.set_y(_computer.get_y() + 1);
                    _ball.bounce();
                    setBallSpeed();
                }
                if (_ball.get_x() == _computer.get_x() + 6) {
                    _ball.set_x(_computer.get_x() + 5);
                    _ball.set_y(_computer.get_y() + 1);
                    _ball.bounce();
                    setBallSpeed();
                }
        }

}

void PlayRoom::drawRoom() {
    _red.ColorOn();
    for (int i = 0; i < _roomHeight; i++) {
        mvprintw(i, 0, "H");              // Left border
        mvprintw(i, _roomWidth - 1, "H"); // Right border
    }
    for (int i = 0; i < _roomWidth; i++) {
        mvprintw(0, i, "z");              // Top border
        mvprintw(_roomHeight - 1, i, "z");// Bottom border
    }
    _red.ColorOff();
}

void PlayRoom::run() {
    int time;
    int ch;

start:
    _introRoom.run();
    usleep(500000);

    _red.FullColor();
    _green.FullColor();
    _blue.FullColor();
    _yellow.FullColor();
    _magenta.StringColor();

    _ball.setCoordinate(_roomWidth / 2, _roomHeight / 2);
    _ball.setDirXY();
    _player.setCoordinate(_roomWidth / 2 - 1, _roomHeight - 3);
    _computer.setCoordinate(_roomWidth / 2 - 1, 2);

    _computerPoint = 0;
    _playerPoint = 0;
    time = 0;

    while ((ch = getch()) != 'q') {
        clear();
        drawRoom();

        mvprintw(0, _roomWidth + 5, "Computer Point: %d", _computerPoint);
        mvprintw(_roomHeight - 1, _roomWidth + 5 , "Player Point: %d", _playerPoint);

        mvprintw((_roomHeight / 2) - 3, _roomWidth + 5, "Ball X: %d", _ball.get_x());
        mvprintw((_roomHeight / 2) - 2, _roomWidth + 5, "Ball Y: %d", _ball.get_y());

        mvprintw((_roomHeight / 2) - 1, _roomWidth + 5, "Player X: %d", _player.get_x());
        mvprintw((_roomHeight / 2), _roomWidth + 5, "Player Y: %d", _player.get_y());

        mvprintw((_roomHeight / 2) + 1, _roomWidth + 5, "BallSpeed %d", _ball.getmoveSpeed());

        if (_introRoom.levelSelected == EASY) {
            int b = rand() % 4;
            _computer.draw(_yellow);
            if (_ball.get_x() > b && _ball.get_x() < _roomWidth - b - 5) {
                _computer.moveAuto(_ball.get_x() - 1 + b);
            }
        }
        else {
            int b = rand() % 3;
            _computer.draw(_green);
            if (_ball.get_x() > b && _ball.get_x() < _roomWidth - b - 5) {
                _computer.moveAuto(_ball.get_x() - 1 + b);
            }
        }

        _player.draw(_blue);
        _ball.draw();

        if (ch == KEY_LEFT) {
            _player.moveLeft();
        } else if (ch == KEY_RIGHT) {
            _player.moveRight();
        }

        _ball.move();
        collisionsHandler();

        if (_ball.get_y() == 1) {
            _playerPoint++;
            _ball.draw();
            _ball.reset();
        } else if (_ball.get_y() == _roomHeight - 2) {
            _computerPoint++;
            _ball.draw();
            _ball.reset();
        }

        if (_computerPoint == 11) {
            time++;
            _ball.stop();
            _magenta.ColorOn();
            mvprintw((_roomHeight / 2) + 3, _roomWidth + 5, "***COMPUTER WIN***");
            _magenta.ColorOff();
            if (time == 200) {
                clear();
                time = 0;
                goto start;
            }
        }

        if (_playerPoint == 11) {
            time++;
            _ball.stop();
            _magenta.ColorOn();
            mvprintw((_roomHeight / 2) + 3, _roomWidth + 5, "***PLAYER WIN***");
            _magenta.ColorOff();
            if (time == 200) {
                clear();
                time = 0;
                goto start;
            }
        }
        usleep(DELAY);
    }

    endwin();
}