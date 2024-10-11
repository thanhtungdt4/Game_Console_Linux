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
    _cyan(Color::Cyan),
    _gray(Color::gray),
    _darkPurple(Color::darkPurple),
    _lightGreen(Color::lightGreen),
    _pink(Color::pink),
    _ball(_roomWidth / 2, _roomHeight / 2),
    _player(_roomWidth / 2 - 1, _roomHeight - 3)
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(0);
    std::srand(static_cast<unsigned int>(std::time(0)));

    /* get initial high score */
    getHighScore();

    if (parseTotalRoom(ROOM_FILE)) {
        endwin();
        throw std::invalid_argument("Read room.txt failed");
    }

    if (has_colors() == FALSE) {
        endwin();
        throw std::invalid_argument("Your terminal does not support color");
    }
    start_color();
}

void PlayRoom::getHighScore()
{
    const char* homeDir = getenv("HOME");
    std::string filePath = std::string(homeDir) + HIGHSCORE_FILE;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        _initalhighScore = 0;
        file.close();
    } else {
        file >> _initalhighScore;
        file.close();
    }
}

void PlayRoom::saveHighScore(const int &playerPoint)
{
    const char* homeDir = getenv("HOME");
    std::string filePath = std::string(homeDir) + HIGHSCORE_FILE;
    std::ofstream file(filePath, std::ios::out);

    if (file.is_open()) {
        file << playerPoint;
        file.close();
    }
}

void PlayRoom::setBallSpeed()
{
    _ball.setmoveSpeed(std::rand() % _randomSpeed + _stepSpeed);
}

bool PlayRoom::isBrickAtXY(int x, int y)
{
    for (auto &brick : bricks) {
        if (!brick.isDestroyed) {
            if (brick.get_x() <= x && x <= brick.get_x() + 2 && y == brick.get_y()) {
                return true;
            }
        }
    }
    return false;
}

bool PlayRoom::isRightBrickEmpty(int brick_x, int brick_y)
{
    return !isBrickAtXY(brick_x + 3, brick_y) ? true : false;
}

bool PlayRoom::isLeftBrickEmpty(int brick_x, int brick_y)
{
    return !isBrickAtXY(brick_x - 1, brick_y) ? true : false;
}

bool PlayRoom::isAllBrickDestroyed()
{
    int destroyCount = 0;
    for (auto &brick : bricks) {
        if (brick.isDestroyed) {
            destroyCount++;
            if (destroyCount == bricks.size()) {
                return true;
            }
        }
    }

    return false;
}

int PlayRoom::parseTotalRoom(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("START") != std::string::npos) {
            _totalRoom++;
        }
    }

    file.close();

    return 0;
}

void PlayRoom::parseRoomFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool inRoom = false;
    int currentRoom = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    /* Clear bricks vector */
    bricks.clear();

    while (std::getline(file, line)) {
        if (line.substr(0, 5) == "START") {
            currentRoom = std::stoi(line.substr(6));
            inRoom = (currentRoom == _roomNumber);
            y = 0;
            width = 0;
            height = 0;
        } else if (line.substr(0, 3) == "END" && inRoom) {
            break;
        } else if (inRoom) {
            if (line.size() > width) {
                width = line.size();
            }
            height++;

            for (int x = 0; x < line.size(); x++) {
                char ch = line[x];
                if (ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5') {
                    int brickType = ch - '0';
                    bricks.emplace_back(x, y, brickType);
                }
            }
            y++;
        }
    }

    file.close();

    _roomHeight = height;
    _roomWidth = width;
}

