#include "Game.h"
#include <iostream> // For std::cerr

int main() {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "An unhandled exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "An unknown unhandled exception occurred." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}