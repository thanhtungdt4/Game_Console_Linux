/*
 * Author: Nguyen Thanh Tung
 * Date: 2024-08-12
 */

#include "PlayRoom.h"

int main() {
    try {
        PlayRoom mainRoom;
        mainRoom.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
    return 0;
}