void PlayRoom::pointCollisionHandle(int x, int y, int brick_x, int brick_y)
{
    if (_ball.get_dir_x() == 1 && _ball.get_dir_y() == -1) {
        if (x == brick_x) {
            if (!isBrickAtXY(x, y + 1)) {
                _ball.set_x(x);
                _ball.set_y(y + 1);
                _ball.set_dirx(1);
                _ball.set_diry(1);
            } else if (!isBrickAtXY(x - 1, y) && isLeftBrickEmpty(brick_x, brick_y)) {
                _ball.set_x(x - 1);
                _ball.set_y(y);
                _ball.set_dirx(-1);
                _ball.set_diry(-1);
            } else {
                _ball.set_x(x - 1);
                _ball.set_y(y + 1);
                _ball.set_dirx(-1);
                _ball.set_diry(1);
            }
        } else if (x == (brick_x + 1) || x == (brick_x + 2)) {
            if (!isBrickAtXY(x, y + 1)) {
                _ball.set_x(x);
                _ball.set_y(y + 1);
                _ball.set_dirx(1);
                _ball.set_diry(1);
            } else {
                _ball.set_x(x - 1);
                _ball.set_y(y + 1);
                _ball.set_dirx(-1);
                _ball.set_diry(1);
            }
        }
    } else if (_ball.get_dir_x() == -1 && _ball.get_dir_y() == -1) {
        if (x == brick_x || x == (brick_x + 1)) {
            if (!isBrickAtXY(x, y + 1)) {
                _ball.set_x(x);
                _ball.set_y(y + 1);
                _ball.set_dirx(-1);
                _ball.set_diry(1);
            } else {
                _ball.set_x(x + 1);
                _ball.set_y(y + 1);
                _ball.set_dirx(1);
                _ball.set_diry(1);
            }
        } else if (x == (brick_x + 2)) {
            if (!isBrickAtXY(x, y + 1)) {
                _ball.set_x(x);
                _ball.set_y(y + 1);
                _ball.set_dirx(-1);
                _ball.set_diry(1);
            } else if (!isBrickAtXY(x + 1, y) && isRightBrickEmpty(brick_x, brick_y)) {
                _ball.set_x(x + 1);
                _ball.set_y(y);
                _ball.set_dirx(1);
                _ball.set_diry(-1);
            } else {
                _ball.set_x(x + 1);
                _ball.set_y(y + 1);
                _ball.set_dirx(1);
                _ball.set_diry(1);
            }
        }
    } else if (_ball.get_dir_x() == 1 && _ball.get_dir_y() == 1) {
        if (x == brick_x) {
            if (!isBrickAtXY(x, y - 1)) {
                _ball.set_x(x);
                _ball.set_y(y - 1);
                _ball.set_dirx(1);
                _ball.set_diry(-1);
            } else if (!isBrickAtXY(x - 1, y) && isLeftBrickEmpty(brick_x, brick_y)) {
                _ball.set_x(x - 1);
                _ball.set_y(y);
                _ball.set_dirx(-1);
                _ball.set_diry(1);
            } else {
                _ball.set_x(x - 1);
                _ball.set_y(y - 1);
                _ball.set_dirx(-1);
                _ball.set_diry(-1);
            }
        } else if (x == (brick_x + 1) || x == (brick_x + 2)) {
            if (!isBrickAtXY(x, y - 1)) {
                _ball.set_x(x);
                _ball.set_y(y - 1);
                _ball.set_dirx(1);
                _ball.set_diry(-1);
            } else {
                _ball.set_x(x - 1);
                _ball.set_y(y - 1);
                _ball.set_dirx(-1);
                _ball.set_diry(-1);
            }
        }
    } else if (_ball.get_dir_x() == -1 && _ball.get_dir_y() == 1) {
        if (x == brick_x || x == (brick_x + 1)) {
            if (!isBrickAtXY(x, y - 1)) {
                _ball.set_x(x);
                _ball.set_y(y - 1);
                _ball.set_dirx(-1);
                _ball.set_diry(-1);
            } else {
                _ball.set_x(x + 1);
                _ball.set_y(y - 1);
                _ball.set_dirx(1);
                _ball.set_diry(-1);
            }
        } else if (x == (brick_x + 2)) {
            if (!isBrickAtXY(x, y - 1)) {
                _ball.set_x(x);
                _ball.set_y(y - 1);
                _ball.set_dirx(-1);
                _ball.set_diry(-1);
            } else if (!isBrickAtXY(x + 1, y) && isRightBrickEmpty(brick_x, brick_y)) {
                _ball.set_x(x + 1);
                _ball.set_y(y);
                _ball.set_dirx(1);
                _ball.set_diry(1);
            } else {
                _ball.set_x(x + 1);
                _ball.set_y(y - 1);
                _ball.set_dirx(1);
                _ball.set_diry(-1);
            }
        }
    } else if (_ball.get_dir_x() == 0) {
        _ball.set_x(x);
        _ball.set_y(y + 1);
        _ball.set_diry(1);
    }
}

