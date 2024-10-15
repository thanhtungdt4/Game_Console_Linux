/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#include <cstdlib>
#include "PlayRoom.h"

int main(int argc, char *argv[]) {
    int roomNumber;
    if (argc >= 2) {
        roomNumber = std::atoi(argv[1]);
    } else {
        roomNumber = 0;
    }

    try {
        PlayRoom mainRoom;
        if (roomNumber > mainRoom.getTotalRoom()) {
            std::cout << "Invalid Room number" << std::endl;
            return -1;
        }
        if (roomNumber > 0) {
            roomNumber--;
        }
        mainRoom.setRoomNumber(roomNumber);
        mainRoom.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}