void PlayRoom::collisionsHandler() {
    /* Check for paddle collisions */
    if (_ball.get_y() == _player.get_y()) {
        if (_ball.get_x() == _player.get_x() + 1) {
            _ball.set_x(_player.get_x() + 1);
            _ball.set_y(_player.get_y() - 1);
            _ball.draw();
            _ball.bounceLeft();
            setBallSpeed();
            _pColisionCount++;
            if (_pColisionCount >= 10) {
                if (_playerPoint >= 2) {
                    _playerPoint -= 2;
                }
                _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
                _ball.is_move = false;
                _ball.setDirXY();
            }
        }
        if (_ball.get_x() == _player.get_x() + 2) {
            _ball.set_x(_player.get_x() + 2);
            _ball.set_y(_player.get_y() - 1);
            _ball.draw();
            _ball.bounceLeft();
            setBallSpeed();
            _pColisionCount++;
            if (_pColisionCount >= 10) {
                if (_playerPoint >= 2) {
                    _playerPoint -= 2;
                }
                _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
                _ball.is_move = false;
                _ball.setDirXY();
            }
        }
        if (_ball.get_x() == _player.get_x() + 3) {
            _ball.set_x(_player.get_x() + 3);
            _ball.set_y(_player.get_y() - 1);
            _ball.draw();
            _ball.bounceStraight();
            setBallSpeed();
            _pColisionCount++;
            if (_pColisionCount >= 5) {
                if (_playerPoint >= 1) {
                    _playerPoint--;
                }
                _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
                _ball.is_move = false;
            }
        }
        if (_ball.get_x() == _player.get_x() + 4) {
            _ball.set_x(_player.get_x() + 4);
            _ball.set_y(_player.get_y() - 1);
            _ball.draw();
            _ball.bounceRight();
            setBallSpeed();
            _pColisionCount++;
            if (_pColisionCount >= 10) {
                if (_playerPoint >= 2) {
                    _playerPoint -= 2;
                }
                _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
                _ball.is_move = false;
                _ball.setDirXY();
            }
        }
        if (_ball.get_x() == _player.get_x() + 5) {
            _ball.set_x(_player.get_x() + 5);
            _ball.set_y(_player.get_y() - 1);
            _ball.draw();
            _ball.bounceRight();
            setBallSpeed();
            _pColisionCount++;
            if (_pColisionCount >= 10) {
                if (_playerPoint >= 2) {
                    _playerPoint -= 2;
                }
                _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
                _ball.is_move = false;
                _ball.setDirXY();
            }
        }
    }

    /* Check collisions with bricks */
    for (auto &brick : bricks) {
        if (!brick.isDestroyed) {
            if (brick.get_x() <= _ball.get_x() && _ball.get_x() <= brick.get_x() + 2 &&
                    _ball.get_y() == brick.get_y()) {
                pointCollisionHandle(_ball.get_x(), brick.get_y(), brick.get_x(), brick.get_y());
                brick.destroy();
                _playerPoint++;
                _pColisionCount = 0; /* reset _pColisionCount */
            }
        }
    }

}

void PlayRoom::drawRoom()
{
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
    usleep(400000);

    _red.FullColor();
    _blue.FullColor();
    _green.FullColor();
    _yellow.FullColor();
    _magenta.FullColor();
    _cyan.FullColor();
    _gray.FullColor();
    _pink.StringColor();
    _darkPurple.StringColor();
    _lightGreen.StringColor();
    _playerHeart = 3;
    _randomSpeed = 4;
    _stepSpeed = 3;
    _playerPoint = 0;
    _pColisionCount = 0;

nextRoom:
    _roomNumber++;
    parseRoomFile(ROOM_FILE);

    _player.setCoordinate(_roomWidth / 2 - 1, _roomHeight - 3);
    _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
    _ball.setDirXY();
    time = 0;

    if (_roomNumber > 5 && _roomNumber <= 10) {
        _randomSpeed = 3;
    } else if (_roomNumber > 10 && _roomNumber <= 15) {
        _randomSpeed = 2;
    } else if (_roomNumber > 15 && _roomNumber <= 25) {
        _stepSpeed = 2;
    } else if (_roomNumber > 25) {
        _stepSpeed = 1;
    }

    while ((ch = getch()) != 'q') {
        clear();
        drawRoom();

        for (auto& brick : bricks) {
            brick.draw(_yellow, _magenta, _cyan, _green, _gray);
        }

        _pink.ColorOn();
        mvprintw(1, _roomWidth + 5, "Heart S2: %d", _playerHeart);
        _pink.ColorOff();
        _lightGreen.ColorOn();
        mvprintw(3, _roomWidth + 5, "Player Score: %d", _playerPoint);
        mvprintw(5, _roomWidth + 5, "Room Number: %d", _roomNumber);
        mvprintw(7, _roomWidth + 5, "Total Room: %d", _totalRoom);
        mvprintw(9, _roomWidth + 5, "High Score: %d", _initalhighScore);
        _lightGreen.ColorOff();

        mvprintw((_roomHeight / 2) - 1, _roomWidth + 5, "dir X: %d", _ball.get_dir_x());
        mvprintw((_roomHeight / 2), _roomWidth + 5, "dir Y: %d", _ball.get_dir_y());
        mvprintw((_roomHeight / 2) + 1, _roomWidth + 5, "Ball Speed %d", _ball.getmoveSpeed());
        mvprintw((_roomHeight / 2) + 2, _roomWidth + 5, "Total bricks: %ld", bricks.size());
        mvprintw((_roomHeight / 2) + 3, _roomWidth + 5, "Colision Count: %d", _pColisionCount);

        _player.draw(_blue);

        if (ch == KEY_LEFT) {
            _player.moveLeft();
            _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
        } else if (ch == KEY_RIGHT) {
            _player.moveRight();
            _ball.setCoordinate(_player.get_x() + 3, _player.get_y() - 1);
        }
        if (ch == '\n' || ch == '\r' || ch == KEY_ENTER) {
            _ball.is_move = true;
        }
        _ball.draw();
        _ball.move();
        collisionsHandler();

        if (_ball.get_y() == _roomHeight - 2) {
            _player.setCoordinate(_roomWidth / 2 - 1, _roomHeight - 3);
            _ball.set_x(_player.get_x() + 3);
            _ball.set_y(_roomHeight - 4);
            _playerHeart--;
            _ball.is_move = false;
            _ball.setDirXY();
            _ball.setmoveSpeed(3);
        }

        if (_playerHeart == 0) {
            time++;
            _ball.stop();
            _darkPurple.ColorOn();
            mvprintw((_roomHeight / 2) + 5, _roomWidth + 5, "***GAME OVER***");
            _darkPurple.ColorOff();
            if (time == 200) {
                clear();
                time = 0;
                _roomNumber = 0;
                goto start;
            }
        }
        if (isAllBrickDestroyed()) {
            time++;
            _player.setCoordinate(_roomWidth / 2 - 1, _roomHeight - 3);
            _ball.set_x(_player.get_x() + 3);
            _ball.set_y(_roomHeight - 4);
            _ball.is_move = false;

            if (_roomNumber == _totalRoom) {
                _darkPurple.ColorOn();
                mvprintw(_roomHeight - 1, _roomWidth + 5, "***MAX ROOM NUMBER***");
                _darkPurple.ColorOff();
                if (time == 100) {
                    clear();
                    time = 0;
                    _roomNumber = 0;
                    goto start;
                }
            } else {
                _darkPurple.ColorOn();
                mvprintw(_roomHeight - 1, _roomWidth + 5, "=>GOING TO NEXT ROOM, LOADING...");
                _darkPurple.ColorOff();
                if (time == 100) {
                    clear();
                    time = 0;
                    goto nextRoom;
                }
            }
        }
        usleep(DELAY);
    }

    endwin();

    if (_playerPoint > _initalhighScore) {
        saveHighScore(_playerPoint);
    }
}